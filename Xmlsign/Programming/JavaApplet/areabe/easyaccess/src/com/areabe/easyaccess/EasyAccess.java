package com.areabe.easyaccess;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.util.*;
import com.areabe.easyaccess.gui.AWTHelper;
import com.areabe.easyaccess.gui.ImageViewer;
import com.areabe.easyaccess.locale.Resources;
import sun.misc.BASE64Decoder;
import java.net.URL;

public class EasyAccess extends Applet {
  private boolean isStandalone = false;
  private WorkerThread wt = null;
  private String configuration = null;
  Log log = Log.getInstance();
  private boolean configError = true;
  private TextArea displayLog;
  private Frame wLog;
  private Button btClear;
  public static final String version = "1.00.0002";
  private Object lockObject= new Object();
  private int conNumber=0;
  boolean isStarted=false;

  // connection status
  public static final int ACTIVE=0;
  public static final int INACTIVE=1;
  public static final int BROKEN=2;

  Image iSSLON;       // SSL on
  Image iSSLOFF;      // SSL off
  Image iViewLogPressed;     // ViewLog button
  Image iViewLogUnpressed;
  Image iViewLogMouseHover;
  Image iStartPressed;     // Start button
  Image iStartUnpressed;
  Image iStartMouseHover;
  Image iStopPressed;     // Stop button
  Image iStopUnpressed;
  Image iStopMouseHover;
  Image iConStatusI;  // connection idle
  Image iConStatusG;  // connection green
  Image iConStatusR;  // connection red
  Resources resources = null;
  ImageViewer sslStatus = null;
  ImageViewer viewLog = null;
  ImageViewer logout = null;
  ImageViewer conStatus = null;
  BorderLayout borderLayout1 = new BorderLayout();
  MouseListener logoutML = null;
  Class jsObjectClass = null;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public EasyAccess() {
  }

  //Initialize the applet
  public void init() {
    try {
      // disable links
      try {
        jsObjectClass = Class.forName("netscape.javascript.JSObject");
      } catch(ClassNotFoundException e) {
        jsObjectClass = null;
      }

      disableLinks();
      System.err.println("**********************************************************************");
      Resources.initResourceBundle();
      resources = Resources.getInstance();

      // got some images

      String sSSL = resources.getString("SSLON_IMAGE");
      iSSLON = AWTHelper.getImage(sSSL);
      AWTHelper.waitForImage(this, sSSL, iSSLON);

      sslStatus = new ImageViewer(iSSLON);

      sSSL = resources.getString("SSLOFF_IMAGE");
      iSSLOFF = AWTHelper.getImage(sSSL);
      AWTHelper.waitForImage(this, sSSL, iSSLOFF);

      String sConStatus = resources.getString("CON_STATUS_IDLE_IMAGE");
      iConStatusI = AWTHelper.getImage(sConStatus);
      AWTHelper.waitForImage(this, sConStatus, iConStatusI);

      sConStatus = resources.getString("CON_STATUS_GREEN_IMAGE");
      iConStatusG = AWTHelper.getImage(sConStatus);
      AWTHelper.waitForImage(this, sConStatus, iConStatusG);

      sConStatus = resources.getString("CON_STATUS_RED_IMAGE");
      iConStatusR = AWTHelper.getImage(sConStatus);
      AWTHelper.waitForImage(this, sConStatus, iConStatusR);
      conStatus = new ImageViewer(iConStatusR);

      String sViewLog = resources.getString("VIEWLOG_UNPRESSED_IMAGE");
      iViewLogUnpressed = AWTHelper.getImage(sViewLog);
      AWTHelper.waitForImage(this, sViewLog, iViewLogUnpressed);
      viewLog = new ImageViewer(iViewLogUnpressed);

      sViewLog = resources.getString("VIEWLOG_PRESSED_IMAGE");
      iViewLogPressed = AWTHelper.getImage(sViewLog);
      AWTHelper.waitForImage(this, sViewLog, iViewLogPressed);

      sViewLog = resources.getString("VIEWLOG_HOVER_IMAGE");
      iViewLogMouseHover = AWTHelper.getImage(sViewLog);
      AWTHelper.waitForImage(this, sViewLog, iViewLogMouseHover);

      String sLogout = resources.getString("START_UNPRESSED_IMAGE");
      iStartUnpressed = AWTHelper.getImage(sLogout);
      AWTHelper.waitForImage(this, sLogout, iStartUnpressed);

      sLogout = resources.getString("START_PRESSED_IMAGE");
      iStartPressed = AWTHelper.getImage(sLogout);
      AWTHelper.waitForImage(this, sLogout, iStartPressed);

      sLogout = resources.getString("START_HOVER_IMAGE");
      iStartMouseHover = AWTHelper.getImage(sLogout);
      AWTHelper.waitForImage(this, sLogout, iStartMouseHover);

      sLogout = resources.getString("STOP_UNPRESSED_IMAGE");
      iStopUnpressed = AWTHelper.getImage(sLogout);
      AWTHelper.waitForImage(this, sLogout, iStopUnpressed);
      logout = new ImageViewer(iStopUnpressed);

      sLogout = resources.getString("STOP_PRESSED_IMAGE");
      iStopPressed = AWTHelper.getImage(sLogout);
      AWTHelper.waitForImage(this, sLogout, iStopPressed);

      sLogout = resources.getString("STOP_HOVER_IMAGE");
      iStopMouseHover = AWTHelper.getImage(sLogout);
      AWTHelper.waitForImage(this, sLogout, iStopMouseHover);

      jbInit();

      // log windows
      Panel panel1 = new Panel();
      GridLayout gridLayout1 = new GridLayout();
      displayLog = new TextArea();
      btClear = new Button();

      wLog = new Frame("EasyAccess Log");
      wLog.setBounds(20,20,600,440);
      wLog.setLayout(gridLayout1);
      panel1.setLayout(null);
      gridLayout1.setColumns(1);
      gridLayout1.setHgap(5);
      gridLayout1.setVgap(5);
      panel1.setBackground(Color.white);
      displayLog.setColumns(0);
      displayLog.setLocale(java.util.Locale.getDefault());
      displayLog.setRows(0);
      displayLog.setSelectionEnd(9);
      displayLog.setSelectionStart(9);
      displayLog.setText("");
      displayLog.setBounds(new Rectangle(10, 9, 570, 330));
      btClear.setForeground(Color.black);
      btClear.setLabel("Clear");
      btClear.setLocale(java.util.Locale.getDefault());
      btClear.setBounds(new Rectangle(501, 351, 80, 25));
      btClear.addActionListener(new btClear_actionAdapter(this));
      panel1.add(displayLog, null);
      panel1.add(btClear, null);
      wLog.add(panel1, null);
      wLog.addWindowListener(new viewLog_windowAdapter(wLog));
      wLog.setResizable(false);
//      wLog.pack();

      String debug = this.getParameter("debug", "false");
      Config.setDebug(debug.toLowerCase().equals("true"));
      if (Config.debug) {
        this.add(viewLog, null);
      }

      String paramConfig = this.getParameter("configuration", null);
      if (paramConfig==null) {
        log.println("No 'configuration' parameter");
        throw new Exception("No 'configuration' parameter");
      }

      if (Config.debug) {
        System.err.println(paramConfig);
      }

      BASE64Decoder b64d = new BASE64Decoder();
      byte[] decodedConfig = b64d.decodeBuffer(paramConfig);
      if (decodedConfig==null) {
        log.println("Parameter 'configuration' is not valid base64 data");
        throw new Exception("Parameter 'configuration' is not valid base64 data");
      }

      java.util.zip.GZIPInputStream gzin = new java.util.zip.GZIPInputStream(new java.io.ByteArrayInputStream(decodedConfig));
      int chr=0;
      StringBuffer sb = new StringBuffer();
      while ((chr = gzin.read())>0) {
        sb.append((char)chr);
      }
      gzin.close();

      configuration = sb.toString();
      configError = !Config.initConfig(configuration);
      if (configError) {
        setStatus(BROKEN);
      }else{
        Config cfg = Config.getInstance();
//        URL u = this.getCodeBase();
//        cfg.gwHost = u.getHost();
        sslStatus.setImage(cfg.isSSLMode()?iSSLON:iSSLOFF);
      }
    }
    catch(Exception e) {
      System.err.println("EasyAccess: init exception: " + e.getMessage());
      e.printStackTrace();
      setStatus(BROKEN);
    }
  }

  //Component initialization
  private void jbInit() throws Exception {
    this.setBackground(new Color(0x17536B));
    this.setLayout(null);

    conStatus.setBounds(new Rectangle(68, 8, 84, 55));
    sslStatus.setBounds(new Rectangle(9, 8, 54, 55));
    sslStatus.addMouseListener(new sslStatus_mouseAdapter(this));
    viewLog.setBounds(new Rectangle(157, 5, 85, 22));
    viewLog.addMouseListener(new viewLog_mouseAdapter(this));
    logout.setBounds(new Rectangle(157, 35, 85, 22));
    logoutML = new logout_mouseAdapter(this);
    logout.addMouseListener(logoutML);
    this.add(sslStatus, null);
    if (Config.debug) {
      this.add(viewLog, null);
    }
    this.add(logout, null);
    this.add(conStatus, null);
  }

  /**
   * Display log.
   *
   * @param e
   */
  void viewLog_actionPerformed(MouseEvent e) {
    log.flush();
    displayLog.setText(log.toString());
    wLog.show();
  }

  /**
   * Clear log.
   *
   * @param e
   */
  void btClear_actionPerformed(ActionEvent e) {
    log.reset();
    displayLog.setText(log.toString());
  }

  //Start the applet
  // workaround for MS - to prevent security exception init() and start() must not contain
  // dangerous code. That is why we run thread instead.
  public void start() {
    enableLinks();
    if (!configError) {
      wt = new WorkerThread(this);
      wt.start();
      isStarted=true;
      logout.setImage(iStopUnpressed);
    }
  }
  //Stop the applet
  public void stop() {
    disableLinks();
    if (wt!=null) {
      wt.stopThread();
      try {
        wt.join();
      }
      catch (Exception e) {}
      wt = null;
      isStarted=false;
      logout.setImage(iStartUnpressed);
    }
  }
  //Destroy the applet
  public void destroy() {
    if (wt!=null) {
      wt.stopThread();
      try {
        wt.join();
      }
      catch (Exception e) {}
      wt = null;
    }
  }
  //Get Applet information
  public String getAppletInfo() {
    return "EasyAccess (Kamikaze) Applet v1.0. Copyright AreaBe, Inc. 2000-2003. All rights reserved.";
  }
  //Get parameter info
  public String[][] getParameterInfo() {
    String[][] pinfo =
      {
      {"configuration", "String", ""},
      };
    return pinfo;
  }

  public void addGUIConnection(String line) {
    synchronized (lockObject) {
      conNumber++;
    }
  }

  public void removeGUIConnection(String line) {
    try {
      synchronized (lockObject) {
        conNumber--;
      }
      if (conNumber==0) {
        setStatus(INACTIVE);
      }
    }catch(Exception e){
      log.println(e);
    }
  }

  public String getVersion(){
    return version;
  }

  public void setStatus(int val) {
    Image i;
    switch (val) {
      case ACTIVE:
        i = iConStatusG;
        break;
      case INACTIVE:
        i = iConStatusI;
        break;
      case BROKEN:
        i = iConStatusR;
        break;
      default:
        i = iConStatusR;
    }
    if (conStatus!=null) {
      conStatus.setImage(i);
    }
  }

  private void disableLinks() {
    try {
      if (jsObjectClass != null) {
        netscape.javascript.JSObject window;

        window = netscape.javascript.JSObject.getWindow(this);
        window = (netscape.javascript.JSObject) window.getMember("top");
        window.eval("disableLinks();");
      }
      else {
        URL url = new URL("javascript:top.disableLinks();");
        getAppletContext().showDocument(url);
      }
    }catch(Exception e){
      if (Config.debug) {
        System.err.println("Scripting from Applet is not supported");
      }
    }
  }

  private void enableLinks() {
    try {
      if (jsObjectClass != null) {
        netscape.javascript.JSObject window;

        window = netscape.javascript.JSObject.getWindow(this);
        window = (netscape.javascript.JSObject) window.getMember("top");
        window.eval("enableLinks();");
      }
      else {
        URL url = new URL("javascript:top.enableLinks();");
        getAppletContext().showDocument(url);
      }
    }catch(Exception e){
      if (Config.debug) {
        System.err.println("Scripting from Applet is not supported");
      }
    }
  }

class sslStatus_mouseAdapter implements java.awt.event.MouseListener {
  EasyAccess adaptee;
  sslStatus_mouseAdapter(EasyAccess adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
  }
  public void mouseExited(MouseEvent e) {
    // remove hint
    //repaint();
  }
  public void mouseEntered(MouseEvent e) {
    // say something, i.e. SSL On/Off
    //repaint();
  }
  public void mouseReleased(MouseEvent e) {
  }
  public void mousePressed(MouseEvent e) {
  }
}

class viewLog_mouseAdapter implements java.awt.event.MouseListener {
  EasyAccess adaptee;
  boolean pressed=false;
  viewLog_mouseAdapter(EasyAccess adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
  }
  public void mouseExited(MouseEvent e) {
    viewLog.setImage(iViewLogUnpressed);
  }
  public void mouseEntered(MouseEvent e) {
    viewLog.setImage(iViewLogMouseHover);
  }
  public void mouseReleased(MouseEvent e) {
    if (pressed) {
      adaptee.viewLog_actionPerformed(e);
      pressed = false;
    }
    viewLog.setImage(iViewLogUnpressed);
  }
  public void mousePressed(MouseEvent e) {
    viewLog.setImage(iViewLogPressed);
    pressed=true;
  }
}

class logout_mouseAdapter implements java.awt.event.MouseListener {
  EasyAccess adaptee;
  boolean pressed=false;

  logout_mouseAdapter(EasyAccess adaptee) {
    this.adaptee = adaptee;
  }
  public void mouseClicked(MouseEvent e) {
  }
  public void mouseExited(MouseEvent e) {
    if (isStarted) {
      logout.setImage(iStopUnpressed);
    }else{
      logout.setImage(iStartUnpressed);
    }
  }
  public void mouseEntered(MouseEvent e) {
    if (isStarted) {
      logout.setImage(iStopMouseHover);
    }else{
      logout.setImage(iStartMouseHover);
    }
  }
  public void mouseReleased(MouseEvent e) {
    if (pressed) {
      if (isStarted) {
        adaptee.stop();
      }else{
        adaptee.start();
      }
      pressed=false;
    }
  }
  public void mousePressed(MouseEvent e) {
    if (isStarted) {
      logout.setImage(iStopPressed);
    }else{
      logout.setImage(iStartPressed);
    }
    pressed=true;
  }
}

class viewLog_windowAdapter implements WindowListener {
  Frame window;
  viewLog_windowAdapter(Frame adaptee) {
    this.window = adaptee;
  }
  public void windowClosing(WindowEvent e) {
    window.setVisible(false);
  }
  public void windowClosed(WindowEvent e) {
  }
  public void windowOpened(WindowEvent e) {
  }
  public void windowIconified(WindowEvent e) {
  }
  public void windowDeiconified(WindowEvent e) {
  }
  public void windowActivated(WindowEvent e) {
  }
  public void windowDeactivated(WindowEvent e) {
  }
}

class btClear_actionAdapter implements java.awt.event.ActionListener {
  EasyAccess adaptee;

  btClear_actionAdapter(EasyAccess adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.btClear_actionPerformed(e);
  }
}
}
