// Copyright 2003 Adam Megacz, see the COPYING file for licensing [LGPL]
package org.xwt.util;
import java.io.*;
import java.util.*;

/** easy to use logger */
public class Log {

    public static boolean on = false;
    public static boolean verbose = false;
    public static boolean logDates = false;
    public static Date lastDate = null;

    /** true iff nothing has yet been logged */
    public static boolean firstMessage = true;

    /** message can be a String or a Throwable */
    public static synchronized void log(Object o, Object message) {
        if (firstMessage && !logDates) {
            firstMessage = false;
            System.err.println("===========================================================================");
            log(Log.class, "Logging enabled at " + new java.util.Date());
        }

        String classname;
        if (o instanceof Class) classname = ((Class)o).getName();
        else if (o instanceof String) classname = (String)o;
        else classname = o.getClass().getName();

        if (classname.indexOf('.') != -1) classname = classname.substring(classname.lastIndexOf('.') + 1);
        if (classname.length() > (logDates ? 14 : 20)) classname = classname.substring(0, (logDates ? 14 : 20));
        while (classname.length() < (logDates ? 14 : 20)) classname = " " + classname;
        classname = classname + ": ";

        if (logDates) {
            Date d = new Date();
            if (lastDate == null || d.getYear() != lastDate.getYear() || d.getMonth() != lastDate.getMonth() || d.getDay() != lastDate.getDay()) {
                String now = new java.text.SimpleDateFormat("EEE dd MMM yyyy").format(d);
                System.err.println();
                System.err.println("=== " + now + " ==========================================================");
            }
            java.text.DateFormat df = new java.text.SimpleDateFormat("[EEE HH:mm:ss] ");
            classname = df.format(d) + classname;
            lastDate = d;
        }

        if (!(message instanceof Throwable)) System.err.println(classname + message);
        else {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ((Throwable)message).printStackTrace(new PrintStream(baos));
            byte[] b = baos.toByteArray();
            BufferedReader br = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(b)));
            String s = null;
            try {
                while((s = br.readLine()) != null) {
                    System.err.print(classname);
                    for(int i=0; i<s.length(); i++)
                        System.err.print(s.charAt(i) == '\t' ? "    " : ("" + s.charAt(i)));
                    System.err.println();
                }
            } catch (Exception e) { }

        }
    }
}
