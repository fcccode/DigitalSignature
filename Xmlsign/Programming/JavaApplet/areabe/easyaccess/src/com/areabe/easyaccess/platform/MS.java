package com.areabe.easyaccess.platform;

import java.io.*;
import java.net.*;
import java.util.*;

import org.xwt.*;
import com.areabe.easyaccess.*;
import com.ms.lang.*;

public class MS
    implements NativeHelper {
  private RegKey reg = null;
  private String interfaces =
      "System\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces";
  private String w98 = "System\\CurrentControlSet\\Services\\VxD";
  private Hashtable saved = new Hashtable();
  public boolean restored = true;
  String dll = null;
  EasyAccess parent = null;
  String osVersion = null;
  String osName = null;
  String w98NameServer = null; // old value for NameServer
  Log log = Log.getInstance();

  public MS() {
  }

  public void init(EasyAccess ea, String osName, String osVersion) throws
      Exception {
    parent = ea;
    this.osVersion = osVersion;
    this.osName = osName;
  }

  /**
   * Add new entry for DNS
   *
   * @param ns
   */
  public void addNameServer() throws Exception {
    try {
      if (osName.equals("Windows 95")
          || osName.equals("Windows 95")
          || osName.equals("Windows 98")
          || osName.equals("Windows Me")
          ) {
        addNameServer98();
      }
      else if (osName.equals("Windows NT")
               || osName.equals("Windows 2000")
               || osName.equals("Windows XP")
               ) {
        addNameServerNT();
      }
      else {
        log.println("Not supported OS:" + osName + "/" + osVersion);
      }
    }catch(Exception e){
      if (Config.debug) {
        e.printStackTrace();
      }
      log.print("Cannot change DNS settings");
      throw e;
    }
  }

  /**
   * Add new entry for DNS - Windows NT/2000/XP/2003 version
   *
   * @param ns
   */
  private void addNameServerNT() throws Exception{
      reg = new RegKey(RegKey.LOCALMACHINE_ROOT, interfaces);
      String newValue = null;
      RegQueryInfo info = reg.queryInfo();
      int numInterfaces = info.subKeys;
      for (int i = 0; i < numInterfaces; i++) {
        String key = reg.enumKey(i);
        if (key == null)
          continue;
        RegKey ifc = new RegKey(reg, key, RegKey.KEYOPEN_ALL);
        String oldNameServer = null;
        try {
          oldNameServer = ifc.getStringValue("NameServer");
        }
        catch (com.ms.lang.RegKeyException rke) {
          ifc.close();
          continue;
        }

        // get rid of 127.0.0.1 if any
        int ins = -1;
        if (oldNameServer != null && (ins = oldNameServer.indexOf(ns)) >= 0) {
          StringTokenizer st = new StringTokenizer(oldNameServer, ",");
          StringBuffer sb = new StringBuffer();
          while (st.hasMoreTokens()) {
            String cNs = st.nextToken();
            if (cNs.equals(ns))
              continue;
            if (sb.length() > 0)
              sb.append(',');
            sb.append(cNs);
          }
          String sVal = sb.toString();
          saved.put(key, sVal);
          ifc.close();
          // original entry already has it
          continue;
        }

        if (oldNameServer != null && oldNameServer.indexOf(ns) < 0) {
          newValue = ns;
          saved.put(key, oldNameServer);
          // get DHCPNameServer if any
          try {
            if (oldNameServer != null && oldNameServer.length() > 0) {
              newValue += "," + oldNameServer;
            }
            else {
              String dhcpNS = ifc.getStringValue("DhcpNameServer");
              if (dhcpNS != null && dhcpNS.length() > 0) {
                newValue += "," + dhcpNS;
              }
            }
          }
          catch (Exception e1) {}
          // protect from storing pure localhost as DNS server
          if (newValue!=null && newValue.length()>0 && !newValue.equals(ns)) {
            ifc.setValue("NameServer", newValue);
          }
        }
        ifc.close();
      }
      reg.close();
      registerDNS();
      log.println("DNS started");
      restored = false;
  }

  /**
   * Add new entry for DNS - Windows 98/Me
   *
   * @param ns
   */
  private void addNameServer98() throws Exception{
      reg = new RegKey(RegKey.LOCALMACHINE_ROOT, w98);
      String newValue = null;
      RegKey ifc = new RegKey(reg, "MSTCP", RegKey.KEYOPEN_ALL);
      String oldNameServer = null;
      try {
        oldNameServer = ifc.getStringValue("NameServer");
        // get rid of 127.0.0.1 if any
        int ins = -1;
        if (oldNameServer != null && (ins = oldNameServer.indexOf(ns)) >= 0) {
          StringTokenizer st = new StringTokenizer(oldNameServer, ",");
          StringBuffer sb = new StringBuffer();
          while (st.hasMoreTokens()) {
            String cNs = st.nextToken();
            if (cNs.equals(ns))
              continue;
            if (sb.length() > 0)
              sb.append(',');
            sb.append(cNs);
          }
          String sVal = sb.toString();
          w98NameServer = sVal;
        }
        else if (oldNameServer != null && oldNameServer.indexOf(ns) < 0) {
          newValue = ns;
          w98NameServer = oldNameServer;
          // get DHCPNameServer if any
          try {
            if (oldNameServer != null && oldNameServer.length() > 0) {
              newValue += "," + oldNameServer;
            }
            else {
              String dhcpNS = ifc.getStringValue("DhcpNameServer");
              if (dhcpNS != null && dhcpNS.length() > 0) {
                newValue += "," + dhcpNS;
              }
            }
          }
          catch (Exception e1) {}
          // protect from storing pure localhost as DNS server
          if (newValue!=null && newValue.length()>0 && !newValue.equals(ns)) {
            ifc.setValue("NameServer", newValue);
          }
        }
        ifc.close();
      }
      catch (com.ms.lang.RegKeyException rke) {
        ifc.close();
      }
      reg.close();
      registerDNS98();
      log.println("W98: DNS started");
      restored = false;
  }

  /**
   * Restore settings for DNS
   *
   * @param e
   */
  public synchronized void restoreNameServer(){
    if (restored)
      return;
    try {
    if (osName.equals("Windows 95")
        || osName.equals("Windows 95")
        || osName.equals("Windows 98")
        || osName.equals("Windows Me")
        ) {
      restoreNameServer98();
    }
    else if (osName.equals("Windows NT")
             || osName.equals("Windows 2000")
             || osName.equals("Windows XP")
             ) {
      restoreNameServerNT();
    }
    else {
      log.println("Not supported OS:" + osName + "/" + osVersion);
    }
    }catch(Exception e){}
  }

  /**
   * Restore settings for DNS
   *
   * @param e
   */
  private void restoreNameServerNT() throws Exception{
      reg = new RegKey(RegKey.LOCALMACHINE_ROOT, interfaces);
      RegQueryInfo info = reg.queryInfo();
      int numInterfaces = info.subKeys;
      for (int i = 0; i < numInterfaces; i++) {
        String key = reg.enumKey(i);
        if (key == null)
          continue;
        if (!saved.containsKey(key))
          continue;
        RegKey ifc = new RegKey(reg, key, RegKey.KEYOPEN_ALL);
        String oldNameServer = null;
        try {
          oldNameServer = ifc.getStringValue("NameServer");
        }
        catch (com.ms.lang.RegKeyException rke) {
          System.err.println("Not found NameServer for " + key);
          ifc.close();
          continue;
        }
        String rval = (String) saved.get(key);
        if (rval == null) {
          rval = "";
        }
        if (Config.debug) {
          System.err.println("restore NameServer for key: " + key);
        }
        ifc.setValue("NameServer", rval);
        ifc.close();
      }
      reg.close();
      registerDNS();
      restored = true;
  }

  /**
   * Restore settings for DNS
   *
   * @param e
   */
  private void restoreNameServer98() throws Exception {
      if (w98NameServer == null)
        return;
      reg = new RegKey(RegKey.LOCALMACHINE_ROOT, w98);
      RegKey ifc = new RegKey(reg, "MSTCP", RegKey.KEYOPEN_ALL);
      String oldNameServer = null;
      try {
        oldNameServer = ifc.getStringValue("NameServer");
        String rval = w98NameServer;
        if (rval == null) {
          rval = "";
        }
        if (Config.debug) {
          System.err.println("restore NameServer for W98");
        }
        ifc.setValue("NameServer", rval);
        ifc.close();
      }
      catch (com.ms.lang.RegKeyException rke) {
        System.err.println("Not found NameServer for w98 to retsore");
        ifc.close();
      }
      reg.close();
      registerDNS98();
      restored = true;
  }

  /**
   * Call native command to refresh DNS records
   */
  private static void registerDNS() {
    try {
      Runtime.getRuntime().exec("ipconfig /registerdns");
    }
    catch (Exception e) {
      if (Config.debug) {
        e.printStackTrace();
      }
    }
  }

  /**
   * Call native command to refresh DNS records
   */
  private static void registerDNS98() {
    try {
      Runtime.getRuntime().exec("ipconfig /renew_all");
    }
    catch (Exception e) {
      if (Config.debug) {
        e.printStackTrace();
      }
    }
  }

  /**
   * Register security provider for SSL
   * @throws Exception
   */
  public void addProvider() throws Exception {
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
