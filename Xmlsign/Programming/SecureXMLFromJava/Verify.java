import infomosaic.securexml.Signature;
import java.io.*;

public class Verify
{
public static void main(String [] args)
{
        Signature sigObj;
        try
        {
                sigObj = new Signature();
                int result = sigObj.verify("signature.xml");
                System.out.println("result = " +  result);
                System.out.println("Signer = " +  sigObj.getSignerSubject("MySignature"));
                System.out.println("Time Stamp = " + sigObj.getSigPropValueByName(0, "Timestamp_MySignature"));
                System.out.println("Time Stamp Format = " + sigObj.getSigPropValueByName(0, "TimeStampFormat"));
        }
        catch (Exception e)
        {
                System.out.println(e.toString());
        }
}
}
