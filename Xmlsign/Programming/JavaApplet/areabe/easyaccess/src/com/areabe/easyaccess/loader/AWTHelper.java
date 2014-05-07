package com.areabe.easyaccess.loader;

import java.awt.*;
import java.io.IOException;
import java.io.InputStream;

public class AWTHelper
{

    public static Image getImage(String s)
        throws AWTException
    {
        String s1 = System.getProperty("java.vendor");
        if(s1.indexOf("Netscape") >= 0)
        {
            try
            {
                InputStream inputstream = (com.areabe.easyaccess.loader.AWTHelper.class).getResourceAsStream(s);
                if(inputstream == null)
                {
                    throw new AWTException("Image \"" + s + "\" not found");
                } else
                {
                    byte abyte0[] = new byte[inputstream.available()];
                    inputstream.read(abyte0);
                    return Toolkit.getDefaultToolkit().createImage(abyte0);
                }
            }
            catch(IOException _ex)
            {
                throw new AWTException("Unable to load image \"" + s + "\"");
            }
        } else
        {
            java.net.URL url = (com.areabe.easyaccess.loader.AWTHelper.class).getResource(s);
            return Toolkit.getDefaultToolkit().getImage(url);
        }
    }

    public static void waitForImage(Component component, String s, Image image)
        throws AWTException
    {
        component.prepareImage(image, component);
        char c = '\240';
        int i;
        while((i = component.checkImage(image, component) & c) == 0)
            try
            {
                Thread.sleep(50L);
            }
            catch(InterruptedException _ex) { }
        if((i & 0x20) == 0)
            throw new AWTException("Failed to load image \"" + s + "\"");
        else
            return;
    }

    public AWTHelper()
    {
    }
}
