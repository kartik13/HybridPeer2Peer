//Project Scenario - only OP, AP, PR and Client

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
static const uint32_t writeSize = 1040;
static uint32_t currentTxBytes = 0;
uint8_t data[writeSize];
static const uint32_t totalTxBytesOP = 2000000; // Data sent, in bytes will be - 2000000 from OP
void StartFlow (Ptr<Socket>, Ipv4Address, uint16_t);
void WriteUntilBufFulOP (Ptr<Socket>, uint32_t);


void RunSimulation (void)
{

  string animFile = "project-scenario-p2p-16P.xml" ;  // Name of file for animation output

  // initialize the tx buffer.
  for(uint32_t i = 0; i < writeSize; ++i)
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

  NodeContainer node2route6;
  node2route6.Add (node2route0.Get (0));
  node2route6.Create (1);

  NodeContainer node2route7;
  node2route7.Add (node2route0.Get (0));
  node2route7.Create (1);

  NodeContainer route0node0;
  route0node0.Add (node2route0.Get (1));
  route0node0.Create (1);

  NodeContainer route0node1;
  route0node1.Add (node2route0.Get (1));
  route0node1.Create (1);

  NodeContainer route1node3;
  route1node3.Add (node2route1.Get (1));
  route1node3.Create (1);

  NodeContainer r1n4;
  r1n4.Add (node2route1.Get (1));
  r1n4.Create (1);

  NodeContainer r2n5;
  r2n5.Add (n2r2.Get (1));
  r2n5.Create (1);

  NodeContainer r2n6;
  r2n6.Add (n2r2.Get (1));
  r2n6.Create (1);

  NodeContainer r3n7;
  r3n7.Add (n2r3.Get (1));
  r3n7.Create (1);

  NodeContainer r3n8;
  r3n8.Add (n2r3.Get (1));
  r3n8.Create (1);

  NodeContainer r4n9;
  r4n9.Add (n2r4.Get (1));
  r4n9.Create (1);

  NodeContainer r4n10;
  r4n10.Add (n2r4.Get (1));
  r4n10.Create (1);

  NodeContainer r5n11;
  r5n11.Add (n2r5.Get (1));
  r5n11.Create (1);

  NodeContainer r5n12;
  r5n12.Add (n2r5.Get (1));
  r5n12.Create (1);

  NodeContainer r6n13;
  r6n13.Add (node2route6.Get (1));
  r6n13.Create (1);

  NodeContainer r6n14;
  r6n14.Add (node2route6.Get (1));
  r6n14.Create (1);

  NodeContainer r7n15;
  r7n15.Add (node2route7.Get (1));
  r7n15.Create (1);

  NodeContainer r7n16;
  r7n16.Add (node2route7.Get (1));
  r7n16.Create (1);

  PointToPointHelper p2p_node2route0;
  p2p_node2route0.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_node2route1;
  p2p_node2route1.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_n2r2;
  p2p_n2r2.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n2r2.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_n2r3;
  p2p_n2r3.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n2r3.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_n2r4;
  p2p_n2r4.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n2r4.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_n2r5;
  p2p_n2r5.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_n2r5.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_node2route6;
  p2p_node2route6.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route6.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_node2route7;
  p2p_node2route7.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_node2route7.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route0node0;
  p2p_route0node0.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route0node0.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route0node1;
  p2p_route0node1.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route0node1.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_route1node3;
  p2p_route1node3.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_route1node3.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r1n4;
  p2p_r1n4.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r1n4.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r2n5;
  p2p_r2n5.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r2n5.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r2n6;
  p2p_r2n6.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r2n6.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r3n7;
  p2p_r3n7.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r3n7.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r3n8;
  p2p_r3n8.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r3n8.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r4n9;
  p2p_r4n9.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r4n9.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r4n10;
  p2p_r4n10.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r4n10.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r5n11;
  p2p_r5n11.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r5n11.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r5n12;
  p2p_r5n12.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r5n12.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r6n13;
  p2p_r6n13.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r6n13.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r6n14;
  p2p_r6n14.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r6n14.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r7n15;
  p2p_r7n15.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r7n15.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  PointToPointHelper p2p_r7n16;
  p2p_r7n16.SetdeviceiceAttribute ("DataRate", DataRateValue (DataRate (10000000)));
  p2p_r7n16.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (10)));

  NetdeviceiceContainer device0 = p2p_node2route0.Install (node2route0);
  NetdeviceiceContainer device1 = p2p_route0node0.Install (route0node0);
  NetdeviceiceContainer device2 = p2p_route0node1.Install (route0node1);
  NetdeviceiceContainer device3 = p2p_node2route1.Install (node2route1);
  NetdeviceiceContainer device4 = p2p_route1node3.Install (route1node3);
  NetdeviceiceContainer device5 = p2p_r1n4.Install (r1n4);
  NetdeviceiceContainer device6 = p2p_n2r2.Install (n2r2);
  NetdeviceiceContainer device7 = p2p_r2n5.Install (r2n5);
  NetdeviceiceContainer device8 = p2p_r2n6.Install (r2n6);
  NetdeviceiceContainer device9 = p2p_n2r3.Install (n2r3);
  NetdeviceiceContainer device10 = p2p_r3n7.Install (r3n7);
  NetdeviceiceContainer device11 = p2p_r3n8.Install (r3n8);
  NetdeviceiceContainer device12 = p2p_n2r4.Install (n2r4);
  NetdeviceiceContainer device13 = p2p_r4n9.Install (r4n9);
  NetdeviceiceContainer device14 = p2p_r4n10.Install (r4n10);
  NetdeviceiceContainer device15 = p2p_n2r5.Install (n2r5);
  NetdeviceiceContainer device16 = p2p_r5n11.Install (r5n11);
  NetdeviceiceContainer device17 = p2p_r5n12.Install (r5n12);
  NetdeviceiceContainer device18 = p2p_node2route6.Install (node2route6);
  NetdeviceiceContainer device19 = p2p_r6n13.Install (r6n13);
  NetdeviceiceContainer device20 = p2p_r6n14.Install (r6n14);
  NetdeviceiceContainer device21 = p2p_node2route7.Install (node2route7);
  NetdeviceiceContainer device22 = p2p_r7n15.Install (r7n15);
  NetdeviceiceContainer device23 = p2p_r7n16.Install (r7n16);

  InternetStackHelper internet;
  internet.InstallAll ();

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("30.1.0.0", "255.255.255.0"); //node2route0
  Ipv4InterfaceContainer ipnode2route0 = ipv4.Assign (device0);
  ipv4.SetBase ("30.2.0.0", "255.255.255.0"); //route0node0
  Ipv4InterfaceContainer iproute0node0 = ipv4.Assign (device1);
  ipv4.SetBase ("30.3.0.0", "255.255.255.0"); //route0node1
  Ipv4InterfaceContainer iproute0node1 = ipv4.Assign (device2);
  ipv4.SetBase ("30.4.0.0", "255.255.255.0"); //node2route1
  Ipv4InterfaceContainer ipnode2route1 = ipv4.Assign (device3);
  ipv4.SetBase ("30.5.0.0", "255.255.255.0"); //route1node3
  Ipv4InterfaceContainer iproute1node3 = ipv4.Assign (device4);
  ipv4.SetBase ("30.6.0.0", "255.255.255.0"); //r1n4
  Ipv4InterfaceContainer ipr1n4 = ipv4.Assign (device5);
  ipv4.SetBase ("30.7.0.0", "255.255.255.0"); //n2r2
  Ipv4InterfaceContainer ipn2r2 = ipv4.Assign (device6);
  ipv4.SetBase ("30.8.0.0", "255.255.255.0"); //r2n5
  Ipv4InterfaceContainer ipr2n5 = ipv4.Assign (device7);
  ipv4.SetBase ("30.9.0.0", "255.255.255.0"); //r2n6
  Ipv4InterfaceContainer ipr2n6 = ipv4.Assign (device8);
  ipv4.SetBase ("30.10.0.0", "255.255.255.0"); //n2r3
  Ipv4InterfaceContainer ipn2r3 = ipv4.Assign (device9);
  ipv4.SetBase ("30.11.0.0", "255.255.255.0"); //r3n7
  Ipv4InterfaceContainer ipr3n7 = ipv4.Assign (device10);
  ipv4.SetBase ("30.12.0.0", "255.255.255.0"); //r3n8
  Ipv4InterfaceContainer ipr3n8 = ipv4.Assign (device11);
  ipv4.SetBase ("30.13.0.0", "255.255.255.0"); //n2r4
  Ipv4InterfaceContainer ipn2r4 = ipv4.Assign (device12);
  ipv4.SetBase ("30.14.0.0", "255.255.255.0"); //r4n9
  Ipv4InterfaceContainer ipr4n9 = ipv4.Assign (device13);
  ipv4.SetBase ("30.15.0.0", "255.255.255.0"); //r4n10
  Ipv4InterfaceContainer ipr4n10 = ipv4.Assign (device14);
  ipv4.SetBase ("30.16.0.0", "255.255.255.0"); //n2r5
  Ipv4InterfaceContainer ipn2r5 = ipv4.Assign (device15);
  ipv4.SetBase ("30.17.0.0", "255.255.255.0"); //r5n11
  Ipv4InterfaceContainer ipr5n11 = ipv4.Assign (device16);
  ipv4.SetBase ("30.18.0.0", "255.255.255.0"); //r5n12
  Ipv4InterfaceContainer ipr5n12 = ipv4.Assign (device17);
  ipv4.SetBase ("30.19.0.0", "255.255.255.0"); //node2route6
  Ipv4InterfaceContainer ipnode2route6 = ipv4.Assign (device18);
  ipv4.SetBase ("30.20.0.0", "255.255.255.0"); //r6n13
  Ipv4InterfaceContainer ipr6n13 = ipv4.Assign (device19);
  ipv4.SetBase ("30.21.0.0", "255.255.255.0"); //r6n14
  Ipv4InterfaceContainer ipr6n14 = ipv4.Assign (device20);
  ipv4.SetBase ("30.22.0.0", "255.255.255.0"); //node2route7
  Ipv4InterfaceContainer ipnode2route7 = ipv4.Assign (device21);
  ipv4.SetBase ("30.23.0.0", "255.255.255.0"); //r7n15
  Ipv4InterfaceContainer ipr7n15 = ipv4.Assign (device22);
  ipv4.SetBase ("30.24.0.0", "255.255.255.0"); //r7n16
  Ipv4InterfaceContainer ipr7n16 = ipv4.Assign (device23);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

//Enable packet capture

  AsciiTraceHelper ascii;
  p2p_node2route0.EnableAsciiAll (ascii.CreateFileStream ("project-scenario-p2p"));
  p2p_node2route0.EnablePcapAll ("project-scenario-p2p");

  //usleep(5000000); // sleep for 5 seconds
  uint16_t serverP = 50000;

  PacketSinkHelper sink1 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application1 = sink1.Install (route0node0.Get (1));
  application1.Start (Seconds (1.0)); // changed 5 to 1
  application1.Stop (Seconds (60.0));

  PacketSinkHelper sink2 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application2 = sink2.Install (r1n4.Get (1));
  application2.Start (Seconds (1.0)); // changed 5 to 1
  application2.Stop (Seconds (60.0));

  PacketSinkHelper sink3 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application3 = sink3.Install (r2n5.Get (1));
  application3.Start (Seconds (1.0)); // changed 5 to 1
  application3.Stop (Seconds (60.0));

  PacketSinkHelper sink4 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application4 = sink4.Install (r2n6.Get (1));
  application4.Start (Seconds (1.0)); // changed 5 to 1
  application4.Stop (Seconds (60.0));

  PacketSinkHelper sink5 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application5 = sink5.Install (route1node3.Get (1));
  application5.Start (Seconds (1.0)); // changed 5 to 1
  application5.Stop (Seconds (30.0));

  PacketSinkHelper sink6 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application6 = sink6.Install (route0node1.Get (1));
  application6.Start (Seconds (1.0)); // changed 5 to 1
  application6.Stop (Seconds (60.0));

  PacketSinkHelper sink7 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application7 = sink7.Install (r3n7.Get (1));
  application7.Start (Seconds (1.0)); // changed 5 to 1
  application7.Stop (Seconds (60.0));

  PacketSinkHelper sink8 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application8 = sink8.Install (r3n8.Get (1));
  application8.Start (Seconds (1.0)); // changed 5 to 1
  application8.Stop (Seconds (30.0));

  PacketSinkHelper sink9 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application9 = sink9.Install (r4n9.Get (1));
  application9.Start (Seconds (1.0)); // changed 5 to 1
  application9.Stop (Seconds (60.0));

  PacketSinkHelper sink10 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application10 = sink10.Install (r4n10.Get (1));
  application10.Start (Seconds (1.0)); // changed 5 to 1
  application10.Stop (Seconds (60.0));

  PacketSinkHelper sink11 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application11 = sink11.Install (r5n11.Get (1));
  application11.Start (Seconds (1.0)); // changed 5 to 1
  application11.Stop (Seconds (60.0));

  PacketSinkHelper sink12 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application12 = sink12.Install (r5n12.Get (1));
  application12.Start (Seconds (1.0)); // changed 5 to 1
  application12.Stop (Seconds (60.0));

  PacketSinkHelper sink13 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application13 = sink13.Install (r6n13.Get (1));
  application13.Start (Seconds (1.0)); // changed 5 to 1
  application13.Stop (Seconds (60.0));

  PacketSinkHelper sink14 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application14 = sink14.Install (r6n14.Get (1));
  application14.Start (Seconds (1.0)); // changed 5 to 1
  application14.Stop (Seconds (60.0));

  PacketSinkHelper sink15 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application15 = sink15.Install (r7n15.Get (1));
  application15.Start (Seconds (1.0)); // changed 5 to 1
  application15.Stop (Seconds (60.0));

  PacketSinkHelper sink16 ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), serverP));

  ApplicationContainer application16 = sink16.Install (r7n16.Get (1));
  application16.Start (Seconds (1.0)); // changed 5 to 1
  application16.Stop (Seconds (60.0));

  Ptr<Socket> loclSoc1 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc1->Bind ();

  Ptr<Socket> loclSoc2 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc2->Bind ();

  Ptr<Socket> loclSoc3 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc3->Bind ();

  Ptr<Socket> loclSoc4 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc4->Bind ();

  Ptr<Socket> loclSoc5 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc5->Bind ();

  Ptr<Socket> loclSoc6 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc6->Bind ();

  Ptr<Socket> loclSoc7 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc7->Bind ();

  Ptr<Socket> loclSoc8 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc8->Bind ();

  Ptr<Socket> loclSoc9 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc9->Bind ();

  Ptr<Socket> loclSoc10 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc10->Bind ();

  Ptr<Socket> loclSoc11 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc11->Bind ();

  Ptr<Socket> loclSoc12 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc12->Bind ();

  Ptr<Socket> loclSoc13 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc13->Bind ();

  Ptr<Socket> loclSoc14 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc14->Bind ();

  Ptr<Socket> loclSoc15 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc15->Bind ();

  Ptr<Socket> loclSoc16 = Socket::CreateSocket (node2route0.Get (0), TcpSocketFactory::GetTypeId ());
  loclSoc16->Bind ();

  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc1, iproute0node0.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc2, ipr1n4.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc3, ipr2n5.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc4, ipr2n6.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc5, iproute1node3.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc6, iproute0node1.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc7, ipr3n7.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc8, ipr3n8.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc9, ipr4n9.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc10, ipr4n10.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc11, ipr5n11.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc12, ipr5n12.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc13, ipr6n13.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc14, ipr6n14.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc15, ipr7n15.GetAddress (1), serverP);
  Simulator::Schedule (Seconds (1.05),&StartFlow, loclSoc16, ipr7n16.GetAddress (1), serverP);

  NodeContainer c;
  c.Add(route0node0.Get(1));
  c.Add(route0node1.Get(1));
  c.Add(route1node3.Get(1));
  c.Add(r1n4.Get(1));
  c.Add(r2n5.Get(1));
  c.Add(r7n16.Get(1));
  c.Add(node2route0.Get(1));
  c.Add(node2route1.Get(1));
  c.Add(n2r2.Get(1));
  c.Add(r2n6.Get(1));
  c.Add(r7n15.Get(1));
  c.Add(node2route7.Get(1));
  c.Add(node2route0.Get(0));
  c.Add(n2r3.Get(1));
  c.Add(r3n7.Get(1));
  c.Add(r6n14.Get(1));
  c.Add(node2route6.Get(1));
  c.Add(n2r5.Get(1));
  c.Add(n2r4.Get(1));
  c.Add(r3n8.Get(1));
  c.Add(r6n13.Get(1));
  c.Add(r5n12.Get(1));
  c.Add(r5n11.Get(1));
  c.Add(r4n10.Get(1));
  c.Add(r4n9.Get(1));

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
  RunSimulation();
  return 0;

}

void StartFlow (Ptr<Socket> loclSoc, Ipv4Address servAddress, uint16_t serverP)
{
  NS_LOG_LOGIC ("Starting flow at time " <<  Simulator::Now ().GetSeconds ());
  loclSoc->Connect (InetSocketAddress (servAddress, serverP)); //connect
  // tell the tcp implementation to call WriteUntilBufferFull again
  // if we blocked and new tx buffer space becomes available
  loclSoc->SetSendCallback (MakeCallback (&WriteUntilBufFulOP));
  WriteUntilBufFulOP (loclSoc, loclSoc->GetTxAvailable ());
}

void WriteUntilBufFulOP (Ptr<Socket> loclSoc, uint32_t txSpace)
{
  while (currentTxBytes < totalTxBytesOP && loclSoc->GetTxAvailable () > 0)
    {
      uint32_t left = totalTxBytesOP - currentTxBytes;
      uint32_t dataOffset = currentTxBytes % writeSize;
      uint32_t toWrite = writeSize - dataOffset;
      toWrite = std::min (toWrite, left);
      toWrite = std::min (toWrite, loclSoc->GetTxAvailable ());
      int amountSent = loclSoc->Send (&data[dataOffset], toWrite, 0);
      if(amountSent < 0)
        {
          // we will be called again when new tx space becomes available.
          return;
        }
      currentTxBytes += amountSent;
    }
 // cout << "write complete at " << Simulator::Now ().GetSeconds ()<<endl;
  loclSoc->Close ();
}
