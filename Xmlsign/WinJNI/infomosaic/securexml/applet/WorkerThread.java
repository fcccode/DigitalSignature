//
// Detects OS and loads corresponding library.
//
package infomosaic.securexml.applet;

import java.io.*;

public class WorkerThread
    extends Thread {
  private XMLSignApplet parent = null;
  private LibLoader lloader = null;

  public WorkerThread(XMLSignApplet applet) {
    this.parent = applet;
  }

	public void loadCacLib()
	{
		try
		{
			System.gc();
			System.load(lloader.cacLibLocation);
		}
		catch (Throwable e)
		{
			e.printStackTrace();
		}
	}

  public void run() {
    try {
      String s = System.getProperty("java.vendor");
      String osName = System.getProperty("os.name");
      String osVersion = System.getProperty("os.version");
      if (s.indexOf("Microsoft") >= 0){
        // IE plus MS JVM - that's our boy. Load the library.
        lloader = new LibLoader();
        lloader.init(parent, osName, osVersion);
      }
      else {
        // SUN JVM on Windows - we can do it as well
        if (osName.startsWith("Windows")) {
	  lloader = new LibLoader();
          lloader.init(parent, osName, osVersion);
        }else if(osName.toLowerCase().startsWith("linux")){
          // Linux - don't care
          throw new IOException("Unsupported OS: " + osName);
        }else{
          // Could be Mac or something else
          throw new IOException("Unsupported OS: " + osName);
        }
      }

      if (lloader.isLoaded()) {
         parent.initSignature();
      }
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }
}
