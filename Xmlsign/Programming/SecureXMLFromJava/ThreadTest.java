import infomosaic.securexml.Signature;

public class ThreadTest {
    public ThreadTest() throws Exception {
        for (int i =0; i<3; i++) {
            InnerThread it = new InnerThread(i);
            it.start();
        }
    }

    public static void main(String[] args) {
        try {
            ThreadTest t = new ThreadTest();
        }catch(Throwable e){
            e.printStackTrace();
        }
    }

    public class InnerThread extends Thread {
        private int m_tnum = -1;
        private Signature m_sig;
        private Signature m_sigL;

        public InnerThread(int tnum) throws Exception {
            m_tnum = tnum;
            m_sig = new Signature();
	    m_sigL = new Signature();
        }

        public void run(){
            System.out.println("Thread ["+m_tnum+"] started.");

            m_sig.setCertificateChainValidation(1);
            m_sig.setCertificatePolicyChecking(1);
            m_sig.setCertificateTrustExplicit(1);
            m_sig.setCertificatePathLengthChecking(1);
            String[] roots = new String[1];
            roots[0] = "C:\\temp\\DoD Class 3 Root CA.cer";
            m_sig.setTrustedRoots(roots);
	    System.out.println("SecureXML Path = " + m_sig.getSecureXMLPath());
	    System.out.println("License Status = " + m_sig.getLicenseStatus());
	    String floatingLicense = m_sigL.getFloatingLicense();
	    m_sigL.destroy();
            int result = -1;
            for (int i=0; i<5; i++)
            {
                    result = m_sig.verify("C:\\temp\\USArmySignedXml1.xml");
		    String [] authPolicyArray = m_sig.getAuthorityConstrainedPolicy();
		    String [] userPolicyArray = m_sig.getUserConstrainedPolicy();
		    for (int j=0; j<authPolicyArray.length; j++)
			System.out.println("Auth Constrained Policy: " + authPolicyArray[j]);
		    for (int k=0; k<userPolicyArray.length; k++)
			System.out.println("User Constrained Policy: " + userPolicyArray[k]);
            }
            int error = m_sig.getLastError();
	    m_sig.destroy();
            System.out.println("Finished Verifying Signature Thread Id = " + m_tnum + ", Result = " + result + ", error: " + error);
        }
    }
}
