package com.areabe.easyaccess.dns;

import java.lang.reflect.*;
import java.io.*;
import java.net.*;
import java.util.*;
import org.xbill.DNS.*;
import org.xbill.DNS.utils.*;
import com.areabe.easyaccess.WorkerThread;
import com.areabe.easyaccess.Config;
import com.areabe.easyaccess.Log;

public class Named {
  Cache cache;
  Hashtable znames;
  short port = 53;
  InetAddress bindAddress;
  DatagramSocket dsock=null;
  ServerSocket ssock=null;
  WorkerThread wt=null;
  static Config cfg = null;
  static Log log = null;
  private static final String SOARecord = "@ root. 55432 10800 900 86400 86400";
  private static final int ttl = 86400;

  public
      Named(WorkerThread wt) throws Exception {
    boolean started = false;

    this.wt = wt;
    cache = null;
    znames = new Hashtable();
    cfg = Config.getInstance();
    log = Log.getInstance();

    bindAddress = InetAddress.getByName("127.0.0.1");

    addPrimaryZone();
    cache = new Cache();
    addUDP(port);
    addTCP(port);
  }

  public void
      addPrimaryZone() throws Exception {

    MyStringTokenizer st = null;
    Record r = null;
    Zone newzone = null;
    Name origin = null;
    Name current = null;

    Enumeration en = cfg.dns.keys();
    while (en.hasMoreElements()) {
      String soaHost = (String)en.nextElement();
      String soaIP = (String) cfg.dns.get(soaHost);

      newzone = new Zone();
      origin = new Name(soaHost + ".");
      current = new Name(soaHost + ".");
      // SOA record
      st = new MyStringTokenizer(SOARecord);
      r = Record.fromString(current,Type.SOA,DClass.IN,ttl,st,origin);
      newzone.addRecord(r);
      // NS record
      st = new MyStringTokenizer("@");
      r = Record.fromString(current,Type.NS,DClass.IN,ttl,st,origin);
      newzone.addRecord(r);
      // A record
      current = new Name(soaHost);
      st = new MyStringTokenizer(soaIP);
      r = Record.fromString(current,Type.A,DClass.IN,ttl,st,origin);
      newzone.addRecord(r);
      // A record for *
      current = new Name("*." + soaHost);
      st = new MyStringTokenizer(soaIP);
      r = Record.fromString(current,Type.A,DClass.IN,ttl,st,origin);
      newzone.addRecord(r);

      newzone.validate();
      znames.put(newzone.getOrigin(), newzone);
      log.println("DNS: Adding zone named <" + newzone.getOrigin() + ":" +soaIP+ ">");
    }
    if (znames.isEmpty()) {
      throw new Exception("Empty DNS zone");
    }
  }

  public Zone
      findBestZone(Name name) {
    Zone foundzone = null;
    foundzone = (Zone) znames.get(name);
    if (foundzone != null)
      return foundzone;
    Name tname = name;
    while (!tname.equals(Name.root)) {
      tname = new Name(tname, 1);
      foundzone = (Zone) znames.get(tname);
      if (foundzone != null)
        return foundzone;
    }
    return null;
  }

  public RRset
      findExactMatch(Name name, short type, short dclass, boolean glue) {
    Zone zone = findBestZone(name);
    if (zone != null)
      return zone.findExactMatch(name, type);
    else
      return null;
  }

  void
      addRRset(Name name, Message response, RRset rrset, boolean sigonly) {
    Enumeration e;
    if (!sigonly) {
      e = rrset.rrs();
      while (e.hasMoreElements()) {
        Record r = (Record) e.nextElement();
        if (!name.isWild() && r.getName().isWild())
          r = r.withName(name);
        response.addRecord(r, Section.ANSWER);
      }
    }
    e = rrset.sigs();
    while (e.hasMoreElements()) {
      Record r = (Record) e.nextElement();
      if (!name.isWild() && r.getName().isWild())
        r = r.withName(name);
      response.addRecord(r, Section.ANSWER);
    }
  }

  void
      addAuthority(Message response, Name name, Zone zone) {
    if (response.getHeader().getCount(Section.ANSWER) > 0 || zone == null) {
      RRset nsRecords = findExactMatch(name, Type.NS, DClass.IN,
                                       false);
      if (nsRecords == null) {
        if (zone != null)
          nsRecords = zone.getNS();
        else {
          RRset[] rrsets;
          rrsets = cache.findRecords(Name.root, Type.NS,
                                     DClass.IN);
          if (rrsets == null)
            nsRecords = null;
          else
            nsRecords = rrsets[0];
        }
      }
      if (nsRecords == null)
        return;
      Enumeration e = nsRecords.rrs();
      while (e.hasMoreElements()) {
        Record r = (Record) e.nextElement();
        if (response.findRecord(r, Section.ANSWER) == false)
          response.addRecord(r, Section.AUTHORITY);
      }
      e = nsRecords.sigs();
      while (e.hasMoreElements()) {
        Record r = (Record) e.nextElement();
        if (response.findRecord(r, Section.ANSWER) == false)
          response.addRecord(r, Section.AUTHORITY);
      }
    }
    else {
      SOARecord soa = (SOARecord) zone.getSOA();
      response.addRecord(soa, Section.AUTHORITY);
    }
  }

  private void
      addGlue(Message response, Name name) {
    RRset a = findExactMatch(name, Type.A, DClass.IN, true);
    Enumeration e = a.rrs();
    while (e.hasMoreElements()) {
      Record r = (Record) e.nextElement();
      if (response.findRecord(r) == false)
        response.addRecord(r, Section.ADDITIONAL);
    }
    e = a.sigs();
    while (e.hasMoreElements()) {
      Record r = (Record) e.nextElement();
      if (response.findRecord(r) == false)
        response.addRecord(r, Section.ADDITIONAL);
    }
  }

  private void
      addAdditional2(Message response, int section) {
    Enumeration e = response.getSection(section);
    while (e.hasMoreElements()) {
      Record r = (Record) e.nextElement();
      try {
        Method m = r.getClass().getMethod("getTarget", null);
        Name glueName = (Name) m.invoke(r, null);
        addGlue(response, glueName);
      }
      catch (Exception ex) {
      }
    }

  }

  void
      addAdditional(Message response) {
    addAdditional2(response, Section.ANSWER);
    addAdditional2(response, Section.AUTHORITY);
  }

  Message
      doAXFR(Name name, Message query, Socket s) {
    Zone zone = (Zone) znames.get(name);
    if (zone == null) {
      return errorMessage(query, Rcode.REFUSED);
    }
    Enumeration e = zone.AXFR();
    try {
      DataOutputStream dataOut;
      dataOut = new DataOutputStream(s.getOutputStream());
      while (e.hasMoreElements()) {
        RRset rrset = (RRset) e.nextElement();
        Message response = new Message();
        addRRset(rrset.getName(), response, rrset, false);
        byte[] out = response.toWire();
        dataOut.writeShort(out.length);
        dataOut.write(out);
      }
    }
    catch (IOException ex) {
      log.println("DNS: AXFR failed");
    }
    try {
      s.close();
    }
    catch (IOException ex) {
    }
    return null;
  }

  /*
   * Note: a null return value means that the caller doesn't need to do
   * anything.  Currently this only happens if this is an AXFR request over
   * TCP.
   */
  Message
      generateReply(Message query, byte[] in, Socket s) {
    boolean badversion;
    int maxLength;
    boolean sigonly;

    if (query.getHeader().getOpcode() != Opcode.QUERY)
      return errorMessage(query, Rcode.NOTIMPL);
    Record queryRecord = query.getQuestion();

    OPTRecord queryOPT = query.getOPT();
    if (queryOPT != null && queryOPT.getVersion() > 0)
      badversion = true;

    if (s != null)
      maxLength = 65535;
    else if (queryOPT != null)
      maxLength = queryOPT.getPayloadSize();
    else
      maxLength = 512;

    Message response = new Message();
    response.getHeader().setID(query.getHeader().getID());
    response.getHeader().setFlag(Flags.QR);
    response.addRecord(queryRecord, Section.QUESTION);

    Name name = queryRecord.getName();
    short type = queryRecord.getType();
    short dclass = queryRecord.getDClass();
    if (type == Type.AXFR && s != null)
      return doAXFR(name, query, s);
    if (!Type.isRR(type) && type != Type.ANY)
      return errorMessage(query, Rcode.NOTIMPL);
    if (type == Type.SIG) {
      type = Type.ANY;
      sigonly = true;
    }
    else
      sigonly = false;

    Zone zone = findBestZone(name);
    if (zone != null) {
      response.getHeader().setFlag(Flags.AA);
      SetResponse zr = zone.findRecords(name, type);
      if (zr.isNXDOMAIN()) {
        response.getHeader().setRcode(Rcode.NXDOMAIN);
        log.println("DNS zone found, but host not found: " + name.toString());
      }
      Vector backtrace = zr.backtrace();
      if (backtrace != null) {
        Enumeration e = backtrace.elements();
        while (e.hasMoreElements()) {
          Record cname = (Record) e.nextElement();
          response.addRecord(cname, Section.ANSWER);
        }
      }
      if (zr.isSuccessful()) {
        RRset[] rrsets = zr.answers();
        for (int i = 0; i < rrsets.length; i++)
          addRRset(name, response, rrsets[i], sigonly);
      }
      addAuthority(response, name, zone);
      addAdditional(response);
    }
    else {
      response.getHeader().setRcode(Rcode.NOTIMPL);
      //log.println("Zone NOT found (NXDOMAIN):" + name.toString());
/*
      SetResponse cr;
      cr = cache.lookupRecords(name, type, dclass,
                               Credibility.NONAUTH_ANSWER);

      Vector backtrace = cr.backtrace();
      if (backtrace != null) {
        Enumeration e = backtrace.elements();
        while (e.hasMoreElements()) {
          Record cname = (Record) e.nextElement();
          response.addRecord(cname,
                             Section.ANSWER);
        }
        if (!cr.isSuccessful())
          response.getHeader().setRcode(Rcode.NXDOMAIN);
      }
      if (cr.isSuccessful()) {
        RRset[] rrsets = cr.answers();
        for (int i = 0; i < rrsets.length; i++)
          addRRset(name, response, rrsets[i], sigonly);
      }
 */
    }
    try {
      byte[] out = response.toWire();
      if (out.length > maxLength) {
        truncate(response, out.length, maxLength);
      }
    }
    catch (IOException e) {
    }
    return response;
  }

  public int
      truncateSection(Message in, int maxLength, int length, int section) {
    int removed = 0;
    Record[] records = in.getSectionArray(section);
    for (int i = records.length - 1; i >= 0; i--) {
      Record r = records[i];
      removed += r.getWireLength();
      length -= r.getWireLength();
      in.removeRecord(r, section);
      if (length > maxLength)
        continue;
      else {
        for (int j = i - 1; j >= 0; j--) {
          Record r2 = records[j];
          if (!r.getName().equals(r2.getName()) ||
              r.getType() != r2.getType() ||
              r.getDClass() != r2.getDClass())
            break;
          removed += r2.getWireLength();
          length -= r2.getWireLength();
          in.removeRecord(r2, section);
        }
        return removed;
      }
    }
    return removed;
  }

  public void
      truncate(Message in, int length, int maxLength) {
    length -= truncateSection(in, maxLength, length, Section.ADDITIONAL);
    if (length < maxLength)
      return;

    in.getHeader().setFlag(Flags.TC);
    length -= truncateSection(in, maxLength, length, Section.AUTHORITY);
    if (length < maxLength)
      return;
    length -= truncateSection(in, maxLength, length, Section.ANSWER);
  }

  public Message
      formerrMessage(byte[] in) {
    Header header;
    try {
      header = new Header(new DataByteInputStream(in));
    }
    catch (IOException e) {
      header = new Header(0);
    }
    Message response = new Message();
    response.setHeader(header);
    for (int i = 0; i < 4; i++)
      response.removeAllRecords(i);
    header.setRcode(Rcode.FORMERR);
    return response;
  }

  public Message
      errorMessage(Message query, short rcode) {
    Header header = query.getHeader();
    Message response = new Message();
    response.setHeader(header);
    for (int i = 0; i < 4; i++)
      response.removeAllRecords(i);
    header.setRcode(rcode);
    return response;
  }

  /**
   *
   * @param port
   */
  public void
      serveTCP(short port) {
    try {
      ssock = new ServerSocket(port, 0, bindAddress);
      while (true) {
        Socket s = ssock.accept();
        int inLength;
        DataInputStream dataIn;
        DataOutputStream dataOut;
        byte[] in;

        try {
          InputStream is = s.getInputStream();
          dataIn = new DataInputStream(is);
          inLength = dataIn.readUnsignedShort();
          in = new byte[inLength];
          dataIn.readFully(in);
        }
        catch (InterruptedIOException e) {
          s.close();
          continue;
        }
        Message query, response;
        try {
          query = new Message(in);
          response = generateReply(query, in, s);
          if (response == null)
            continue;
        }
        catch (IOException e) {
          response = formerrMessage(in);
        }
        byte[] out = response.toWire();
        dataOut = new DataOutputStream(s.getOutputStream());
        dataOut.writeShort(out.length);
        dataOut.write(out);
        s.close();
      }
    }
    catch (Exception e) {
      if (Config.debug) {
        System.err.println("DNS serveTCP exception: " + e);
      }
      wt.setDNSFailed();
    }
    finally{
      log.println("DNS: TCP listener stopped");
      synchronized (wt) {
        try {
          wt.notifyAll();
        }catch(Exception e){
          if (Config.debug) {
            System.err.println("DNS TCP: notify failed");
          }
          if (!(e instanceof IOException)) {
            e.printStackTrace();
          }
        }
      }
    }
  }

  /**
   *
   * @param port
   */
  public void
      serveUDP(short port) {
    DatagramPacket dp=null;
    try {
      dsock = new DatagramSocket(port, bindAddress);
      while (true) {
        short udpLength = 512;
        dp = new DatagramPacket(new byte[512],
                                               512);
        try {
          dsock.receive(dp);
        }
        catch (InterruptedIOException e) {
          continue;
        }
        byte[] in = new byte[dp.getLength()];
        System.arraycopy(dp.getData(), 0, in, 0, in.length);
        Message query, response;
        try {
          query = new Message(in);
          response = generateReply(query, in, null);
          if (response == null)
            continue;
        }
        catch (IOException e) {
          response = formerrMessage(in);
        }
        byte[] out = response.toWire();

        dp = new DatagramPacket(out, out.length,
                                dp.getAddress(), dp.getPort());
        dsock.send(dp);
      }
    }
    catch (Exception e) {
      if (Config.debug) {
        System.err.println("DNS serveUDP exception: " + e);
        if (!(e instanceof IOException)) {
          e.printStackTrace();
        }
      }
      wt.setDNSFailed();
    }
    finally{
      log.println("DNS: UDP listener stopped");
      synchronized (wt) {
        try {
          wt.notifyAll();
        }catch(Exception e){
          if (Config.debug) {
            System.err.println("DNS UDP: notify failed");
            if (!(e instanceof IOException)) {
              e.printStackTrace();
            }
          }
        }
      }
    }
  }

  public void
      addTCP(final short port) {
    Thread t;
    t = new Thread(new Runnable() {
      public void run() {
        serveTCP(port);
      }
    });
    t.start();
  }

  public void
      addUDP(final short port) {
    Thread t;
    t = new Thread(new Runnable() {
      public void run() {
        serveUDP(port);
      }
    });
    t.start();
  }

  public void stopListeners(){
    try {
      if (dsock!=null) dsock.close();
      if (ssock!=null) ssock.close();
    }catch(Exception e){}
  }

  public static void main(String[] args) throws Exception{
    File f = new File("config.txt");
    FileInputStream fis = new FileInputStream(f);
    byte[] b = new byte[(int)f.length()];
    fis.read(b);
    fis.close();
    Named nm = new Named(null);
  }
}