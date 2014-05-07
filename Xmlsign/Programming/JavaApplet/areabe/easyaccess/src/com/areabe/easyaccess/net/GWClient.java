package com.areabe.easyaccess.net;

import java.net.*;
import java.io.*;
import java.util.StringTokenizer;

import com.areabe.easyaccess.Config;
import com.areabe.easyaccess.Log;
import com.areabe.easyaccess.WorkerThread;
import com.areabe.easyaccess.EasyAccess;

public class GWClient extends Message
    implements Runnable{
//our applet
  TCPSession parent = null;
//Network related members
  Thread net_thread = null;
  BufferedInputStream in = null;
  BufferedOutputStream out = null; // server output stream
  BufferedOutputStream client_os = null; // client output stream
  Socket sock = null;
  ServerSocket server_sock = null;
  Object net_lock = new Object();
  Log log = Log.getInstance();
  Config cfg = Config.getInstance();

  private String gwHost;
  private int gwPort;
  public static final int SERVER_NOT_FOUND = 1;
  public static final int SESSION_EXPIRED = 3;
  public static final int LOGIN_FAILED = 2;
  public static final int RESPONSE_OK = 0;
  public static final int CORE_FAILED = 4;
  public static final int ACCESS_DENIED = 5;
  public static final int BAD_HEADER = 6;
  public static final int GW_CON_FAILED = -1;

  private WorkerThread wt = null;

  public GWClient(TCPSession parent) {
    this.parent = parent;
    this.gwPort = cfg.gwPort;
    this.gwHost = cfg.gwHost;
    this.wt = parent.lt.wt;
  }

//Runnable interface
///////////////////////////////

  public void run() {
    try {
      doRead();
    }
    catch (IOException io_ex) {}
    finally {
      disconnect();
    }
  }

  /**
   * Starts new read thread
   *
   * @param client_os
   */
  public void read(BufferedOutputStream client_os) {
    this.client_os = client_os;
    startNetThread();
  }

  /**
   * Connect to the gateway, initialize protocol
   *
   * @param h
   * @param p
   * @throws IOException
   */
  public int connect(String h, int p) throws Exception {
    if (Config.debug) {
      System.err.println("Trying to connect to:" + h + ":" + p);
    }
    if (cfg.isSSLMode()) {
      try {
        sock = wt.helper.getSecureSocket(gwHost, gwPort);
      }catch(Exception e) {
        log.println("Cannot establish SSL session: " + e.getMessage());
        e.printStackTrace(log);
      }
    }else{
      sock = new Socket(gwHost, gwPort);
    }
    out = new BufferedOutputStream(sock.getOutputStream());
    in = new BufferedInputStream(sock.getInputStream());

    // send protocol header
    StringBuffer sb = new StringBuffer();
    sb.append("GET /eaconnect HTTP/1.1\r\n");
    sb.append("User-Agent: EasyAccess " + EasyAccess.version + "\r\n");
    sb.append("Cookie: ");
    sb.append("swanstorserver=");
    sb.append(cfg.getServerName());
    sb.append(';');
    sb.append("sessionid=");
    sb.append(cfg.getSessionID());
    sb.append(';');
    sb.append("host=");
    sb.append(h);
    sb.append(';');
    sb.append("port=");
    sb.append(p);
    sb.append(';');
    sb.append("protocol=");
    sb.append(parent.protocol);
    sb.append(";\r\n\r\n");

    byte[] hdr = sb.toString().getBytes();
    out.write(hdr);
    out.flush();
    if (Config.debug) {
      System.err.println("Connection header:" + sb.toString());
    }

    // read response
    LineNumberReader reader = new LineNumberReader(new InputStreamReader(in));
    String line=null;
    int response=GW_CON_FAILED;
    while ((line= reader.readLine())!=null) {
      if (line.trim().length()==0) {
        break;
      }
      if (line.startsWith("Response:")) {
        int i = line.indexOf(':');
        String strRes = line.substring(i+1).trim();
        try {
          response = Integer.parseInt(strRes);
        }catch(Exception ignore){
          log.println("Cannot recognize GW response - must be numeric, got: <" + strRes + ">");
        }
      }
    }
    return response;
  }

  /**
   * Close session
   */
  public void disconnect() {
    synchronized (net_lock) {
      abort_connection();
      server_sock = null;
      sock = null;
      out = null;
      in = null;
      net_thread = null;
      parent.stopSession();
    }
  }

  /**
   * Send data to the GW
   *
   * @param buf
   * @param len
   */
  public void send(byte[] buf, int len) {
    synchronized (net_lock) {
      if (out == null)
        return;
      try {
        out.write(buf, 0, len);
        out.flush();
      }
      catch (IOException io_ex) {
        abort_connection();
      }
    }
  }

//Network related private functions
////////////////////////////
  private void startNetThread() {
    net_thread = new Thread(this);
    net_thread.start();
  }

  private void abort_connection() {
    synchronized (net_lock) {
      if (net_thread != null) {
        try {
          if (sock != null)
            sock.close();
          if (server_sock != null)
            server_sock.close();
        }
        catch (IOException ioe) {
        }
        net_thread.interrupt();
        net_thread = null;
      }
    }
  }

  private void doRead() throws IOException {
    try {
      if (in == null || client_os == null) {
        throw new IOException(
            "GWClint InputStream or Client OutputStream is null");
      }
      byte[] buf = new byte[TCPSession.READ_BUFFER];
      int bytes_read = 0;

      if (parent.protocol == Config.FTP) {
        // read by line
        try {
          while (true) {
            String line = readLine(in);
            if (line == null || line.length() == 0)break;
            byte[] b = handleFTP(line);
            if (b != null && b.length > 0) {
              client_os.write(b);
              client_os.flush();
            }
            else {
              client_os.write(line.getBytes());
              client_os.write('\r');
              client_os.write('\n');
              client_os.flush();
            }
          }
        }
        catch (IOException ioe) {
          throw ioe;
        }
        catch (Exception e) {
          if (Config.debug) {
            log.println("Cannot parse FTP request: " + e.getMessage());
            e.printStackTrace();
          }
        }
      }
      else {
        while ( (bytes_read = in.read(buf)) > 0) {
          client_os.write(buf, 0, bytes_read);
          client_os.flush();
        }
      }
    }catch(IOException iox) {
      throw iox;
    }catch(Exception e) {
      if (Config.debug) {
       e.printStackTrace();
      }
      throw new IOException(e.getMessage());
    }
  }

  /**
   * Ftp handler
   *
   * @param dt
   * @param len
   * @return
   */
  private byte[] handleFTP(String line) {
    String ftpServerIP = "";
    String myIP = (String) cfg.tcpPorts.get(String.valueOf(parent.port));

    try {
      String ret = null;
      String start_with = "227 Entering Passive Mode ";
      //
      // If the passed string doesn't start with above, return
      //
      if (line.length() < start_with.length())
        return null;

      //
      // If the passed string starts with the above pattern
      //
      if (line.startsWith(start_with)) {
        //
        // The port used for sending data is a standard port given in the Init file.
        //
        int myPort = getFreeTCPPort(myIP);
        if (myPort==0) {
          log.println("Cannot allocate TCP port for FTP data connection");
          return null;
        }
        int mp1 = myPort / 256;
        int mp2 = myPort - (mp1 * 256);

        int ftpPort = 0;
        int p1 = 0;
        int p2 = 0;
        StringTokenizer st = new StringTokenizer(line, " ");
        String[] parts = new String[5];
        int tkcnt = 0;
        if (st.countTokens() < 5) {
          return null;
        }
        while (st.hasMoreTokens()) {
          parts[tkcnt] = st.nextToken();
          tkcnt++;
          if (tkcnt == 5)
            break;
        }
        int i2 = parts[4].indexOf('(');
        String s1 = parts[4].substring(i2 + 1);
        int i3 = s1.indexOf(')');
        String s2 = s1.substring(0, i3);

        String[] parts227 = new String[6];
        st = new StringTokenizer(s2, ",");
        if (st.countTokens() < 6) {
          return null;
        }
        tkcnt = 0;
        while (st.hasMoreTokens()) {
          parts227[tkcnt] = st.nextToken();
          tkcnt++;
          if (tkcnt == 6)
            break;
        }

        ftpServerIP = parts227[0] + "." + parts227[1] + "." +
            parts227[2] + "." + parts227[3];
        p1 = Integer.parseInt(parts227[4]);
        p2 = Integer.parseInt(parts227[5]);
        ftpPort = p1 * 256 + p2;

        String myIP_comma = myIP.replace('.', ',');
        ret = start_with + "(" + myIP_comma + "," + mp1 + "," + mp2 + ")\r\n";
        //
        // Start new listener in a separate thread
        //
        wt.startListener(myIP,myPort,ftpServerIP,ftpPort,Config.FTP_DATA);
        return ret.getBytes();
      }else{
        return null;
      }
    }
    catch (Exception e) {
      if (Config.debug) {
        System.err.println("Cannot parse FTP response");
        e.printStackTrace();
      }
    }
    return null;
  }

  /**
   * Locate unused TCP port > 60000
   *
   * @return
   */
  private int getFreeTCPPort(String ip) {
    InetAddress ia = null;
    try {
      ia = InetAddress.getByName(ip);
    }catch(IOException e){}
    for (int i=60000;i<65535;i++) {
      try {
        ServerSocket s = new ServerSocket(i,0,ia);
        s.close();
        return i;
      }catch(IOException e){}
    }
    return 0;
  }
}
