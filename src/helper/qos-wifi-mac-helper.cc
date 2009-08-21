/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 MIRKO BANCHI
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as 
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */
#include "qos-wifi-mac-helper.h"
#include "ns3/msdu-aggregator.h"
#include "ns3/wifi-mac.h"
#include "ns3/edca-txop-n.h"
#include "ns3/pointer.h"
#include "ns3/uinteger.h"

namespace ns3 {

QosWifiMacHelper::QosWifiMacHelper ()
{
  ObjectFactory defaultAggregator;
  defaultAggregator.SetTypeId ("ns3::MsduStandardAggregator");
  m_aggregators.insert (std::make_pair (AC_VO, defaultAggregator));
  m_aggregators.insert (std::make_pair (AC_VI, defaultAggregator));
  m_aggregators.insert (std::make_pair (AC_BE, defaultAggregator));
  m_aggregators.insert (std::make_pair (AC_BK, defaultAggregator));
}

QosWifiMacHelper::~QosWifiMacHelper ()
{}

QosWifiMacHelper
QosWifiMacHelper::Default (void)
{
  QosWifiMacHelper helper;
  helper.SetType ("ns3::QstaWifiMac");
  
  return helper;
}

void
QosWifiMacHelper::SetType (std::string type,
                           std::string n0, const AttributeValue &v0,
                           std::string n1, const AttributeValue &v1,
                           std::string n2, const AttributeValue &v2,
                           std::string n3, const AttributeValue &v3,
                           std::string n4, const AttributeValue &v4,
                           std::string n5, const AttributeValue &v5,
                           std::string n6, const AttributeValue &v6,
                           std::string n7, const AttributeValue &v7)
{
  m_mac.SetTypeId (type);
  m_mac.Set (n0, v0);
  m_mac.Set (n1, v1);
  m_mac.Set (n2, v2);
  m_mac.Set (n3, v3);
  m_mac.Set (n4, v4);
  m_mac.Set (n5, v5);
  m_mac.Set (n6, v6);
  m_mac.Set (n7, v7);
}

void
QosWifiMacHelper::SetMsduAggregatorForAc (AccessClass accessClass, std::string type,
                                          std::string n0, const AttributeValue &v0,
                                          std::string n1, const AttributeValue &v1,
                                          std::string n2, const AttributeValue &v2,
                                          std::string n3, const AttributeValue &v3)
{
  std::map<AccessClass, ObjectFactory>::iterator it;
  it = m_aggregators.find (accessClass);
  if (it != m_aggregators.end ())
    {
      it->second.SetTypeId (type);
      it->second.Set (n0, v0);
      it->second.Set (n1, v1);
      it->second.Set (n2, v2);
      it->second.Set (n3, v3);
    }
}

void
QosWifiMacHelper::Setup (Ptr<WifiMac> mac, enum AccessClass ac, std::string dcaAttrName) const
{
  ObjectFactory factory  = m_aggregators.find (ac)->second;
  PointerValue ptr;
  mac->GetAttribute (dcaAttrName, ptr);
  Ptr<EdcaTxopN> edca = ptr.Get<EdcaTxopN> ();
  Ptr<MsduAggregator> aggregator = factory.Create<MsduAggregator> ();
  edca->SetMsduAggregator (aggregator);
}


Ptr<WifiMac>
QosWifiMacHelper::Create (void) const
{
  Ptr<WifiMac> mac = m_mac.Create<WifiMac> ();
  
  Setup (mac, AC_VO, "VO_EdcaTxopN");
  Setup (mac, AC_VI, "VI_EdcaTxopN");
  Setup (mac, AC_BE, "BE_EdcaTxopN");
  Setup (mac, AC_BK, "BK_EdcaTxopN");

  return mac;
}

} //namespace ns3
