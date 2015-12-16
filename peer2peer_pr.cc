// Project Scenario with Programmable Router

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "ns3/core-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/netanim-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/trace-helper.h"

using namespace ns3;
using namespace std;
static const uint32_t write_Size = 1040;
static uint32_t current_Tx_Bytes = 0;
uint8_t data[write_Size];
int count1 = 1;

static const uint32_t total_Tx_Bytes_OP = 1400000; // Data sent, in bytes will be - 1400000 from OP, 600000 for AP

static const uint32_t total_Tx_Bytes_AP = 600000;

void Start_Flow_AP (Ptr<Socket>, Ipv4_Address, uint16_t);
void Write_Until_Buffer_Full_AP (Ptr<Socket>, uint32_t);

void Start_Flow_OP (Ptr<Socket>, Ipv4_Address, uint16_t);
void Write_Until_Buffer_Full_OP (Ptr<Socket>, uint32_t);

// class to hold the values required for further processing
class File_Name
{
 private:

 string File_Name;
 string ip1;
 string ip2;
 string chunk1;
 string chunk2;

 public:

 void put_file_name(char *file)
 {
   int j=0,c=0;
   char fil[15];
   for (j=0; j<= 11; j++)
    {
      fil[c] = file[j];
      c++;
    }
   File_Name = string(fil);
//   cout << "File_Name stored in the class is " << File_Name << " time is " <<  Simulator::Now ().GetSeconds () << endl; - was needed for testing
 }

 string get_File_Name(void)
 {
   return File_Name;
 }

 void Load_Info(char *request)
 {
   string ip_1, ip_2, chunk_1, chunk_2;
   char chunk[10]="0";
   chunk[0]=request[2];
   chunk[1]=request[3];
   chunk1 = string(chunk);
   chunk[0]=request[12];
   chunk[1]=request[13];
   chunk2 = string(chunk);
//   cout << "Chunk division is " << chunk1 << " " << chunk2 <<endl; - was needed for testing
 }

 string get_ip1()
 {
     return ip1;
 }

 string get_ip2()
 {
     return ip2;
 }

 string get_chunk1()
 {
     return chunk1;
 }

 string get_chunk2()
 {
     return chunk2;
 }

};

File_Name obj; // global object for File_Name class

// this function is used for generating one packet - gets socket, remote address and a data (which is either request or response)

static void Generate_Traffic (Ptr<Socket> socket, InetSocketAddress Address, int event)
{
    string File_Name, chunk, reqflag, s;
    chunk = "";
    reqflag = "";
    string temp ="0";

    switch (event)
    {
    case 1:
        File_Name = "Iron_Man.mp4";
        chunk = "000";
        reqflag = "00";
        s = reqflag+chunk+File_Name;
//        cout << "file name is " << File_Name << ", chunk is " << chunk << ", reqflag is " << reqflag <<endl; - was needed for testing
//        cout << "response will be " << s <<  " for event: "<< event << endl; - was needed for testing
        break;

    case 2:
        File_Name = "017040.0.0.23050.0.0.2";
        s = reqflag+chunk+File_Name;
//        cout << "file name is " << File_Name << ", chunk is " << chunk << ", reqflag is " << reqflag <<endl; - was needed for testing
//        cout << "response will be " << s <<  " for event: "<< event << endl; - was needed for testing
        break;

    case 3:
        File_Name = obj.get_File_Name();
        chunk = "070";
        reqflag = "10";
        s = reqflag+chunk+File_Name;
//        cout << "file name is " << File_Name << ", chunk is " << chunk << ", reqflag is " << reqflag <<endl; - was needed for testing
//        cout << "response will be " << s <<  " for event: "<< event << endl; - was needed for testing
        break;

    case 4:
        File_Name = "Iron_Man.mp4";
        chunk = "070";
        reqflag = "11";
        s = reqflag+chunk+File_Name;
//        cout << "file name is " << File_Name << ", chunk is " << chunk << ", reqflag is " << reqflag <<endl; - was needed for testing
//        cout << "response will be " << s <<  " for event: "<< event << endl; - was needed for testing
        break;

    case 5:
        File_Name = obj.get_File_Name();
        chunk = temp+obj.get_chunk2();
        reqflag = "10";
        s = reqflag+chunk+File_Name;
//        cout << "file name is " << File_Name << ", chunk is " << chunk << ", reqflag is " << reqflag <<endl; - was needed for testing
//        cout << "response will be " << s <<  " for event: "<< event << endl; - was needed for testing
        break;

    case 6:
        File_Name = "Iron_Man.mp4";
        chunk = "030";
        reqflag = "11";
        s = reqflag+chunk+File_Name;
//        cout << "file name is " << File_Name << ", chunk is " << chunk << ", reqflag is " << reqflag <<endl; - was needed for testing
//        cout << "response will be " << s <<  " for event: "<< event << endl; - was needed for testing
        break;
    }
    socket->Connect (Address);
    const char *ss;
    ss=s.c_str();
    cout << "at=" << Simulator::Now ().GetSeconds () << " Sent Data "<< s <<endl;
    socket->Send (Create<Packet> (reinterpret_cast<const uint8_t*>(ss),s.size()));
    socket->Close ();
}

// function for processing request

static void process_request(char *buf)
{
 // cout << "buffer is " << buf << endl; - was needed for testing
  int j,c=0;
  char req[3];
  req[0] = buf[0];
  req[1] = buf[1];
  req[2] = '\0';
  char File_Name[15];
  for (j=5; j<= 16; j++)
    {
      File_Name[c] = buf[j];
      c++;
    }
  //cout << "req flag is " << req << " file name requested is " << File_Name << endl;- was needed for testing

  if (req[0]=='0' &&req[1] =='0')
  {
    obj.put_file_name(File_Name);
  }
}


// this function is used for accepting one packet, gets the corresponding socket as input

static void Socket_Printer (Ptr<Socket> socket)
{
  char buf[1024]="0";//thisisunnecessar
  uint32_t flags = 0;
 // cout << "printed by Socket_Printer, node is :" << socket->GetNode() <<endl; - was needed for testing
  while(socket->Recv (reinterpret_cast <uint8_t*>(buf),sizeof(buf),flags))
  {
     cout << "at=" << Simulator::Now ().GetSeconds () << " received Data is "<< buf<<endl;
  }
  if (count1 == 1)
  {
      process_request(buf);
      count1++;
  }
  if (buf[12] != '.')
  {
      obj.Load_Info(buf);
      count1++;
  }
}


static void Print_Traffic (Ptr<Socket> socket)
{
 // cout <<"printed by Print_Traffic, node is :" << socket->GetNode()  << " at time " <<Simulator::Now()<< endl; - was needed for testing
  socket->Listen();
  socket->SetRecvCallback (MakeCallback (&Socket_Printer));
}

void
Run_Simulation (void)
{
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  string animFile = "project-scenario-PR.xml" ;  // Name of file for animation output

  // initialize the tx buffer.
  for(uint32_t i = 0; i < write_Size; ++i)
    {
      char m = toascii (97 + i % 26);
      data[i] = m;
      // the above statements write a-->z over and over again into data[] - Pradeep
    }

  //             n3
  //             |
  //n0-r0-r1-r2-n1--n2

  NodeContainer n0_r0;
  n0_r0.Create (2);

  NodeContainer r0_r1;
  r0_r1.Add (n0_r0.Get(1));
  r0_r1.Create (1);

  NodeContainer r1_r2;
  r1_r2.Add (r0_r1.Get(1));
  r1_r2.Create (1);

  NodeContainer r2_n1;
  r2_n1.Add (r1_r2.Get(1));
  r2_n1.Create (1);

  NodeContainer n1_n2;
  n1_n2.Add (r2_n1.Get (1));
  n1_n2.Create (1);

  NodeContainer n1_n3;
  n1_n3.Add (r2_n1.Get (1));
  n1_n3.Create (1);


  PointToPointHelper p2p_n0_r0;
  p2p_n0_r0.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n0_r0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r0_r1;
  p2p_r0_r1.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r0_r1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r1_r2;
  p2p_r1_r2.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r1_r2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r2_n1;
  p2p_r2_n1.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r2_n1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_n1_n2;
  p2p_n1_n2.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n1_n2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_n1_n3;
  p2p_n1_n2.SetDeviceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n1_n2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  NetDeviceContainer dev0 = p2p_n0_r0.Install (n0_r0);
  NetDeviceContainer dev1 = p2p_r0_r1.Install (r0_r1);
  NetDeviceContainer dev2 = p2p_r1_r2.Install (r1_r2);
  NetDeviceContainer dev3 = p2p_r2_n1.Install (r2_n1);
  NetDeviceContainer dev4 = p2p_n1_n2.Install (n1_n2);
  NetDeviceContainer dev5 = p2p_n1_n3.Install (n1_n3);

  InternetStackHelper internet;
  internet.InstallAll ();

  Ipv4_AddressHelper ipv4;
  ipv4.SetBase ("30.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer ipn0_r0 = ipv4.Assign (dev0);
  ipv4.SetBase ("40.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer ipr0_r1 = ipv4.Assign (dev1);
  ipv4.SetBase ("50.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer ipr1_r2 = ipv4.Assign (dev2);
  ipv4.SetBase ("60.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer ipr2_n1 = ipv4.Assign (dev3);
  ipv4.SetBase ("70.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer ipn1_n2 = ipv4.Assign (dev4);
  ipv4.SetBase ("80.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer ipn1_n3 = ipv4.Assign (dev5);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory"); //TCP isn't working

// create ipv4 address and the inetsocket address for router
  Address RouterAddress (InetSocketAddress (ipr2_n1.GetAddress (1), 54000));
  InetSocketAddress Router_Address = InetSocketAddress::ConvertFrom (RouterAddress);

// create ipv4 address and the inetsocket address for client - used for communication with router

  Address clientAddressRxR (InetSocketAddress (ipn0_r0.GetAddress (0), 45001));
  InetSocketAddress client_AddressRxR = InetSocketAddress::ConvertFrom (clientAddressRxR);

// create ipv4 address and the inetsocket address for OP

  Address OPAddress (InetSocketAddress (ipn1_n2.GetAddress (1), 54391));
  InetSocketAddress OP_Address = InetSocketAddress::ConvertFrom (OPAddress);

// create ipv4 address and the inetsocket address for client - used for sending data to OP

  Address clientAddressTxOP (InetSocketAddress (ipn0_r0.GetAddress (0), 45000));
  InetSocketAddress client_AddressTxOP = InetSocketAddress::ConvertFrom (clientAddressTxOP);
//  cout << client_AddressTxOP << " " << clientAddressTxOP <<endl; - was needed for testing

// create ipv4 address and the inetsocket address for client - used for receiving data from OP

  Address clientAddressRxOP (InetSocketAddress (ipn0_r0.GetAddress (0), 45001));
  InetSocketAddress client_AddressRxOP = InetSocketAddress::ConvertFrom (clientAddressRxOP);

// create ipv4 address and the inetsocket address for client - used for sending data to AP

  Address clientAddressTxAP (InetSocketAddress (ipn0_r0.GetAddress (0), 45000));
  InetSocketAddress client_AddressTxAP = InetSocketAddress::ConvertFrom (clientAddressTxAP);

// create ipv4 address and the inetsocket address for client - used for receiving data from AP

  Address clientAddressRxAP (InetSocketAddress (ipn0_r0.GetAddress (0), 45001));
  InetSocketAddress client_AddressRxAP = InetSocketAddress::ConvertFrom (clientAddressRxAP);

// create ipv4 address and the inetsocket address for AP

  Address APAddress (InetSocketAddress (ipn1_n3.GetAddress (1), 54391));
  InetSocketAddress AP_Address = InetSocketAddress::ConvertFrom (APAddress);

//Enable packet capture

  AsciiTraceHelper ascii;
  p2p_n0_r0.EnableAsciiAll (ascii.CreateFileStream ("project-scenario-PR"));
  p2p_n0_r0.EnablePcapAll ("project-scenario-PR");

// Packet Description
// first 2 characters represent type of request - 00 file request, 01 response for file request, 10 download request, 11 OK response
// next 3 characters represent chunk numbers
// next comes the file name Iron_Man.mp4


// event 1 : Client contacts OP asking for the file : packet is 00000Iron_Man.mp4

  Ptr<Socket> OPrx_event1 = Socket::CreateSocket (n1_n2.Get (1), tid);
  Ptr<Socket> clienttx_event1 = Socket::CreateSocket (n0_r0.Get (0), tid);
  OPrx_event1->Bind (OP_Address);
  clienttx_event1->Bind(client_AddressTxOP);

  Simulator::Schedule (Seconds(0.0), &Generate_Traffic, clienttx_event1, OP_Address, 1);
  Simulator::Schedule (Seconds(0.0), &Print_Traffic, OPrx_event1);

// event 2 : Router sends 1 packet informing client to contact OP for 70% of the load and AP for 30% of the load : packet is 017040.0.0.23050.0.0.2

  Ptr<Socket> Routertx_event2 = Socket::CreateSocket (r2_n1.Get (1), tid);
  Ptr<Socket> clientrx_event2 = Socket::CreateSocket (n0_r0.Get (0), tid);
  clientrx_event2->Bind(client_AddressRxR);
  Routertx_event2->Bind (Router_Address);

  Simulator::Schedule (Seconds(0.05), &Generate_Traffic, Routertx_event2, client_AddressRxR, 2); //,2
  Simulator::Schedule (Seconds(0.05), &Print_Traffic, clientrx_event2);


// event 3 : Client --> OP Download request : packet is 10070Iron_Man.mp4

  Ptr<Socket> OPrx_event3 = Socket::CreateSocket (n1_n2.Get (1), tid);
  Ptr<Socket> clienttx_event3 = Socket::CreateSocket (n0_r0.Get (0), tid);
  OPrx_event3->Bind (OP_Address);
  clienttx_event3->Bind(client_AddressTxOP);

  Simulator::Schedule (Seconds(0.1), &Generate_Traffic, clienttx_event3, OP_Address, 3);
  Simulator::Schedule (Seconds(0.1), &Print_Traffic, OPrx_event3);

// event 4 : OP --> client Ok response : packet is 11070Iron_Man.mp4

  Ptr<Socket> OPtx_event4 = Socket::CreateSocket (n1_n2.Get (1), tid);
  Ptr<Socket> clientrx_event4 = Socket::CreateSocket (n0_r0.Get (0), tid);
  clientrx_event4->Bind(client_AddressRxOP);
  OPtx_event4->Bind (OP_Address);

  Simulator::Schedule (Seconds(0.15), &Generate_Traffic, OPtx_event4, client_AddressRxOP, 4);
  Simulator::Schedule (Seconds(0.15), &Print_Traffic, clientrx_event4);

// event 5 : client --> AP Download request : packet is 10030Iron_Man.mp4

  Ptr<Socket> APrx_event5 = Socket::CreateSocket (n1_n3.Get (1), tid);
  Ptr<Socket> clienttx_event5 = Socket::CreateSocket (n0_r0.Get (0), tid);
  APrx_event5->Bind (AP_Address);
  clienttx_event5->Bind(client_AddressTxAP);

  Simulator::Schedule (Seconds(0.2), &Generate_Traffic, clienttx_event5, AP_Address, 5);
  Simulator::Schedule (Seconds(0.2), &Print_Traffic, APrx_event5);

// event 6 : AP --> client Ok response : packet is 11030Iron_Man.mp4

  Ptr<Socket> APtx_event6 = Socket::CreateSocket (n1_n3.Get (1), tid);
  Ptr<Socket> clientrx_event6 = Socket::CreateSocket (n0_r0.Get (0), tid);
  APtx_event6->Bind (AP_Address);
  clientrx_event6->Bind(client_AddressRxAP);

  Simulator::Schedule (Seconds(0.25), &Generate_Traffic, APtx_event6, client_AddressRxAP, 6);
  Simulator::Schedule (Seconds(0.25), &Print_Traffic, clientrx_event6);

  //usleep(5000000); // sleep for 5 seconds
  uint16_t servPort = 50000;

  PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4_Address::GetAny (), servPort));

  ApplicationContainer apps = sink1.Install (n0_r0.Get (0)); //sink is installed on the node 1 in n1_n2 selection, which is n2 - Pradeep - changed from n1_n2 to n0n1.get(0)
  apps.Start (Seconds (1.0)); // changed 5 to 1
  apps.Stop (Seconds (10.0));

  Ptr<Socket> localSocket1 = Socket::CreateSocket (n1_n2.Get (1), TcpSocketFactory::GetTypeId ()); // changed from n0n1.get(0) to n1_n2.get(1)
  localSocket1->Bind ();
//  Config::ConnectWithoutContext ("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&CwndTracer));

  Simulator::Schedule (Seconds (5.0),&Start_Flow_OP, localSocket1, ipn0_r0.GetAddress (0), servPort); // changed ipn1_n2.getaddress(1) to ipn0_r0.getaddress(0) schedulenow takes address of method to invoke, object on which the method has to be invoked and the arguments to be passed to the method. So here, we invoke the StartFlow method, which takes the 3 arguments
  //cout << "executed at time : "<< Simulator::Now ().GetSeconds () << endl; - was needed for testing

  PacketSinkHelper sink2 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4_Address::GetAny (), servPort));

  ApplicationContainer apps1 = sink2.Install (n0_r0.Get (0)); //sink is installed on the node 1 in n1_n2 selection, which is n2 - Pradeep - changed from n1_n2 to n0n1.get(0)
  apps1.Start (Seconds (1.0)); // changed 5 to 1
  apps1.Stop (Seconds (10.0));

  Ptr<Socket> localSocket2 = Socket::CreateSocket (n1_n3.Get (1), TcpSocketFactory::GetTypeId ()); // changed from n0n1.get(0) to n1_n2.get(1)
  localSocket2->Bind ();
//  Config::ConnectWithoutContext ("/NodeList/0/$ns3::TcpL4Protocol/SocketList/0/CongestionWindow", MakeCallback (&CwndTracer));

  Simulator::Schedule (Seconds (5.0),&Start_Flow_AP, localSocket2, ipn0_r0.GetAddress (0), servPort); // changed ipn1_n2.getaddress(1) to ipn0_r0.getaddress(0) schedulenow takes address of method to invoke, object on which the method has to be invoked and the arguments to be passed to the method. So here, we invoke the StartFlow method, which takes the 3 arguments
  //cout << "executed at time : "<< Simulator::Now ().GetSeconds () << endl; - was needed for testing

  NodeContainer c;
  c.Add(n0_r0);
  c.Add(r1_r2);
  c.Add(n1_n2);
  c.Add(n1_n3.Get(1));

  double distance = 500;
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator", "MinX", DoubleValue (0.0), "MinY", DoubleValue (0.0), "DeltaX", DoubleValue (distance), "DeltaY", DoubleValue (distance), "GridWidth", UintegerValue (5), "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (c);

  AnimationInterface anim (animFile);
  Simulator::Run ();
  cout << "Animation Trace file created:" << animFile.c_str ()<< endl;
  Simulator::Destroy ();

}

NS_LOG_COMPONENT_DEFINE ("TcpLargeTransfer");

// The number of bytes to send in this simulation.

int main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Run_Simulation();
  return 0;

}

void Start_Flow_OP (Ptr<Socket> localSocket, Ipv4_Address servAddress, uint16_t servPort)
{
  NS_LOG_LOGIC ("Starting flow at time " <<  Simulator::Now ().GetSeconds ());
  localSocket->Connect (InetSocketAddress (servAddress, servPort)); //connect
  // tell the tcp implementation to call WriteUntilBufferFull again
  // if we blocked and new tx buffer space becomes available
  localSocket->SetSendCallback (MakeCallback (&Write_Until_Buffer_Full_OP));
  Write_Until_Buffer_Full_OP (localSocket, localSocket->GetTxAvailable ());
}

void Write_Until_Buffer_Full_OP (Ptr<Socket> localSocket, uint32_t txSpace)
{
  while (current_Tx_Bytes < total_Tx_Bytes_OP && localSocket->GetTxAvailable () > 0)
    {
      uint32_t left = total_Tx_Bytes_OP - current_Tx_Bytes;
      uint32_t dataOffset = current_Tx_Bytes % write_Size;
      uint32_t toWrite = write_Size - dataOffset;
      toWrite = std::min (toWrite, left);
      toWrite = std::min (toWrite, localSocket->GetTxAvailable ());
      int amountSent = localSocket->Send (&data[dataOffset], toWrite, 0);
      if(amountSent < 0)
        {
          // we will be called again when new tx space becomes available.
          return;
        }
      current_Tx_Bytes += amountSent;
    }
  localSocket->Close ();
}

void Start_Flow_AP (Ptr<Socket> localSocket, Ipv4_Address servAddress, uint16_t servPort)
{
  NS_LOG_LOGIC ("Starting flow at time " <<  Simulator::Now ().GetSeconds ());
  localSocket->Connect (InetSocketAddress (servAddress, servPort)); //connect
  // tell the tcp implementation to call WriteUntilBufferFull again
  // if we blocked and new tx buffer space becomes available
  localSocket->SetSendCallback (MakeCallback (&Write_Until_Buffer_Full_AP));
  Write_Until_Buffer_Full_AP (localSocket, localSocket->GetTxAvailable ());
}

void Write_Until_Buffer_Full_AP (Ptr<Socket> localSocket, uint32_t txSpace)
{
  while (current_Tx_Bytes < total_Tx_Bytes_AP && localSocket->GetTxAvailable () > 0)
    {
      uint32_t left = total_Tx_Bytes_AP - current_Tx_Bytes;
      uint32_t dataOffset = current_Tx_Bytes % write_Size;
      uint32_t toWrite = write_Size - dataOffset;
      toWrite = std::min (toWrite, left);
      toWrite = std::min (toWrite, localSocket->GetTxAvailable ());
      int amountSent = localSocket->Send (&data[dataOffset], toWrite, 0);
      if(amountSent < 0)
        {
          // we will be called again when new tx space becomes available.
          return;
        }
      current_Tx_Bytes += amountSent;
    }
  localSocket->Close ();
}
