import junit.framework.*;
import java.io.*;
import java.util.*;
import infomosaic.securexml.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */


public class TestSignatureNss extends TestSignature {
  public static Test suite(){
    TestSignature.nss = true;
    return new TestSuite(TestSignatureNss.class);
  }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(suite());
  }
}
