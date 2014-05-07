package com.areabe.easyaccess;

import java.util.*;
import java.io.*;

public class Config {

  /*
   * TCP protocol type
   */

  public static final int UNKNOWN = 0;
  public static final int HTTP = 1;
  public static final int GENERIC_SMP = 2;
  public static final int FTP = 3;
  public static final int FTP_DATA = 9999;
  public static final int TNS = 4;
  public Hashtable dns = new Hashtable(); // key = SOA host name, value = IP
  public Hashtable tcpPorts = new Hashtable(); // key = port, value = IP to bind with

//  public Hashtable realHost = new Hashtable(); // key = fake hostname, value = hostname to connect
  public Hashtable origHost = new Hashtable(); // key = fake hostname, value = hostname to use in "Host" header
  private Hashtable portType = new Hashtable(); // key = port, value = protocol type
  private static Config thisConfig = null;
  public static boolean debug = false;
  private Log log = Log.getInstance();
  public String libraryURL = null;
  private String sesid = null;
  private String swanstor = null;
  private boolean sslMode = false;
  private String portalFingerprint = null;

  public String gwHost = null;
  public int gwPort = 0;

  public static Config getInstance() {
    return thisConfig;
  }

  public static boolean initConfig(String cfg) {
    try {
      System.err.println("New configuration applied.");
      thisConfig = new Config(cfg);
      return true;
    }
    catch (Exception e) {
      return false;
    }
  }

  private Config(String cfg) throws Exception {
    try {
      Hashtable hosts = new Hashtable();
      StringReader sr = new StringReader(cfg);
      LineNumberReader reader = new LineNumberReader(sr);
      String line;
      StringTokenizer st = null;
      int section = 0;
      String pName = null;
      String pValue = null;

      while ( (line = reader.readLine()) != null) {
        if (line.startsWith("#"))continue;
        if (line.length() == 0)continue;

        if (line.equalsIgnoreCase("[HTTP_PORTS]")) {
          section = 1;
        }
        else if (line.equalsIgnoreCase("[HOSTS]")) {
          section = 2;
        }
        else if (line.equalsIgnoreCase("[OTHER]")) {
          section = 3;
        }
        else {
          st = new StringTokenizer(line, "=");
          switch (section) {
            case 1:

              // add http port
              String param = st.nextToken();
              String sPort = (String) st.nextToken();
              tcpPorts.put(sPort, "127.0.0.1");
              portType.put(sPort, String.valueOf(HTTP));
              break;
            case 2:

              // parse host section
              pName = st.nextToken().toLowerCase();
              pValue = null;
              try {
                pValue = st.nextToken().toLowerCase();
              }
              catch (Exception e) {}
              if (pName.startsWith("type")) {
                String snum = pName.substring(4).trim();
                String[] hCfg = null;
                if (hosts.containsKey(snum)) {
                  hCfg = (String[]) hosts.get(snum);
                }
                else {
                  hCfg = new String[6];
                }
                if (pValue != null) hCfg[0] = new String(pValue);
                hosts.put(snum, hCfg);
              }
              else if (pName.startsWith("host")) {
                String snum = pName.substring(4).trim();
                String[] hCfg = null;
                if (hosts.containsKey(snum)) {
                  hCfg = (String[]) hosts.get(snum);
                }
                else {
                  hCfg = new String[6];
                }
                if (pValue != null) hCfg[1] = new String(pValue);
                hosts.put(snum, hCfg);
              }
              else if (pName.startsWith("ip")) {
                String snum = pName.substring(2).trim();
                String[] hCfg = null;
                if (hosts.containsKey(snum)) {
                  hCfg = (String[]) hosts.get(snum);
                }
                else {
                  hCfg = new String[6];
                }
                if (pValue != null) hCfg[2] = new String(pValue);
                hosts.put(snum, hCfg);
              }
              else if (pName.startsWith("port")) {
                String snum = pName.substring(4).trim();
                String[] hCfg = null;
                if (hosts.containsKey(snum)) {
                  hCfg = (String[]) hosts.get(snum);
                }
                else {
                  hCfg = new String[6];
                }
                if (pValue != null) hCfg[3] = new String(pValue);
                hosts.put(snum, hCfg);
              }
              else if (pName.startsWith("orighost")) {
                String snum = pName.substring(8).trim();
                String[] hCfg = null;
                if (hosts.containsKey(snum)) {
                  hCfg = (String[]) hosts.get(snum);
                }
                else {
                  hCfg = new String[6];
                }
                if (pValue != null) hCfg[4] = new String(pValue);
                hosts.put(snum, hCfg);
              }
              else {
                log.println("Config: unknown line in config file: " + line);
              }
              break;
            case 3:
              // other settings. Do not use StringTokenizer because base64 could have "=" chars
              int i = line.indexOf('=');
              if (i <= 0)continue;
              pName = line.substring(0,i).toLowerCase();
              pValue = line.substring(i+1);

              if (pName.toLowerCase().equals("registry_dll_url") && pValue != null) {
                libraryURL = pValue;
              }
              else if (pName.toLowerCase().equals("session_id") && pValue != null) {
                sesid = pValue;
              }
              else if (pName.toLowerCase().equals("server") && pValue != null) {
                swanstor = pValue;
              }
              else if (pName.toLowerCase().equals("portal") && pValue != null) {
                gwHost = pValue;
              }
              else if (pName.toLowerCase().equals("ssl") && pValue != null) {
                setSSLMode(pValue.equalsIgnoreCase("on"));
              }
              else if (pName.toLowerCase().equals("port") && pValue != null) {
                gwPort = Integer.parseInt(pValue);
              }
              else if (pName.toLowerCase().equals("portal_ssl_fingerprint") &&
                       pValue != null) {
                portalFingerprint = pValue;
              }

              break;
            default:
              log.println("Config: unknown section in config file: " + line);
          }
        }
      }

      // now work with hosts
      Enumeration en = hosts.keys();
      while (en.hasMoreElements()) {
        String snum = (String) en.nextElement();
        String[] sval = (String[]) hosts.get(snum);
        if (sval[1] != null && sval[0] != null) {
          if (sval[0].equals("http")) {
            // in case if sval[1] is multiple value
            String val = sval[1]; // fake hosts
            String val1 = sval[4]; // original hosts
            if (val.indexOf(',') > 0) {
              StringTokenizer stk0 = new StringTokenizer(val, ",");
              StringTokenizer stk1 = new StringTokenizer(val1, ",");
              if (stk0.countTokens() != stk1.countTokens())throw new
                  IOException(
                  "Number of fake names not equival to the number of original names for host: " +
                  sval[4]);
              while (stk0.hasMoreTokens()) {
                val = stk0.nextToken();
                val1 = stk1.nextToken();
                dns.put(val, "127.0.0.1");
                origHost.put(val, val1.toLowerCase());
                log.println("Addedd name rule: " + val + " -> " + val1);
              }
            }
            else {
              dns.put(val, "127.0.0.1");
              origHost.put(val, val1.toLowerCase());
              log.println("Addedd name rule: " + val + " -> " + val1);
            }
          }
          else {
            if (sval[2] == null) sval[2] = "127.0.0.1";
            dns.put(sval[1], sval[2]);
            if (sval[3] != null) {
              tcpPorts.put(sval[3], sval[2]);
              int stype = parseType(sval[0]);
              portType.put(sval[3], String.valueOf(stype));
            }
          }
        }
      }

      if (tcpPorts.size() == 0 || portType.size() == 0 || dns.size() == 0) {
        throw new Exception("Empty configuration");
      }

    }
    catch (Exception e) {
      log.println("Bad configuration: " + cfg);
      if (debug) {
        System.out.println("Bad configuration: " + e.getMessage());
        e.printStackTrace();
      }
      throw e;
    }
  }

  /**
   * Translate string type into integer: "http"=1, ...
   * @param stype
   * @return
   */
  private int parseType(String stype) {
    if (stype == null)return UNKNOWN;
    if (stype.toLowerCase().equals("http")) {
      return HTTP;
    }
    else if (stype.toLowerCase().equals("smp-generic")) {
      return GENERIC_SMP;
    }
    else if (stype.toLowerCase().equals("smp-ftp")) {
      return FTP;
    }
    else if (stype.toLowerCase().equals("smp-tns")) {
      return TNS;
    }
    else {
      log.println("Unknown protocol type: " + stype);
      return UNKNOWN;
    }
  }

  /**
   * By given port returns type of expected protocol
   *
   * @param port
   * @return
   */
  public int getPortType(int port) {
    if (portType.containsKey(String.valueOf(port))) {
      String sPortType = portType.get(String.valueOf(port)).toString();
      try {
        return Integer.parseInt(sPortType);
      }
      catch (Exception e) {
        return UNKNOWN;
      }
    }
    else {
      //log.println("No type specified for the port: " + port);
      return UNKNOWN;
    }
  }

  public static String getProtocolName(int protocol) {
    switch (protocol) {
      case UNKNOWN:
        return "UNKNOWN";
      case HTTP:
        return "HTTP";
      case GENERIC_SMP:
        return "SMP";
      case FTP:
        return "FTP";
      case FTP_DATA:
        return "FTP (Data)";
      case TNS:
        return "Oracle TNS";
      default:
        return "Unknown";
    }
  }

  public static void setDebug(boolean val) {
    debug = val;
  }

  /**
   * get session ID
   * @return
   */
  public String getSessionID() {
    return sesid;
  }

  /**
   * Get SWANStor server name
   * @return
   */
  public String getServerName() {
    return swanstor;
  }

  public void setSSLMode(boolean val) {
    sslMode = val;
  }

  public boolean isSSLMode() {
    return sslMode;
  }

  public static void main(String[] args) throws Exception {
    File f = new File("config.txt");
    FileInputStream fis = new FileInputStream(f);
    byte[] b = new byte[ (int) f.length()];
    fis.read(b);
    fis.close();
    Config.initConfig(new String(b));
    Config cfg = Config.getInstance();
  }
}
