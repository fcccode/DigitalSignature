import java.io.*;
import infomosaic.securexml.*;

public class MakeInfFile {
  private static Signature signature = null;
  private static String content =
      "[Add.Code]\r\n" +
      "  XMLSign.dll=XMLSign.dll\r\n" +
      "\r\n" +
      "[XMLSign.dll]\r\n" +
      "  file=thiscab\r\n" +
      "  DestDir=11\r\n" +
      "  RegisterServer=yes\r\n" +
      "  FileVersion=";

  public static void main(String[] args) throws Exception {
      signature = new Signature();
      String version = signature.getVersion();
      String infVersion = version.replaceAll("\\.","\\,");
      File vFile = new File("default.inf");
      if (vFile.exists()) vFile.delete();
      FileOutputStream fos = new FileOutputStream(vFile);
      fos.write(content.getBytes());
      fos.write(infVersion.getBytes());
      fos.write("\r\n".getBytes());
      fos.close();
  }
}
