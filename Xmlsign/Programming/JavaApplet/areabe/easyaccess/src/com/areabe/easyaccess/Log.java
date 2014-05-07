package com.areabe.easyaccess;
import java.io.*;
import java.util.Date;

public class Log extends java.io.PrintWriter{
  private static ByteArrayOutputStream out = new ByteArrayOutputStream();
  private static Log log=null;

  public static Log getInstance() {
    if (log==null) {
      log = new Log();
    }
    return log;
  }

  private Log() {
    super(out,true);
  }

  public void println(String s) {
    Date dt = new Date();
    super.println(dt.toString()+ "\t" + s);
  }

  public String toString() {
    return out.toString();
  }

  public void reset() {
    out.reset();
  }
}