package com.areabe.easyaccess.platform;
import com.ice.jni.registry.*;
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

public class SunWindows implements NativeHelper{
  private static com.ice.jni.registry.Registry reg = new Registry();
  private String interfacesStr  = "System\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces";
  private String w98 = "System\\CurrentControlSet\\Services\\VxD\\MSTCP";
  private Hashtable saved = new Hashtable();
  public boolean restored = true;
  String dll = null;
  EasyAccess parent = null;
  String osVersion = null;
  String osName = null;
  String w98NameServer = null; // old value for NameServer
  Log log = Log.getInstance();
  Config cfg = Config.getInstance();

  public SunWindows() {
  }

  public void init(EasyAccess ea,String osName,String osVersion) throws Exception{
    parent = ea;
    this.osVersion = osVersion;
    this.osName = osName;
    try {
      String libLocation = System.getProperty("java.home");
      libLocation += File.separator;
      libLocation += "jniregistry.dll";

      File f = new File(libLocation);
      boolean mustload = true;
      if (f.exists()) {
        if (f.length() != 55808) {
          f.delete();
        }
        else {
          mustload = false;
        }
      }
      if (mustload) {
        // get the library from URL
        downloadLibrary(libLocation);
      }
      if (!Registry.libraryLoaded) {
        Registry.loadLibrary(libLocation);
        if (!Registry.libraryLoaded) {
          throw new Exception("Library not loaded");
        }
      }
    }catch(Exception e){
      if (Config.debug) {
        e.printStackTrace();
      }
      log.print("Registry library not loaded");
      throw e;
    }
  }

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
        System.err.println("Not supported OS:" + osName + "/" + osVersion);
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
   * Add new entry for DNS
   *
   * @param ns
   */
  public void addNameServerNT() throws Exception{
      String newValue = null;
      RegistryKey hkeyLocal = Registry.HKEY_LOCAL_MACHINE;
      RegistryKey interfaces = hkeyLocal.openSubKey(interfacesStr,
          RegistryKey.ACCESS_ALL);
      int numInterfaces = interfaces.getNumberSubkeys();
      for (int i=0;i<numInterfaces;i++) {
        String key = interfaces.regEnumKey(i);
        RegistryKey ifc = interfaces.openSubKey(key,RegistryKey.ACCESS_ALL);
        String oldNameServer = null;
        try {
          oldNameServer = ifc.getStringValue("NameServer");
        }catch(RegistryException e) {
          ifc.closeKey();
          continue;
        }
        // get rid of 127.0.0.1 if any
        int ins = -1;
        if (oldNameServer != null && (ins = oldNameServer.indexOf(ns))>=0) {
          StringTokenizer st = new StringTokenizer(oldNameServer,",");
          StringBuffer sb= new StringBuffer();
          while (st.hasMoreTokens()) {
            String cNs = st.nextToken();
            if (cNs.equals(ns)) continue;
            if (sb.length()>0) sb.append(',');
            sb.append(cNs);
          }
          String sVal = sb.toString();
          saved.put(key, sVal);
          ifc.closeKey();
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
            RegStringValue rval = new RegStringValue(ifc, "NameServer",
                newValue);
            ifc.setValue(rval);
          }
        }
        ifc.closeKey();
      }
      interfaces.closeKey();
      hkeyLocal.closeKey();
      registerDNSNT();
      log.println("DNS started");
      restored = false;
  }

  /**
   * Add new entry for DNS
   *
   * @param ns
   */
  public void addNameServer98() throws Exception{
      String newValue = null;
      RegistryKey hkeyLocal = Registry.HKEY_LOCAL_MACHINE;
      RegistryKey ifc = hkeyLocal.openSubKey(w98,
          RegistryKey.ACCESS_ALL);
      String oldNameServer = null;
      try {
        oldNameServer = ifc.getStringValue("NameServer");
        // get rid of 127.0.0.1 if any
        int ins = -1;
        if (oldNameServer != null && (ins = oldNameServer.indexOf(ns))>=0) {
          StringTokenizer st = new StringTokenizer(oldNameServer,",");
          StringBuffer sb= new StringBuffer();
          while (st.hasMoreTokens()) {
            String cNs = st.nextToken();
            if (cNs.equals(ns)) continue;
            if (sb.length()>0) sb.append(',');
            sb.append(cNs);
          }
          String sVal = sb.toString();
          w98NameServer = sVal;
        }else if (oldNameServer != null && oldNameServer.indexOf(ns) < 0) {
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
            RegStringValue rval = new RegStringValue(ifc, "NameServer",
                newValue);
            ifc.setValue(rval);
          }
        }
      }catch(RegistryException e) {}
      ifc.closeKey();
      hkeyLocal.closeKey();
      registerDNS98();
      log.println("DNS started");
      restored = false;
  }

  /**
   * Restore settings for DNS
   *
   * @param e
   */
  public synchronized void restoreNameServer(){
    if (restored) return;
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
        System.err.println("Not supported OS:" + osName + "/" + osVersion);
      }
    }catch(Exception e){}
  }

  /**
   * Restore settings for DNS
   *
   * @param e
   */
  public void restoreNameServerNT() throws Exception{
      com.ice.jni.registry.Registry reg = new Registry();
      RegistryKey hkeyLocal = Registry.HKEY_LOCAL_MACHINE;
      RegistryKey interfaces = hkeyLocal.openSubKey(interfacesStr,
          RegistryKey.ACCESS_ALL);
      int numInterfaces = interfaces.getNumberSubkeys();
      for (int i=0;i<numInterfaces;i++) {
        String key = interfaces.regEnumKey(i);
        if (key==null) continue;
        if (!saved.containsKey(key)) continue;
        RegistryKey ifc = interfaces.openSubKey(key, RegistryKey.ACCESS_ALL);
        try {
          String oldNameServer = ifc.getStringValue("NameServer");
          // get old value and restore it
          String sVal = (String) saved.get(key);
          RegStringValue rval = new RegStringValue(ifc, "NameServer",
              sVal);
          if (rval==null) {
             rval = new RegStringValue(ifc,"NameServer","");
          }
          ifc.setValue(rval);
        }catch(RegistryException e){}
        ifc.closeKey();
      }
      interfaces.closeKey();
      hkeyLocal.closeKey();
      registerDNSNT();
      restored = true;
  }

  /**
   * Restore settings for DNS
   *
   * @param e
   */
  public void restoreNameServer98() throws Exception{
      if (w98NameServer==null) return;
      com.ice.jni.registry.Registry reg = new Registry();
      RegistryKey hkeyLocal = Registry.HKEY_LOCAL_MACHINE;
      RegistryKey ifc = hkeyLocal.openSubKey(w98,
          RegistryKey.ACCESS_ALL);
      try {
        String oldNameServer = ifc.getStringValue("NameServer");
        RegStringValue rval = new RegStringValue(ifc, "NameServer",
            w98NameServer);
        if (rval==null) {
          rval = new RegStringValue(ifc,"NameServer","");
        }
        ifc.setValue(rval);
      }catch(RegistryException e) {}
      ifc.closeKey();
      hkeyLocal.closeKey();
      registerDNS98();
      restored = true;
  }

/**
 * Call native command to refresh DNS records
 */
private static void registerDNSNT(){
  try {
    Runtime.getRuntime().exec("ipconfig /registerdns");
  }catch(Exception e){
    e.printStackTrace();
  }
}

/**
 * Call native command to refresh DNS records on W98/Me
 */
private static void registerDNS98(){
  try {
    Runtime.getRuntime().exec("ipconfig /renew_all");
  }catch(Exception e){
    e.printStackTrace();
  }
}

private void downloadLibrary(String fileName) throws Exception {
  // try to create a file
    File f = new File(fileName);
    if (f.exists()) {
      f.delete();
    }
    FileOutputStream fos = new FileOutputStream(f);

    if (cfg.libraryURL==null) {
      throw new Exception("Library URL is null");
    }

    //HttpTimeoutHandler xHTH = new HttpTimeoutHandler(30000);	// timeout value in milliseconds
    //URL u = new URL((URL)null, parent.libraryUrl, xHTH);
    //HttpURLConnection huc = (HttpURLConnection) u.openConnection();

    URL u = new URL(cfg.libraryURL);
    HttpURLConnection huc = (HttpURLConnection) u.openConnection();
    huc.setRequestMethod("GET");
    huc.connect();
    InputStream is = huc.getInputStream();
    int code = huc.getResponseCode();
    if (code >= 200 && code < 300) {
      byte[] buf = new byte[2400];
      int l = 0;
      while ((l = is.read(buf))>0) {
        fos.write(buf,0,l);
      }
    }
    fos.close();
    huc.disconnect();
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
