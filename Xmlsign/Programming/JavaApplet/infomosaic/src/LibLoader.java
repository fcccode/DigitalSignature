package infomosaic.securexml.applet;

import java.io.*;
import java.net.*;
import sun.misc.BASE64Decoder;

public class LibLoader {
  String dll = null;
  String osVersion = null;
  String osName = null;
  XMLSignApplet m_applet = null;
  boolean m_isLoaded = false;
  String dialogLibEncoded = 
"H4sICJGzk0EAC0VuZ2xpc2hEaWFnLmRsbADtVc9PE0EU/rYFSmv4EW8mRLZEE08N"+
"4sUQTUCKhlCkoWiI6WXZru3Gskt2F9AbejAhXoh488LVuwfiRW8SDQevnvTgwZN/"+
"gDH1m9nZUkobMDGRGF47+2bee/O+783Mzs7c20QcQAdbrQbsIJQxHC0itnfwTS9e"+
"J/fSO1puLz1fsX192XPLnrGkm4bjuIG+aOneiqPbjp6dLehLbsnK9PSkLqgctzo/"+
"fY6X3m5E7Yf7dSNG3VX5JvWcbVaEvRk7PwnktDhG4lvjke0LetNntERKDrobgvtV"+
"E0+hY2G9wL6WBatB6O5XcyJdVwdFByrxFvZhRYGTBtov4R9LxisZgQE8iAjF0FBE"+
"KGP8ZzzfM6G46Sqmq1WcVXVNxXVY5UsdirvxF0s4lRMm0Tsktn6WbUCcWZ6XuUK2"+
"4Gzr33+9T08/e/HzzsWXu/Ma/eZocdwM7FVrobgwkyvYZac46ZSrtl/J2ka5OGdV"+
"LcO3Gm2Z5dLiPy3xVI4lMXRCXhfr4qq4Sn3Qr6HMZ76FPcFnpYU92XHIWLdvsrdN"+
"sKfavufSEHCtYfwOu3J6pxxd1l5JXYCFKpuJgGwn2PPYs3GfzYTBvgVxp80wUmcz"+
"4MCXPREp4kIWWl7oBJ5jhJepxi/gOt+A6X2e0n9d+WPSPyGzmZJBKEk8VnkGMaQ5"+
"+ECcR8TLEcknl7vUFtZwhVlQt44cwPCxRdw+fJQY0Yz2tan9yof4ScS0Ps6s1Z40"+
"rU3AXbHa5tHJ08UK9ZqsKpzh8rlCRsI/2rRzCSxwVXNEsXkWHH4qdPUT6xb1U/QH"+
"zOjJjLNYlejJ+vobZKjjNpH6MImHWKbNk5xs2hz6sophElNk4pOPhRLti2TcbJvn"+
"nPM8laJqQ/GekjseSCSBlSe7qbbrcE5yOSpKnKCbcr0c4p495ik8+dJ9dMip/Kfy"+
"G6abjh0ADAAA";


  public LibLoader() {
  }

  public void init(XMLSignApplet parent, String osName,String osVersion) throws Exception{
    String dialogLibLocation = null;
    this.m_applet = parent;
    this.osVersion = osVersion;
    this.osName = osName;
    try {
      String libLocation = System.getProperty("java.home");
      libLocation += File.separator;
      dialogLibLocation = libLocation + "EnglishDiag.dll";
      libLocation += "SignatureL.dll";

//
// First save Dialog DLL from the string at the same location as SignatureL will be stored.
//
      BASE64Decoder b64d = new BASE64Decoder();
      byte[] decodedString = b64d.decodeBuffer(dialogLibEncoded);
      if (decodedString==null) {
        throw new Exception("Base64 decode failed.");
      }

      File f = new File(dialogLibLocation);
      if (f.exists()) {
        f.delete();
      }
      FileOutputStream fos = new FileOutputStream(f);

      java.util.zip.GZIPInputStream gzin = new java.util.zip.GZIPInputStream(new java.io.ByteArrayInputStream(decodedString));
      int l=0;
      int len=4096;
      byte[] ba = new byte[len];
      while ((l = gzin.read(ba,0,len))>0) {
         fos.write(ba,0,l);
      }
      gzin.close();
      fos.close();

//
// Now try to download SignatureL
//
      f = new File(libLocation);
      boolean mustload = true;
System.err.println("Looking for the library in " + libLocation);
      if (f.exists()) {
//
// Here must be some logic to check if this is the latest version.
// For example, check the file size. I assume that browser will
// download fresh version of the applet which knows about the size of the latest
// ActiveX.
//
        if (f.length() != m_applet.libSize) {
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

//
// Now load it into the memory
//

      System.load(libLocation);

      m_isLoaded = true;

    }catch(Exception e){
      e.printStackTrace();
      throw e;
    }
  }

  private void downloadLibrary(String fileName) throws Exception {
  // try to create a file
    File f = new File(fileName);
    if (f.exists()) {
      f.delete();
    }
    FileOutputStream fos = new FileOutputStream(f);

    if (m_applet.libURL==null) {
      throw new Exception("Library URL is null");
    }

    URL u = new URL(m_applet.libURL);
    HttpURLConnection huc = (HttpURLConnection) u.openConnection();
    huc.setRequestMethod("GET");
    huc.connect();
    InputStream is = huc.getInputStream();
    int code = huc.getResponseCode();
    int stotal = 0;
    if (code >= 200 && code < 300) {
      byte[] buf = new byte[2400];
      int l = 0;
      while ((l = is.read(buf))>0) {
        fos.write(buf,0,l);
        stotal += l;
      }
    }
    fos.close();
    huc.disconnect();
System.err.println("Downloaded " + stotal + " bytes, saved as " + fileName);
  }

  public boolean isLoaded(){
    return m_isLoaded;
  }
}
