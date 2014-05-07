package com.areabe.easyaccess.loader;

import java.applet.Applet;
import java.awt.*;
import java.io.PrintStream;
import com.areabe.easyaccess.locale.Resources;

public class AppletLoader
    extends Applet {
  private Image b;
  private Dimension d;

  public void init() {
    Resources.initResourceBundle();
    Resources resources = Resources.getInstance();
    d = new Dimension(25, 90);
    try {
      String s = resources.getString("SPLASH_PROGRESS_IMG");
      b = AWTHelper.getImage(s);
      AWTHelper.waitForImage(this, s, b);
      return;
    }
    catch (Exception exception) {
      System.err.println("ERROR: " + exception.toString());
      exception.printStackTrace();
      return;
    }
  }

  public String getAppletInfo() {
    return
        "EasyAccess Loader. Copyright 2004 AreaBe, Inc. All rights reserved.";
  }

  public String[][] getParameterInfo() {
    return a;
  }

  public void start() {
    LoaderThread lt = new LoaderThread(this, 2);
    lt.start();
  }

  public void stop() {
  }

  public void paint(Graphics g) {
    update(g);
  }

  public void update(Graphics g) {
    if (b != null)
      g.drawImage(b, 0, 0, this);
  }

  public boolean imageUpdate(Image image, int i, int j, int k, int l, int i1) {
    return super.imageUpdate(image, i, j, k, l, i1);
  }

  public AppletLoader() {
  }

  private static final String a[][] = {
      {
      "SUN-WINDOWS", "String", "Sun JVM applet (Windows)"
  } ,
      {
      "SUN-LINUX", "String", "Sun JVM applet (Linux)"
  }
      , {
      "MS", "String", "Microsoft JVM applet"
  }
      , {
      "resources", "String", "class name of ResourceBundle to use"
  }
  };
}
