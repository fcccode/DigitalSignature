package com.areabe.easyaccess.gui;
import java.io.PrintStream;
import java.io.PrintWriter;

public class AWTException extends Exception
{

    public AWTException(String s)
    {
        b = s;
    }

    public String getMessage()
    {
        StringBuffer stringbuffer = new StringBuffer();
        if(b != null)
            stringbuffer.append(b);
        if(c != null)
        {
            if(stringbuffer.length() > 0)
                stringbuffer.append(": ");
            stringbuffer.append(c.getMessage());
        }
        return stringbuffer.toString();
    }

    public String toString()
    {
        StringBuffer stringbuffer = new StringBuffer();
        stringbuffer.append(super.toString());
        if(c != null)
        {
            stringbuffer.append(": ");
            stringbuffer.append(c.toString());
        }
        return stringbuffer.toString();
    }

    public void printStackTrace(PrintWriter printwriter)
    {
        if(c != null)
        {
            c.printStackTrace(printwriter);
            return;
        } else
        {
            super.printStackTrace(printwriter);
            return;
        }
    }

    public void printStackTrace(PrintStream printstream)
    {
        if(c != null)
        {
            c.printStackTrace(printstream);
            return;
        } else
        {
            super.printStackTrace(printstream);
            return;
        }
    }

    private final int a = 1;
    private final String b;
    private final Exception c = null;
}
