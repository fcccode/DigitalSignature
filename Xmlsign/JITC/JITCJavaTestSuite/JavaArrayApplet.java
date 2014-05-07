import java.awt.*;
import java.applet.*;
import java.util.*;

public class JavaArrayApplet extends Applet{
 private String  [] javaArray;

 public String [] getJavaArray() {
   return javaArray;
   }

public String getJavaArrayAsAString() {
   // you need more error checking here, of course...
   if (javaArray == null) return "";

   int k=0;
   String s = "";

	try
	{
		k = javaArray.length;
		if (k > 0)
		{
			s = javaArray[0];
			if (k > 1)
			{
				for (int i= 1 ; i < k; i++) 
				{
					s += "|" + javaArray[i] ;
				}
			}
		}
	}
	catch (Exception e)
	{
		return ("k = " + k + ", " + e.toString());
	}

   return s;
   }

 /*
  * Type cast from Java string[]
  */
 public void setStringArray(Object o)
 {
    try {
	javaArray = (String[]) o;
    }catch(Throwable e){
        System.out.println("Cannot cast passed object to String[]: " + e.toString());
    }
 }

 public void putJavaArray(String arrayAsAString) {
   int i = 0;
   String s;
	 try
	 {
		 StringTokenizer st =
			 new StringTokenizer(arrayAsAString, "|");

		 while(st.hasMoreTokens())
		 {
			 st.nextToken();
			 i++;
		 }
		 javaArray = new String[i];
		 i=0;
		 st =
			 new StringTokenizer(arrayAsAString, "|");

		 while(st.hasMoreTokens())
		 {
			 javaArray[i++] = st.nextToken();
		 }
	 }
	 catch (Exception e)
	 {
		 e.printStackTrace();
		 System.err.println("i = " + i + " Bombed in putJavaArray: " + arrayAsAString);
	 }
   }
 }