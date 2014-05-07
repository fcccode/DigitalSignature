// This is the applet, however working logic should be outside of this class.
// In my example it is in the WorkerThread which is loaded by start().
//
//

import java.applet.*;

public class XMLSignApplet extends Applet {
  private WorkerThread wt = null;
  public static final String version = "1.00.0000";
  boolean isStarted=false;

  //Construct the applet
  public XMLSignApplet() {
  }

  //Initialize the applet
  public void init() {
  }

  //Start the applet
  // workaround for MS - to prevent security exception init() and start() must not contain
  // dangerous code. That is why we run thread instead.
  public void start() {
      wt = new WorkerThread(this);
      wt.start();
      isStarted=true;
  }

  //Stop the applet
  public void stop() {
    if (wt!=null) {
      wt.stopThread();
      try {
        wt.join();
      }
      catch (Exception e) {}
      wt = null;
      isStarted=false;
    }
  }

  //Destroy the applet
  public void destroy() {
    if (wt!=null) {
      wt.stopThread();
      try {
        wt.join();
      }
      catch (Exception e) {}
      wt = null;
    }
  }
  //Get Applet information
  public String getAppletInfo() {
    return "XMLSignApplet v1.0. Copyright Infomosaic, Inc. 2000-2004. All rights reserved.";
  }

  public String getVersion(){
    return version;
  }

}
