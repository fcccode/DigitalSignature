package com.areabe.easyaccess.platform;

import java.util.*;
import java.io.*;
import java.net.*;
import com.areabe.easyaccess.Log;
import com.areabe.easyaccess.EasyAccess;
import com.areabe.easyaccess.Config;
/*
import com.claymoresystems.cert.*;
import com.claymoresystems.ptls.*;
import com.claymoresystems.sslg.*;
*/
import org.xwt.TinySSL;

public class SunLinux implements NativeHelper{
  public boolean restored = true;
  EasyAccess parent = null;
  String osVersion = null;
  String osName = null;
  Log log = Log.getInstance();
  byte[] oldDNS = null;
  Config cfg = Config.getInstance();
  private static final String nsConfig = "/etc/resolv.conf";
  private static final String newNS = "nameserver 127.0.0.1\n";
  private boolean alreadyExists = false;

  public SunLinux() {
  }

  public void init(EasyAccess ea,String osName,String osVersion) throws Exception{
    this.parent = ea;
    this.osVersion = osVersion;
    this.osName = osName;
  }

  public void addNameServer() throws Exception {
    // modify file /etc/resolv.conf
    try {
      File f = new File(nsConfig);
      File back = new File("/tmp/resolv.conf~");

      try {
        if (back.exists())
          back.delete();
      }catch(Exception e0){}

      FileInputStream fs = new FileInputStream(f);
      byte[] ctx = new byte[ (int) f.length()];
      fs.read(ctx);
      fs.close();
      oldDNS = ctx;

      // make backup
      FileOutputStream fos = new FileOutputStream(back);
      fos.write(oldDNS);
      fos.close();

      // rewrite old file
      String s = new String(oldDNS);
      LineNumberReader lr = new LineNumberReader(new StringReader(s));
      String line = null;
      while ((line = lr.readLine())!=null) {
        if (line.indexOf(ns)>0) {
          alreadyExists = true;
          break;
        }
      }
      lr.close();

      // do nothing if such line already exists
      if (alreadyExists) return;

      fos = new FileOutputStream(f);
      fos.write(newNS.getBytes());
      fos.write(oldDNS);
      fos.close();
      restored = false;

    }catch(Exception e){
      if (Config.debug) {
        e.printStackTrace();
      }
      log.print("Cannot change DNS settings");
      throw e;
    }
  }

  public synchronized void restoreNameServer(){
    if (restored || alreadyExists)
      return;
    // modify file /etc/resolv.conf
    try {
      File f = new File(nsConfig);
      // rewrite the file with old content
      FileOutputStream fos = new FileOutputStream(f);
      fos = new FileOutputStream(f);
      fos.write(oldDNS);
      fos.close();

    }catch(Exception e){}
  }

  /**
   * Register security provider for SSL
   * @throws Exception
   */
  public void addProvider() throws Exception {
    // JSSE related
    //java.security.Security.addProvider(new com.sun.net.ssl.internal.ssl.Provider());
  }

  /**
   * Create secure socket
   * @param host
   * @param port
   * @return
   * @throws Exception
   */
  public Socket getSecureSocket(String host, int port) throws IOException {
    Socket s = new TinySSL(host, port, true, true);
    return (Socket) s;
  }

}