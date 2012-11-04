/* -*- Mode:C++; c-file-style:"microsoft"; indent-tabs-mode:nil; -*- */
#ifndef __TOCINO_RX_H__
#define __TOCINO_RX_H__

#include <stdint.h>
#include <vector>

#include "ns3/ptr.h"

#include "tocino-flow-control.h"

namespace ns3
{

class NetDevice;
class TocinoNetDevice;
class Packet;
class CallbackQueue;

class TocinoRx
{
public:
    TocinoRx( Ptr<TocinoNetDevice> );
    ~TocinoRx();
    
    Ptr<NetDevice> GetNetDevice();
    
//    void Receive(Ptr<const Packet> p);
    void Receive(Ptr<Packet> p);
   
    friend class TocinoNetDevice;
    friend class TocinoTx;
private:
    
    uint32_t m_portNumber;
    TocinoFlowControl::State m_xstate; // tracks xstate of TocinoTx on other end of channel

    const Ptr<TocinoNetDevice> m_tnd; // link to owning TocinoNetDevice
    
    std::vector< Ptr <CallbackQueue> > m_queues; // packet queues to write
    
    bool IsBlocked();
    void CheckForUnblock(); // called from TocinNetDeviceTransmitter
    void SetXState(TocinoFlowControl::State s) {m_xstate = s;}
    TocinoFlowControl::State GetXState() {return m_xstate;}
};

} // namespace ns3

#endif // __TOCINO_RX_H__
