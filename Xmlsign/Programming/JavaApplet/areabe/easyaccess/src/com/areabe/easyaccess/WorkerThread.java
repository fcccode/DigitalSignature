package com.areabe.easyaccess;

import java.io.*;
import com.areabe.easyaccess.dns.Named;
import com.areabe.easyaccess.net.TCPSession;
import com.areabe.easyaccess.platform.*;
import com.areabe.easyaccess.EasyAccess;
import com.areabe.easyaccess.Log;
import com.areabe.easyaccess.Config;
import java.net.*;
import java.util.*;

public class WorkerThread
    extends Thread {
  private final EasyAccess parent;
  public NativeHelper helper;
  private Vector sockets = new Vector();
  private Vector serverSockets = new Vector();
  private boolean dnsModified = false;
  private boolean dnsFailed = false; // jnamed will set it to true when TCP or UDP listener fails
  private boolean tcpFailed = false;
  private boolean keepAlive = true;
  private Named dns;
  private Log log = Log.getInstance();
  private Config cfg = Config.getInstance();
  private Object sockLock = new Object();
  private Object serverSockLock = new Object();

  public Object listenerLock = new Object();
  public ListenerThread lt = null;

  public WorkerThread(EasyAccess applet) {
    parent = applet;
  }

  public void run() {
    try {
      String s = System.getProperty("java.vendor");
      String osName = System.getProperty("os.name");
      String osVersion = System.getProperty("os.version");
      if (s.indexOf("Microsoft") >= 0)
        helper = (NativeHelper) Class.forName(
            "com.areabe.easyaccess.platform.MS").
            newInstance();
      else {
        if (osName.startsWith("Windows")) {
          helper = (NativeHelper) Class.forName(
              "com.areabe.easyaccess.platform.SunWindows").
              newInstance();
        }else if(osName.toLowerCase().startsWith("linux")){
          helper = (NativeHelper) Class.forName(
              "com.areabe.easyaccess.platform.SunLinux").
              newInstance();
        }else{
          throw new IOException("Unsupported OS: " + osName);
        }
      }
      helper.init(parent, osName, osVersion);
      helper.addNameServer();
      dnsModified = true;
      // set SSL provider
      helper.addProvider();
      // add DNS entries
      initDNS();
      // when listener stops it will reset dns status
      startListener();
      parent.setStatus(EasyAccess.INACTIVE);
      log.println("EaccessAccess v. " +parent.getVersion()+ " started.");
      while (keepAlive && !dnsFailed && !tcpFailed) {
        try {
          synchronized (this) {
            this.wait();
          }
        }
        catch (Exception ie) {}
      }
      if (Config.debug) {
        System.err.println("WorkerThread notified");
      }
      if (dnsFailed) {
        throw new IOException("DNS listener failed");
      }
      if (tcpFailed) {
        throw new IOException("TCP listener failed");
      }
    }
    catch (Exception e) {
      if (Config.debug) {
        e.printStackTrace();
      }
      log.println(e.getMessage());
    }
    finally {
      // restore DNS
      restoreDNS();

      // stop listeners
      stopThread();

      if (Config.debug) {
        System.err.println("EasyAccess: WorkerThread stopped");
      }
      log.println("EasyAccess: WorkerThread stopped");
      parent.setStatus(EasyAccess.BROKEN);
    }
  }

  /**
   * Start DNS server
   * @throws Exception
   */
  void initDNS() throws Exception {
    dns = new Named(this);
  }

  /**
   * Open listener on specified port and forward requests to the socks server.
   */
  void startListener() {
    // get all ports to listen on from Host configuration table
    Enumeration en = cfg.tcpPorts.keys();
    while (en.hasMoreElements()) {
      String sPort = (String) en.nextElement();
      String bindAddress = (String) cfg.tcpPorts.get(sPort);
      int port = Integer.parseInt(sPort);
      ListenerThread t = new ListenerThread(bindAddress, port, null, 0, 0, this);
    }
  }

  /**
   * Special case for Ftp and TNS
   *
   * @param bindAddress
   * @param port
   */
  public void startListener(String bindAddress, int port, String destIP, int destPort, int protocol) {
    ListenerThread t = new ListenerThread(bindAddress, port, destIP, destPort, protocol, this);
  }


  /**
   * closure of sockets should terminate the thread.
   * This method must not have any unsafe code i.e. work with Registry or file system.
   */
  public synchronized void stopThread() {
    // this is to stop current thread
    if (!keepAlive)
      return; // this code already been executed
    keepAlive = false;
    // close all sessions
    synchronized (sockLock) {
      for (int i = 0; i < sockets.size(); i++) {
        try {
          ( (Socket) sockets.elementAt(i)).close();
        }
        catch (Exception e) {}
      }
    }
    System.err.println("All sockets closed");

    // close TCP listeners
    synchronized (serverSockLock) {
      for (int i = 0; i < serverSockets.size(); i++) {
        try {
          ServerSocket serverSock = (ServerSocket) serverSockets.elementAt(i);
          serverSock.close();
          System.err.println("ServerSocket OID=" + serverSock.toString() +
                             " closed.");
        }
        catch (Exception e) {
          if (Config.debug) {
            System.err.println("Can't close ServerSocket: " + e.getMessage());
            e.printStackTrace();
          }
        }
      }
    }
    System.err.println("All server sockets closed");

    // close DNS listeners
    if (dns != null)
      dns.stopListeners();
    dns = null;

    synchronized (this) {
      try {
        this.notifyAll();
      }
      catch (Exception e) {}
    }
  }

  private synchronized void setDNSStatus(boolean val) {
    dnsModified = val;
  }

  public synchronized void setDNSFailed() {
    dnsFailed = true;
  }

  public synchronized void setTCPFailed() {
    tcpFailed = true;
  }

  private synchronized void restoreDNS() {
    if (dnsModified) {
      // restore DNS
      try {
        helper.restoreNameServer();
        setDNSStatus(false);
        log.println("DNS stopped");
      }
      catch (Exception e1) {
        e1.printStackTrace();
      }
    }
  }

  public class ListenerThread
      extends Thread {
    String bindAddress=null;
    int port=0;
    int destPort=0;
    String destIP = null;
    int protocol = 0;
    public WorkerThread wt = null;
    ListenerThread(String bindAddress, int port, String destIP, int destPort, int protocol, WorkerThread parent) {
      this.bindAddress = bindAddress;
      this.port = port;
      this.wt = parent;
      this.destPort = destPort;
      this.destIP = destIP;
      this.protocol = protocol;
      start();
    }

    public void run() {
      serveTCP(this.port, this.destPort, this.bindAddress, this.destIP, this.protocol, this);
      System.err.println("ListenerThread stopped: port =" + port + ", address=" +
                         bindAddress);
    }
    /**
     * Open listener on specified port. Pass all incoming data to the SocksClient
     */
    void serveTCP(int port, int destPort, String address, String destIP, int protocol, Thread wt) {
      Socket sock = null;
      ServerSocket serverSock = null;
      try {
        log.println("Listen on port " + port + ", host=" + address);
        InetAddress bindAddress = InetAddress.getByName(address);
        serverSock = new ServerSocket(port, 0, bindAddress);

        synchronized (serverSockLock) {
          serverSockets.addElement(serverSock);
        }

        while (true) {
          sock = serverSock.accept();
          if (Config.debug) {
            log.println("Accepted connection on port " + port);
          }
          try {
            synchronized (sockLock) {
              sockets.addElement(sock);
            }
            TCPSession tcpSes = new TCPSession(parent, sock, port, destPort, destIP, protocol, this);
            if (protocol==Config.FTP_DATA) {
              // wait until session closed and break the loop
              synchronized (this) {
                this.wait();
                break;
              }
            }
          }
          catch (Exception e) {
            e.printStackTrace();
          }
        }
      }
      catch (Exception e) {
        if (Config.debug) {
          System.err.println("WorkerThread: TCP listener on port " + port +
                             " stopped, exception: " + e.getMessage());
          if (! (e instanceof IOException)) {
            e.printStackTrace();
          }
        }
      }
      finally {

        if (sock!=null) {
          try {
            sock.close();
          }
          catch (IOException ioe) {}
          synchronized (sockLock) {
            sockets.removeElement(sock);
          }
        }

        if (serverSock!=null) {
          try {
            serverSock.close();
          }
          catch (IOException ioe) {}
          synchronized (serverSockLock) {
            serverSockets.removeElement(serverSock);
          }
        }

        setTCPFailed();
        synchronized (wt) {
          try {
            wt.notifyAll();
          }
          catch (Exception e) {}
        }
        log.println("Listener stopped on port " + port + ", host = " + address);
      }
    }
 }
}
