//Project Scenario is only for OP, AP, PR and Client with 6 Peers

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
static const uint32_t ws = 1040;
static uint32_t CTB = 0;
uint8_t data[ws];
static const uint32_t totalTxBytesOP = 2000000; // Data sent, in bytes will be - 2000000 from OP
void sFlowOP (Ptr<Socket>, Ipv4Address, uint16_t);
void WriteUntilBufFulOP (Ptr<Socket>, uint32_t);


void RunSimulation (void)
{

  string animFile = "project-scenario-p2p-6P.xml" ;  // Name of file for animation output

  // initialize the tx buffer.
  for(uint32_t i = 0; i < ws; ++i)
    {
      char m = toascii (97 + i % 26);
      data[i] = m;
      // the above statements write a-->z over and over again into data[] 
    }

  NodeContainer node2route0;
  node2route0.Create (2);

  NodeContainer route2node0;
  route2node0.Add (node2route0.Get (1));
  route2node0.Create (1);

  NodeContainer route0node1;
  route0node1.Add (node2route0.Get (1));
  route0node1.Create (1);

  NodeContainer node2route1;
  node2route1.Add (node2route0.Get (0));
  node2route1.Create (1);

  NodeContainer route1node3;
  route1node3.Add (node2route1.Get (1));
  route1node3.Create (1);

  NodeContainer route1node4;
  route1node4.Add (node2route1.Get (1));
  route1node4.Create (1);

  NodeContainer node2route2;
  node2route2.Add (node2route0.Get (0));
  node2route2.Create (1);

  NodeContainer route2node5;
  route2node5.Add (node2route2.Get (1));
  route2node5.Create (1);

  NodeContainer r2n6;
  r2n6.Add (node2route2.Get (1));
  r2n6.Create (1);

  PointToPointHelper p2p_node2route0;
  p2p_node2route0.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route2node0;
  p2p_route2node0.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route2node0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route0node1;
  p2p_route0node1.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route0node1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_node2route1;
  p2p_node2route1.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route1node3;
  p2p_route1node3.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route1node3.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route1node4;
  p2p_route1node4.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route1node4.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_node2route2;
  p2p_node2route2.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route2node5;
  p2p_route2node5.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route2node5.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r2n6;
  p2p_r2n6.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r2n6.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));


  NetdeviceiceContainer deviceice0 = p2p_node2route0.Install (node2route0);
  NetdeviceiceContainer deviceice1 = p2p_route2node0.Install (route2node0);
  NetdeviceiceContainer device2 = p2p_route0node1.Install (route0node1);
  NetdeviceiceContainer device3 = p2p_node2route1.Install (node2route1);
  NetdeviceiceContainer device4 = p2p_route1node3.Install (route1node3);
  NetdeviceiceContainer device5 = p2p_route1node4.Install (route1node4);
  NetdeviceiceContainer device6 = p2p_node2route2.Install (node2route2);
  NetdeviceiceContainer device7 = p2p_route2node5.Install (route2node5);
  NetdeviceiceContainer device8 = p2p_r2n6.Install (r2n6);


  InternetStackHelper internet;
  internet.InstallAll ();

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("30.1.0.0", "255.255.255.0"); //node2route0
  Ipv4InterfaceContainer ipnode2route0 = ipv4.Assign (deviceice0);
  ipv4.SetBase ("30.2.0.0", "255.255.255.0"); //route2node0
  Ipv4InterfaceContainer iproute2node0 = ipv4.Assign (deviceice0);
  ipv4.SetBase ("30.3.0.0", "255.255.255.0"); //route0node1
  Ipv4InterfaceContainer iproute0node1 = ipv4.Assign (device2);
  ipv4.SetBase ("30.4.0.0", "255.255.255.0"); //node2route1
  Ipv4InterfaceContainer ipnode2route1 = ipv4.Assign (device3);
  ipv4.SetBase ("30.5.0.0", "255.255.255.0"); //route1node3
  Ipv4InterfaceContainer iproute1node3 = ipv4.Assign (device4);
  ipv4.SetBase ("30.6.0.0", "255.255.255.0"); //route1node4
  Ipv4InterfaceContainer iproute1node4 = ipv4.Assign (device5);
  ipv4.SetBase ("30.7.0.0", "255.255.255.0"); //node2route2
  Ipv4InterfaceContainer ipnode2route2 = ipv4.Assign (device6);
  ipv4.SetBase ("30.8.0.0", "255.255.255.0"); //route2node5
  Ipv4InterfaceContainer iproute2node5 = ipv4.Assign (device7);
  ipv4.SetBase ("30.9.0.0", "255.255.255.0"); //r2n6
  Ipv4InterfaceContainer ipr2n6 = ipv4.Assign (device8);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

//Enable packet capture

  AsciiTraceHelper ascii;
  p2p_node2route0.EnableAsciiAll (ascii.CreateFileStream ("project-scenario-p2p"));
  p2p_node2route0.EnablePcapAll ("project-scenario-p2p");

  //usleep(5000000); // sleep for 5 seconds
  uint16_t servPort = 50000;

  PacketSHelper S1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), servPort));

  ApplicationContainer apps1 = S1.Install (route2node0.Get (1));
  apps1.Start (Seconds (1.0)); // changed 5 to 1
  apps1.Stop (Seconds (60.0));

  PacketSHelper S2 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), servPort));

  ApplicationContainer apps2 = S2.Install (route1node4.Get (1));
  apps2.Start (Seconds (1.0)); // changed 5 to 1
  apps2.Stop (Seconds (60.0));

  PacketSHelper S3 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), servPort));

  ApplicationContainer apps3 = S3.Install (route2node5.Get (1));
  apps3.Start (Seconds (1.0)); // changed 5 to 1
  apps3.Stop (Seconds (60.0));

  PacketSHelper S4 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), servPort));

  ApplicationContainer apps4 = S4.Install (r2n6.Get (1));
  apps4.Start (Seconds (1.0)); // changed 5 to 1
  apps4.Stop (Seconds (60.0));

  PacketSHelper S5 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), servPort));

  ApplicationContainer apps5 = S5.Install (route1node3.Get (1));
  apps5.Start (Seconds (1.0)); // changed 5 to 1
  apps5.Stop (Seconds (30.0));

  PacketSHelper S6 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), servPort));

  ApplicationContainer apps6 = S6.Install (route0node1.Get (1));
  apps6.Start (Seconds (1.0)); // changed 5 to 1
  apps6.Stop (Seconds (60.0));

  Ptr<Socket> localSocket1 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  localSocket1->Bind ();

  Ptr<Socket> localSocket2 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  localSocket2->Bind ();

  Ptr<Socket> localSocket3 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  localSocket3->Bind ();

  Ptr<Socket> localSocket4 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  localSocket4->Bind ();

  Ptr<Socket> localSocket5 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  localSocket5->Bind ();

  Ptr<Socket> localSocket6 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  localSocket6->Bind ();

  Simulator::Schedule (Seconds (1.05),&sFlowOP, localSocket1, iproute2node0.GetAddress (1), servPort);
  Simulator::Schedule (Seconds (1.05),&sFlowOP, localSocket2, iproute1node4.GetAddress (1), servPort);
  Simulator::Schedule (Seconds (1.05),&sFlowOP, localSocket3, iproute2node5.GetAddress (1), servPort);
  Simulator::Schedule (Seconds (1.05),&sFlowOP, localSocket4, ipr2n6.GetAddress (1), servPort);
  Simulator::Schedule (Seconds (1.05),&sFlowOP, localSocket5, iproute1node3.GetAddress (1), servPort);
  Simulator::Schedule (Seconds (1.05),&sFlowOP, localSocket6, iproute0node1.GetAddress (1), servPort);
  //cout << "executed at time : "<< Simulator::Now ().GetSeconds () << endl; - was needed for testing

  NodeContainer c;
  c.Add(route2node0.Get(1));
  c.Add(route2node0.Get(0));
  c.Add(node2route0.Get(0));
  c.Add(node2route2.Get(1));
  c.Add(r2n6.Get(1));
  c.Add(route0node1.Get(1));
  c.Add(route1node3.Get(1));
  c.Add(route1node3.Get(0));
  c.Add(route1node4.Get(1));
  c.Add(route2node5.Get(1));

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
  CommandLine command;
  command.Parse (argc, argv);
  RunSimulation();
  return 0;

}

void sFlowOP (Ptr<Socket> localSocket, Ipv4Address servAddress, uint16_t servPort)
{
  NS_LOG_LOGIC ("Starting flow at time " <<  Simulator::Now ().GetSeconds ());
  localSocket->Connect (InetSocketAddress (servAddress, servPort)); //connect
  // tell the tcp implementation to call WriteUntilBufferFull again
  // if we blocked and new tx buffer space becomes available
  localSocket->SetSendCallback (MakeCallback (&WriteUntilBufFulOP));
  WriteUntilBufFulOP (localSocket, localSocket->GetTxAvailable ());
}

void WriteUntilBufFulOP (Ptr<Socket> localSocket, uint32_t txSpace)
{
  while (CTB < totalTxBytesOP && localSocket->GetTxAvailable () > 0)
    {
      uint32_t left = totalTxBytesOP - CTB;
      uint32_t dataOffset = CTB % ws;
      uint32_t toWrite = ws - dataOffset;
      toWrite = std::min (toWrite, left);
      toWrite = std::min (toWrite, localSocket->GetTxAvailable ());
      int amountSent = localSocket->Send (&data[dataOffset], toWrite, 0);
      if(amountSent < 0)
        {
          // we will be called again when new tx space becomes available.
          return;
        }
      CTB += amountSent;
    }
 // cout << "write complete at " << Simulator::Now ().GetSeconds ()<<endl;
  localSocket->Close ();
}
