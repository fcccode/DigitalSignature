package infomosaic.securexml;

import junit.framework.*;

public class AllTests
    extends TestCase {

  public AllTests(String s) {
    super(s);
  }

  public static Test suite() {
    TestSuite suite = new TestSuite();
    suite.addTestSuite(infomosaic.securexml.TestSignature.class);
    return suite;
  }
}
