package infomosaic.securexml.applet;

import java.applet.*;
import infomosaic.securexml.Signature;
import java.net.URL;

public class XMLSignApplet extends Applet {
  private WorkerThread wt = null;
  public static final String version = "1.00.0000";
  private Signature sigObj = null;
  public String libURL = null;
  public int libSize = 0;
  Class jsObjectClass = null;  

  //Construct the applet
  public XMLSignApplet() {
  }

  //Initialize the applet
  public void init() {
      libURL = this.getParameter("LIBURL", null);
      String sLibSize = this.getParameter("LIBSIZE", "0");
      libSize = Integer.parseInt(sLibSize);
      // disable links
      try {
        jsObjectClass = Class.forName("netscape.javascript.JSObject");
      } catch(ClassNotFoundException e) {
        jsObjectClass = null;
      }

      disableLinks();
  }

  //Start the applet
  // workaround for MS - to prevent security exception init() and start() must not contain
  // dangerous code. That is why we run thread instead.
  public void start() {
      wt = new WorkerThread(this);
      wt.start();
      try {
         wt.join();  // we only wait for this thread to load the library
      }catch(Exception e){}

      if (sigObj==null) {
         System.err.println("Library wasn't loaded - exiting");
      }else{
         enableLinks();
      }
  }

  //Stop the applet
  public void stop() {
  }

  //Destroy the applet
  public void destroy() {
    if (sigObj != null) sigObj.destroy();
    sigObj = null;
  }

  //Get Applet information
  public String getAppletInfo() {
    return "XMLSignApplet v1.0. Copyright Infomosaic, Inc. 2000-2004. All rights reserved.";
  }

  public String getVersion(){
    return version;
  }

  public Signature getSignature(){
    return sigObj;
  }

  public void initSignature() throws Exception{
    sigObj = new Signature();
  }

  //Get a parameter value
  public String getParameter(String key, String def) {
    return (getParameter(key) != null) ? getParameter(key) : def;
  }

  private void disableLinks() {
    try {
      if (jsObjectClass != null) {
        netscape.javascript.JSObject window;

        window = netscape.javascript.JSObject.getWindow(this);
        window = (netscape.javascript.JSObject) window.getMember("top");
        window.eval("disableLinks();");
      }
      else {
        URL url = new URL("javascript:top.disableLinks();");
        getAppletContext().showDocument(url);
      }
    }catch(Exception e){
        e.printStackTrace();
        System.err.println("Scripting from Applet is not supported");
    }
  }

  private void enableLinks() {
    try {
      if (jsObjectClass != null) {
        netscape.javascript.JSObject window;

        window = netscape.javascript.JSObject.getWindow(this);
        window = (netscape.javascript.JSObject) window.getMember("top");
        window.eval("enableLinks();");
      }
      else {
        URL url = new URL("javascript:top.enableLinks();");
        getAppletContext().showDocument(url);
      }
    }catch(Exception e){
        e.printStackTrace();
        System.err.println("Scripting from Applet is not supported");
    }
  }

}

