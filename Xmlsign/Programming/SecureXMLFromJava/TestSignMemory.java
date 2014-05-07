import infomosaic.securexml.*; 



public class TestSignMemory 
{ 
  public static void main(String[] args) 
  { 

        String testStr=""; 
          try 
          { 
            System.out.println("Started Test"); 
                for(int i=0; i<9999999; i++) { 
              if((i%100)==0) 
                  System.out.println("Loop Value = " + i); 
                  Signature s1 = new Signature(); 
           s1.setCertificateChainValidation(1);
            s1.setCertificatePolicyChecking(1);
            s1.setCertificateTrustExplicit(1);
            s1.setCertificatePathLengthChecking(1);
            String[] roots = new String[1];
            roots[0] = "C:\\temp\\DoD Class 3 Root CA.cer";
            s1.setTrustedRoots(roots);
                  s1.verify("C:\\Temp\\USArmySignedXml1.xml"); 
                  s1.destroy(); 
              
            } 
          } 
          catch (Exception e) 
          { 
          e.printStackTrace(); 
          } 
  } 
} 

