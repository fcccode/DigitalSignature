package com.areabe.easyaccess.net;

import java.io.*;
import java.net.*;
import java.util.*;

import com.areabe.easyaccess.*;

public class TCPSession
    extends Thread {
  private Socket sock;
  public int protocol = Config.UNKNOWN;
  public int port =0; // local port (listener)
  private int destPort =0; // port for connection on SWANStor side (FTP data case)
  private String destIP = null; // server to connect on SWANStor side (FTP data case)

  private EasyAccess parent = null;
  private Config cfg = Config.getInstance();
  private Log log = Log.getInstance();
  public WorkerThread.ListenerThread lt = null;

  public static int SEND_BUFFER = 8192;  // read from Client, write to the Gateway
  public static int READ_BUFFER = 8192;  // read from the Gateway, write to Client

  private int numread =0; // counter for http request content-length

  public TCPSession(EasyAccess parent, Socket sock, int port, int destPort, String destIP, int prot, WorkerThread.ListenerThread lt) {
    this.sock = sock;
    this.protocol = (prot==0)?cfg.getPortType(port):prot;
    this.parent = parent;
    this.port = port;
    this.destPort = destPort;
    this.destIP =destIP;
    this.lt = lt;
    start();
  }

  /**
   * TCP session
   *
   * @param sock
   * @param isHTTP
   */
  void session(Socket sock) {
    GWClient scl = null;

    try {
      scl = new GWClient(this);
      BufferedInputStream dataIn = new BufferedInputStream(sock.getInputStream());
      BufferedOutputStream dataOut = new BufferedOutputStream(sock.
          getOutputStream());
      byte[] buf = new byte[SEND_BUFFER];
      String item = null;

      try {
        HTTPRequest req = null;
        int conPort = (destPort>0)?destPort:port; // for Ftp-data and some other protocols port may be different from local
        String conHost = (String) cfg.tcpPorts.get(String.valueOf(port)); // use local port here
        if (conHost == null) {
          if (destIP == null) {
            log.println("Configuration error: no host for port " + port);
            parent.setStatus(EasyAccess.BROKEN);
            throw new IOException("Configuration error: no host for port " +
                                  port);
          }else{
            conHost = destIP;
          }
        }
//        String rHost = cfg.realHost.containsKey(conHost) ?
//            (String) cfg.realHost.get(conHost) : conHost;

        byte[] httpBuf = null;
        // special cases
        if (protocol==Config.HTTP) {
          // get Host header and use it for connection
          req = new HTTPRequest(dataIn);
          httpBuf = req.read();
          if (httpBuf == null) {
            sock.close();
            parent.setStatus(EasyAccess.BROKEN);
            log.println("Parse HTTP request failed. Close connection.");
            throw new IOException(
                "Parse HTTP request failed. Close connection.");
          }
          if (req.host == null) {
            sock.close();
            parent.setStatus(EasyAccess.BROKEN);
            log.println("Parse HTTP request failed - no Host header.");
            throw new IOException(
                "Parse HTTP request failed - no Host header. Close connection.");
          }
          conHost = (req.realHost != null) ? req.realHost : req.host;
          conPort = req.port;
          if (Config.debug) {
            log.print(req.command + " " + req.url + "\n");
            Enumeration en = req.getHeaders();
            while (en.hasMoreElements()) {
              String s = (String) en.nextElement();
              log.print(s);
              log.print(":");
              log.print(req.getHeaderField(s) + "\n");
            }
          }
        }

        String pName = Config.getProtocolName(protocol);

        if (Config.debug) {
          log.println("CONNECT: host: " + conHost + ", port: " + conPort +
                      ", protocol=" + pName);
        }

        item = pName + ": " + conHost + ":" + conPort;
        parent.addGUIConnection(item);

        int conStatus = GWClient.GW_CON_FAILED;
        try {
          conStatus = scl.connect(conHost, conPort); // connect to the gateway
        }
        catch (Exception e) {
          if (Config.debug) {
            e.printStackTrace(log);
            log.println("Connect failed: " + e.getMessage());
          }
        }

        String msg;
        switch (conStatus) {
          case GWClient.RESPONSE_OK:
//            log.println("Gateway: connection succeded.");
            parent.setStatus(EasyAccess.ACTIVE);
            break;
          case GWClient.CORE_FAILED:
            msg = "Gateway: Core connection failed.";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          case GWClient.LOGIN_FAILED:
            msg = "SWANStor: Login failed.";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          case GWClient.SERVER_NOT_FOUND:
            msg =
                "Gateway: SWANStor Server not connected to the core at this time.";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          case GWClient.SESSION_EXPIRED:
            msg = "SWANStor: Session expired.";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          case GWClient.ACCESS_DENIED:
            msg = "SWANStor: Access to " + conHost + " denied.";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          case GWClient.GW_CON_FAILED:
            msg = "Gateway: connection failed (Gateway not responding).";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          case GWClient.BAD_HEADER:
            msg = "Gateway: invalid request.";
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
          default:
            msg = "Gateway: connection refused, status: " + conStatus;
            log.println(msg);
            parent.setStatus(EasyAccess.BROKEN);
            sendResponse(403, dataOut, msg);
            throw new IOException(msg);
        }

        // start Read Thread
        scl.read(dataOut);
        // continue read
        // for non-http protocols just read and write
        if (protocol!=Config.HTTP) {
          int i = 0;
          while ( (i = dataIn.read(buf)) > 0) {
            scl.send(buf, i);
          }
        }else{
          /*
           * HTTP request must go through filter to replace "Host" header
           * Fro this reason we must follow request headers and read in according with content-length
           *
           */
          int contentLength = 0;
          boolean bodyTooBig = false;
          while (true) { // http keep-alive loop, may include several requests
          // write HTTP header data if any
            if (httpBuf != null) {
              scl.send(httpBuf, httpBuf.length);
              httpBuf = null;
            }
/*
            log.println("HTTP request: " + req.command + " " + req.url);
            Enumeration en = req.getHeaders();
            while (en.hasMoreElements()) {
              String s = (String) en.nextElement();
              log.print(s);
              log.print(":");
              log.print(req.getHeaderField(s)+"\n");
            }
*/
            if (!("GET".equals(req.command)) && req.containsHeaderField("Content-length")) {
              int n = Integer.parseInt(req.getHeaderField("Content-length"));
              contentLength = n;
              if (n > READ_BUFFER) {
                bodyTooBig = true;
                n = READ_BUFFER;
              }
              httpBuf = new byte[n];
              int offset = 0;
              while (offset < httpBuf.length) {
                n = dataIn.read(httpBuf, offset, httpBuf.length - offset);
                if (n < 0) {
                  throw new IOException("Premature end of request (read by Content-Length)");
                }
                numread += n;
                offset += n;
              } // read content body loop
            } // not GET

            if (httpBuf != null) {
              scl.send(httpBuf, httpBuf.length);
            }

            if (bodyTooBig) {
              while (numread<contentLength) {
                httpBuf = readNext(contentLength, dataIn);
                if (httpBuf != null) {
                  scl.send(httpBuf, httpBuf.length);
                  httpBuf = null;
                }
              }
              bodyTooBig = false;
            }

            req = new HTTPRequest(dataIn);
            httpBuf = req.read();
            if (httpBuf == null) {
              break;
            }
          } // keep-alive loop
        } // http case
      }
      catch (IOException e) {
        if (Config.debug) {
          System.err.println("TCPSession: local port " + port + ": Closing client socket by exception: " + e.getMessage());
        }
      }
      catch (Exception e) {
        if (Config.debug) {
          System.err.println("TCPSession: local port " + port);
          e.printStackTrace();
        }
      }
      finally {
        if (item != null) {
          try {
            parent.removeGUIConnection(item);
          }
          catch (Exception ei) {}
        }
        try {
          scl.disconnect();
          sock.close();
        }
        catch (Exception e1) {}
        if (protocol == Config.FTP_DATA) {
          synchronized (lt) {
            try {
              lt.notifyAll();
            }catch(Exception e){}
          }
        }
      }
    }
    catch (IOException io) {
      if (Config.debug) {
        System.err.println(io.getMessage());
      }
    }
  }

  /**
   * Used when request is bigger than we can handle (>Portal.BUFFER)
   */
  private byte[] readNext(int contentLength, BufferedInputStream in) throws IOException{
    byte[] data=null;
    if (contentLength-numread<READ_BUFFER) {
      data = new byte[contentLength-numread];
    }else{
      data = new byte[READ_BUFFER];
    }
    int offset = 0;
    int n=0;
    while (offset < data.length)
    {
       n = in.read(data, offset, data.length - offset);
       if (n < 0)
        {
          throw new IOException("Premature end of request (read by Content-Length, large request)");
        }
         numread +=n;
         offset += n;
    }
    return data;
  }


  /**
   * Main method
   */
  public void run() {
    session(sock);
  }

  /**
   * Close socket will stop the thread
   */
  public void stopSession() {
    try {
      if (sock != null)
        sock.close();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * Read input stream and locate "Host" header.
   */
  class HTTPRequest
      extends Message {
    String host = null;
    String realHost = null;
    int port = 80;
    private BufferedInputStream in = null;
    String command = null;
    String url = null;
    String protocol = null;

    HTTPRequest(BufferedInputStream dataIn) {
      in = dataIn;
      numread = 0;
    }

    public byte[] read() throws IOException {
      // read leading whitespace if any
      int len = 0;
      do {
         if ( (len = in.read()) == -1) {
           return null;
         }
      }
      while (Character.isWhitespace( (char) len));
      // put the character back
      statusLine = readLine(in);
      StringBuffer sb = new StringBuffer(statusLine);
      sb.insert(0, (char) len);
      statusLine = sb.toString();

      if (statusLine == null || statusLine.length() == 0) {
        return this.getBytes();
      }

      StringTokenizer st = new StringTokenizer(statusLine);
      try {
        command = (String) st.nextToken();
        url = (String) st.nextToken();
        protocol = (String) st.nextToken();
      }
      catch (Exception e) {
        return this.getBytes();
      }

      if (!protocol.startsWith("HTTP")) {
        return this.getBytes();
      }

      readHeaders(in);
// detect host and try to resolve it
      if (this.containsHeaderField("Host")) {
        host = this.getHeaderField("Host");
        int i = host.indexOf(':');
        if (i > 0) {
          try {
            port = Integer.parseInt(host.substring(i + 1));
          }
          catch (Exception e) {
            port = 80;
          }
          host = host.substring(0, i);
        }

        /*
         * fake hosts processing
         */
        // loop through realHost, look for closest match to host
        boolean loop=true;
        boolean found=false;
        i =0;
        String key = "." + host;
        StringBuffer prefix = new StringBuffer();
        while (loop) {
          i = key.indexOf(".");
          if (i>=0) {
            if (i>0) {
              prefix.append(key.substring(0,i+1));
            }
            key = key.substring(i+1);
          }else{
            loop = false;
          }
//          if (cfg.realHost.containsKey(key)) {
//            realHost = (String) cfg.realHost.get(key);
//            found=true;
//          }
          if (cfg.origHost.containsKey(key.toLowerCase())) {
            // replace fake host with original in http headers
            String oHost = (String) cfg.origHost.get(key.toLowerCase());
            prefix.append(oHost);
            this.setHeaderField("Host", prefix.toString());
            realHost = prefix.toString();
            found = true;
            break;
          }
        }

        if (!found) {
          realHost = host;
        }
      }
      return this.getBytes();
    }
  }

  /**
   * Send error response to the browser
   *
   * @param code
   * @param os
   * @param msg
   */
  private void sendResponse(int code, OutputStream os, String status) {
    try {
      StringBuffer sb = new StringBuffer();
      sb.append("HTTP/1.1 ");
      String stat = null;
      switch (code) {
        case 200:
          stat = "200 OK";
          break;
        case 202:
          stat = "202 Accepted";
          break;
        case 300:
          stat = "300 Ambiguous";
          break;
        case 301:
          stat = "301 Moved Permanently";
          break;
        case 302:
          stat = "302 Object Moved";
          break;
        case 400:
          stat = "400 Bad Request";
          break;
        case 401:
          stat = "401 Denied";
          break;
        case 403:
          stat = "403 Forbidden";
          break;
        case 404:
          stat = "404 Not Found";
          break;
        case 405:
          stat = "405 Bad Method";
          break;
        case 413:
          stat = "413 Request Entity Too Large";
          break;
        case 415:
          stat = "415 Unsupported Media";
          break;
        case 501:
          stat = "501 Not Implemented";
          break;
        case 502:
          stat = "502 Bad Gateway";
          break;
        case 504:
          stat = "504 Gateway Timeout";
          break;
        case 505:
          stat = "505 HTTP Version Not Supported";
          break;
        default:
          stat = "500 Internal Server Error";
      }

      String msg = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"><HTML>\r"
      + "<!-- Generated Message --><HEAD>\r"
      + "<TITLE>SWANStor EasyAccess warning/error</TITLE></HEAD>\r"
      + "<BODY BGCOLOR=\"#FFFFFF\" TEXT=\"#000000\" LINK=\"#000080\" VLINK=\"#000080\" ALINK=\"#000080\">\r"
      + "<h2 class=\"headline\">HTTP " + code + " </h2>\r"
      + "<HR ALIGN=\"center\" WIDTH=\"95%\" size=\"4\">\r"
      + "<p class=\"i30\">" + status + "</P>"
      + "<HR ALIGN=\"center\" WIDTH=\"95%\" size=\"4\">\r"
      + "<p class=\"i25\"><A HREF=\"http://www.areabe.com/\">AreaBe, Inc</A> SWANStor EasyAccess, Version " + parent.getVersion()
      + " Copyright (c) 2000-2004 by AreaBe, Inc</p>\r"
      + "</BODY></HTML>";

      sb.append(stat);
      sb.append("\r\n");
      sb.append("Content-Length:");
      sb.append(String.valueOf(msg.length()));
      sb.append("\r\n");
      sb.append("Content-Type: text/html; charset=iso-8859-1\r\n");
      sb.append("Connection: close\r\n\r\n");
      sb.append(msg);
      os.write(sb.toString().getBytes());
      os.flush();

     }catch(Exception e){
      log.println("Cannot return message to the browser: " + e.getMessage());
      if (Config.debug) {
        e.printStackTrace();
      }
    }
  }
}