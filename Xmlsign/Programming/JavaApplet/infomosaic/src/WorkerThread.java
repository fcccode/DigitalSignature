// Initiate working process here, in run() after you load the library.
//
//
//
import java.io.*;

public class WorkerThread
    extends Thread {
  private boolean keepAlive = true;
  private boolean processFailed = false;
  private XMLSignApplet parent = null;
  private LibLoader lloader = null;

  public WorkerThread(XMLSignApplet applet) {
    this.parent = applet;
  }

  public void run() {
    try {
      String s = System.getProperty("java.vendor");
      String osName = System.getProperty("os.name");
      String osVersion = System.getProperty("os.version");
      if (s.indexOf("Microsoft") >= 0){
        // IE plus MS JVM - that's our boy. Load the library.
        lloader = new LibLoader();
        lloader.init(osName, osVersion);
      }
      else {
        // SUN JVM on Windows - we can do it as well
        if (osName.startsWith("Windows")) {
	  lloader = new LibLoader();
          lloader.init(osName, osVersion);
        }else if(osName.toLowerCase().startsWith("linux")){
          // Linux - don't care
          throw new IOException("Unsupported OS: " + osName);
        }else{
          // Could be Mac or something else
          throw new IOException("Unsupported OS: " + osName);
        }
      }

      // start your working process here. In AreaBe example it was DNS server and listeners.
      // ...........

      // get into the loop until applet is terminated or process failed
      while (keepAlive && !processFailed) {
        try {
          synchronized (this) {
            this.wait();
          }
        }
        catch (Exception ie) {}
      }
    }
    catch (Exception e) {
      e.printStackTrace();
    }
    finally {
      // stop process
      stopThread();
    }
  }


  /**
   * The process when is done should call this method.
   * This method must not have any unsafe code i.e. work with Registry or file system.
   */
  public synchronized void stopThread() {
    // this is to stop current thread
    if (!keepAlive)
      return; // this code already been executed
    keepAlive = false;

    // do something here to finish any working threads (if any remain)
    // ......

    synchronized (this) {
      try {
        this.notifyAll();
      }
      catch (Exception e) {}
    }
  }
}
