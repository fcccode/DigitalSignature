package com.areabe.easyaccess.gui;

import java.awt.*;
import java.io.IOException;
import java.io.InputStream;

public class AWTHelper
{
    public static void waitForImage0(Component component, String s, Image image)
        throws AWTException
    {
        component.prepareImage(image, component);
        char c = '\240';
        int cnt=0;
        int i;
        while(((i = component.checkImage(image, component) & c) == 0) && cnt<600) {
          try {
            Thread.sleep(100L);
          }
          catch (InterruptedException _ex) {}
          cnt++;
        }
        if((i & 0x20) == 0)
            throw new AWTException("Failed to load image \"" + s + "\"");
        else
            return;
    }

    public AWTHelper()
    {
    }

    public static Image getImage(String s) throws AWTException{
      try {
        Image img = null;
        java.net.URL url = (com.areabe.easyaccess.gui.AWTHelper.class).
            getResource(s);
        img = Toolkit.getDefaultToolkit().createImage( (java.awt.image.
            ImageProducer) url.getContent());
        return img;
      }catch(Exception e) {
        throw new AWTException("Failed to load image \"" + s + "\"");
      }
    }

    public static void waitForImage(Component component, String s, Image image)
        throws AWTException {
      try {
        MediaTracker mt = new MediaTracker(component);
        mt.addImage(image,0);
        mt.waitForID(0,60000);
      }catch(Exception e) {
        throw new AWTException("Failed to load image \"" + s + "\": " + e.getMessage());
      }
    }
}
