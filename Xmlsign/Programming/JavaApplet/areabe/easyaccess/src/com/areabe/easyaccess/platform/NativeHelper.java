package com.areabe.easyaccess.platform;

import com.areabe.easyaccess.EasyAccess;
import java.net.Socket;
import java.io.IOException;

public interface NativeHelper {
public static String ns = "127.0.0.1";
  public boolean restored=true;
  public void addNameServer() throws Exception;
  public void restoreNameServer();
  public void init(EasyAccess parent, String osName, String osVersion) throws Exception;
  public void addProvider() throws Exception;
  public Socket getSecureSocket(String host, int port) throws IOException;
}