import infomosaic.securexml.*;
 
public class TestInf implements Runnable {
 static private String testSynch=null;
 
 static final private String testStr =""; 


 public void run() {
		   int maxCount = 1000;
		   int result=0;

  try {
   //testSynch.wait();
   String thName = Thread.currentThread().getName();
   System.out.println(thName + " Started Test - ");
   Signature s1 = new Signature();
            s1.setCertificateChainValidation(1);
            s1.setCertificatePolicyChecking(1);
            s1.setCertificateTrustExplicit(1);
            s1.setCertificatePathLengthChecking(1);
	    s1.setDetailedVerificationFlag(0);
            String[] roots = new String[1];
            roots[0] = "C:\\temp\\DoD Class 3 Root CA.cer";
            s1.setTrustedRoots(roots);
	    String signedXML = s1.readAll("C:\\Temp\\USArmySignedXml1.xml");
 	    java.util.Date startTime = new java.util.Date();
   for (int i = 0; i < maxCount ; i++) {
    //if ((i % 10) == 0)
    // System.out.println(thName + " Loop Value = " + i);
    result = s1.verifyXMLStr(signedXML);
 
   }
		   java.util.Date endTime = new java.util.Date();
		   long s = startTime.getTime();
		   long e = endTime.getTime();
		   System.out.println(startTime.toString());
		   System.out.println(endTime.toString());
		   long totalMs = e - s;
		   double opPerSec = (double) maxCount / ((double)totalMs/1000);

		   System.out.println("Result = " + result + " Start:" + s + " End:" + e + "\nOperations per second =" + opPerSec);
    s1.destroy();
  } catch (Throwable e) {
   e.printStackTrace();
  }
 
 }
 
 /**
  * @param args
  */
 public static void main(String[] args) {
  // TODO Auto-generated method stub
 
  try {
   testSynch = "This is a test";
   synchronized (testSynch) {
    TestInf t = null;
    Thread th = null;
    for(int i=0; i<1; i++) {
     t = new TestInf();
     th = new Thread(t);
     th.start();
    }
    Thread.sleep(1000);
   }
   //testSynch.notify();
   System.out.println("Completed Thread Creation");
   while (true) {
    Thread.sleep(1000);
   }
 
  } catch (Throwable t) {
   t.printStackTrace();
  }
 }
}

 
