package com.areabe.easyaccess.loader;
import com.areabe.easyaccess.loader.AppletLoader;
import java.applet.Applet;
import java.applet.AppletContext;
import java.io.PrintStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class LoaderThread extends Thread
{

    public LoaderThread(Applet applet, int i)
    {
        c = applet;
        b = i;
    }

    public void run()
    {
        AppletContext appletcontext = c.getAppletContext();
        URL url = c.getDocumentBase();
        String s = System.getProperty("java.vendor");
        String s1 = System.getProperty("java.version");
        String osName = System.getProperty("os.name");
        String osVersion = System.getProperty("os.version");
        String s2 = null;
        if(s.indexOf("Microsoft") >= 0)
            s2 = "MS";
        else {
          if (osName.startsWith("Windows")) {
            s2 = "SUN-WINDOWS";
          }else if(osName.toLowerCase().startsWith("linux")){
            s2 = "SUN-LINUX";
          }else{
            s2 = "SUN-LINUX"; // assume it is Unix-like system
          }
        }

        String s3 = c.getParameter(s2);
        if(s3 == null)
            s3 = "<empty>";
        try
        {
            if(b > 0)
                Thread.sleep(b * 1000);
            appletcontext.showDocument(new URL(url, s3), "_self");
            return;
        }
        catch(MalformedURLException _ex)
        {
            System.err.println("ERROR: Badly formed redirection URL \"" + s3 + "\"");
        }
        catch(InterruptedException _ex)
        {
            return;
        }
    }

    private final int b;
    private final Applet c;
}
