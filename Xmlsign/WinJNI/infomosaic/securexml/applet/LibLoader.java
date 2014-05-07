package infomosaic.securexml.applet;

import java.io.*;
import java.net.*;
import java.lang.reflect.Method;

public class LibLoader {
  String dll = null;
  String osVersion = null;
  String osName = null;
  XMLSignApplet m_applet = null;
  boolean m_isLoaded = false;
  String cacLibLocation = null;

  public LibLoader() 
  {
  }

  public void init(XMLSignApplet parent, String osName,String osVersion) throws Exception{
    String dialogEngLibLocation = null;
	  String dialogSpanishLibLocation = null;
	  String dialogFrenchLibLocation = null;
	  String dialogGermanLibLocation = null;
	  String dialogJapaneseLibLocation = null;
	  String dialogHungarianLibLocation = null;

	this.m_applet = parent;
    this.osVersion = osVersion;
    this.osName = osName;
    File f = null;
    FileOutputStream fos = null;
    String libLocation = null;

    try {
     int MAX_PATH = 260;
     StringBuffer temppath = new StringBuffer(MAX_PATH);
     Class c = Class.forName("com.ms.wfc.win32.Windows");
     Class[] pars = new Class[2];
     pars[0] = java.lang.Integer.TYPE;
     pars[1] = temppath.getClass();
     Method gtp = c.getMethod("GetTempPath",pars);
     Object[] ppars = new Object[2];
     ppars[0] = new Integer(temppath.capacity());
     ppars[1] = temppath;
     gtp.invoke(null,ppars);

     String tStr = new String(temppath);
//     int i = tStr.lastIndexOf('\\');
//     tStr = tStr.substring(0,i);
//     i = tStr.lastIndexOf('\\');
//     tStr = tStr.substring(0,i);
//     i = tStr.lastIndexOf('\\');
//     tStr = tStr.substring(0,i);

     libLocation = tStr;

   }catch(Throwable thre){
//     System.out.println(thre);
   }
   

    try {
		if (libLocation == null) 
		{
			libLocation = System.getProperty("user.home");
			libLocation += File.separator + "Application Data" + File.separator + "Infomosaic";
		}
		else
		{
			libLocation += "Infomosaic";
		}
	  try
	  {
	  	f = new File(libLocation);
	    if (f.isDirectory() == false)
			f.mkdir();
	  }
	  catch (SecurityException se)
	  {
	 	se.printStackTrace();
	  }
	  libLocation +=  File.separator;
      dialogEngLibLocation = libLocation + "EnglishDiag.dll";
	  dialogSpanishLibLocation = libLocation + "SpanishDiag.dll";
	  dialogGermanLibLocation = libLocation + "GermanDiag.dll";
	  dialogFrenchLibLocation = libLocation + "FrenchDiag.dll";
	  dialogJapaneseLibLocation = libLocation + "JapaneseDiag.dll";
	  dialogHungarianLibLocation = libLocation + "HungarianDiag.dll";
	  cacLibLocation = libLocation + "SecureXMLCac.dll";
	  libLocation += "SignatureL.dll";

          InputStream inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("EnglishDiag.dll");
          int l=0;
          if(inputstream != null)
          {
            byte abyte[] = new byte[4096];
            f = new File(dialogEngLibLocation);
			  if (f.exists()) 
			  {
				  try
				  {
					  f.delete();
					  fos = new FileOutputStream(f);            
					  while ((l=inputstream.read(abyte))>0) 
					  {
						  fos.write(abyte,0,l);
					  }
					  fos.close();
				  }
				  catch(Exception e){
				  e.printStackTrace();}
			  }
			  else
			  {
				  fos = new FileOutputStream(f);            
				  while ((l=inputstream.read(abyte))>0) 
				  {
					  fos.write(abyte,0,l);
				  }
				  fos.close();
			  }
          }

		inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("SpanishDiag.dll");
		l=0;
		if(inputstream != null)
		{
			byte abyte[] = new byte[4096];
			f = new File(dialogSpanishLibLocation);
			if (f.exists()) 
			{
				try
				{
					f.delete();
					fos = new FileOutputStream(f);            
					while ((l=inputstream.read(abyte))>0) 
					{
						fos.write(abyte,0,l);
					}
					fos.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();}
			}
			else
			{
				fos = new FileOutputStream(f);            
				while ((l=inputstream.read(abyte))>0) 
				{
					fos.write(abyte,0,l);
				}
				fos.close();
			}
		}
		
		inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("GermanDiag.dll");
		l=0;
		if(inputstream != null)
		{
			byte abyte[] = new byte[4096];
			f = new File(dialogGermanLibLocation);
			if (f.exists()) 
			{
				try
				{
					f.delete();
					fos = new FileOutputStream(f);            
					while ((l=inputstream.read(abyte))>0) 
					{
						fos.write(abyte,0,l);
					}
					fos.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();}
			}
			else
			{
				fos = new FileOutputStream(f);            
				while ((l=inputstream.read(abyte))>0) 
				{
					fos.write(abyte,0,l);
				}
				fos.close();
			}
		}
		
		inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("FrenchDiag.dll");
		l=0;
		if(inputstream != null)
		{
			byte abyte[] = new byte[4096];
			f = new File(dialogFrenchLibLocation);
			if (f.exists()) 
			{
				try
				{
					f.delete();
					fos = new FileOutputStream(f);            
					while ((l=inputstream.read(abyte))>0) 
					{
						fos.write(abyte,0,l);
					}
					fos.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();}
			}
			else
			{
				fos = new FileOutputStream(f);            
				while ((l=inputstream.read(abyte))>0) 
				{
					fos.write(abyte,0,l);
				}
				fos.close();
			}
		}
		
		inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("JapaneseDiag.dll");
		l=0;
		if(inputstream != null)
		{
			byte abyte[] = new byte[4096];
			f = new File(dialogJapaneseLibLocation);
			if (f.exists()) 
			{
				try
				{
					f.delete();
					fos = new FileOutputStream(f);            
					while ((l=inputstream.read(abyte))>0) 
					{
						fos.write(abyte,0,l);
					}
					fos.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();}
			}
			else
			{
				fos = new FileOutputStream(f);            
				while ((l=inputstream.read(abyte))>0) 
				{
					fos.write(abyte,0,l);
				}
				fos.close();
			}
		}
		
		inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("HungarianDiag.dll");
		l=0;
		if(inputstream != null)
		{
			byte abyte[] = new byte[4096];
			f = new File(dialogSpanishLibLocation);
			if (f.exists()) 
			{
				try
				{
					f.delete();
					fos = new FileOutputStream(f);            
					while ((l=inputstream.read(abyte))>0) 
					{
						fos.write(abyte,0,l);
					}
					fos.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();}
			}
			else
			{
				fos = new FileOutputStream(f);            
				while ((l=inputstream.read(abyte))>0) 
				{
					fos.write(abyte,0,l);
				}
				fos.close();
			}
		}
		
		l =0;
          inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("SignatureL.dll");
          if(inputstream == null)
          {
            throw new Exception("Library SignatureL.dll not found");
          } else
          {
            byte abyte[] = new byte[4096];
            f = new File(libLocation);
			  if (f.exists()) 
			  {
				  try
				  {
					  f.delete();
					  fos = new FileOutputStream(f);     
					  while ((l=inputstream.read(abyte))>0) 
					  {
						  fos.write(abyte,0,l);
					  }
					  fos.close();
				  }
				  catch (Exception e){e.printStackTrace();}
			  }
			  else
			  {
				  fos = new FileOutputStream(f);     
				  while ((l=inputstream.read(abyte))>0) 
				  {
					  fos.write(abyte,0,l);
				  }
				  fos.close();
			  }
          }

		inputstream = (infomosaic.securexml.applet.LibLoader.class).getResourceAsStream("SecureXMLCac.dll");
		l=0;
		if(inputstream != null)
		{
			byte abyte[] = new byte[4096];
			f = new File(cacLibLocation);
			if (f.exists()) 
			{
				try
				{
					f.delete();
					fos = new FileOutputStream(f);            
					while ((l=inputstream.read(abyte))>0) 
					{
						fos.write(abyte,0,l);
					}
					fos.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}
			}
			else
			{
				fos = new FileOutputStream(f);            
				while ((l=inputstream.read(abyte))>0) 
				{
					fos.write(abyte,0,l);
				}
				fos.close();
			}
		}

		try
		{
			System.load(libLocation);
			m_isLoaded = true;
		}
		catch (Throwable e)
		{
			System.gc();
			Thread.sleep(300);
			e.printStackTrace();
		}
		try
		{
			System.load(cacLibLocation);
		}
		catch (Throwable e)
		{
			System.gc();
//			Thread.sleep(300);
			e.printStackTrace();
		}
	}
	catch(Exception e)
	{
      e.printStackTrace();
//      throw e;
    }
  }

  public boolean isLoaded(){
    return m_isLoaded;
  }
}
