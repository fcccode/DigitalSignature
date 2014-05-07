package infomosaic.securexml.applet;

import java.applet.*;
import infomosaic.securexml.SignatureImpl;
import infomosaic.securexml.SmartcardImpl;
import java.net.URL;

public class XMLSignApplet extends Applet {
  private WorkerThread wt = null;
  public static final String version = "1.00.0000";
  private SignatureImpl sigObj = null;
  private SmartcardImpl cacObj = null;
  Class jsObjectClass = null;  

  //Construct the applet
  public XMLSignApplet() {
	  System.gc();
  }

  //Initialize the applet
  public void init() {
      // disable links
      try {
        jsObjectClass = Class.forName("netscape.javascript.JSObject");
      } catch(ClassNotFoundException e) {
        jsObjectClass = null;
      }

      disableLinks();
	  System.gc();
  }

  //Start the applet
  // workaround for MS - to prevent security exception init() and start() must not contain
  // dangerous code. That is why we run thread instead.
  public void start() {
	  System.gc();
	  wt = new WorkerThread(this);
      wt.start();
		try 
		{
			wt.join();  // we only wait for this thread to load the library
		}
		catch(Exception e)
		{
		}

      if (sigObj==null) {
         System.err.println("Library wasn't loaded - exiting");
      }else{
         enableLinks();
      }
  }

  //Stop the applet
  public void stop() {
	  System.gc();
  }

  //Destroy the applet
  public void destroy() {
    if (sigObj != null) sigObj.destroy();
    sigObj = null;
	System.gc();
  }

  //Get Applet information
  public String getAppletInfo() {
    return "SecureXML Java Applet XMLSignApplet v1.0. Copyright (c) Infomosaic Corporation. 2004-2005. All rights reserved.";
  }

  public String getVersion(){
    return version;
  }

  public SignatureImpl getSignature(){
    return sigObj;
  }

  public SmartcardImpl getSmartcard()
  {
	  try
	  {
		  if (cacObj != null)
		  {
			  cacObj.destroy();
		  }
//		  else
//		  {
//			  wt.loadCacLib();
//			  try
//			  {
//				  wt.join();
//			  }
//			  catch (Throwable e)
//			  {
//				  Thread.sleep(300);
//				  e.printStackTrace();
//			  }
//		  }
	  }
	  catch (Exception e)
	  {
		  e.printStackTrace();
	  }
	  cacObj = new SmartcardImpl();
      return cacObj;
  }

  public void initSignature() throws Exception
  {
    sigObj = new SignatureImpl();
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

