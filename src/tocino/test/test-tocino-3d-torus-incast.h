/* -*- Mode:C++; c-file-style:"microsoft"; indent-tabs-mode:nil; -*- */
#ifndef __TEST_TOCINO_3D_TORUS_INCAST_H__
#define __TEST_TOCINO_3D_TORUS_INCAST_H__

#include <stdint.h>
#include <vector>

#include "ns3/test.h"
#include "ns3/node-container.h"

#include "ns3/tocino-3d-torus-topology-helper.h"

#include "tocino-test-results.h"

namespace ns3
{

class TestTocino3DTorusIncast : public TestCase
{
    public:

    TestTocino3DTorusIncast( uint32_t radix, bool doWrap );

    private:
    
    const uint32_t RADIX;
    const uint32_t NODES;
   
    const bool m_doWrap;

    void CheckAllQuiet();

    int Middle() const;
    bool IsCenterNeighbor( const int x, const int y, const int z ) const;

    void TestHelper( const unsigned, const unsigned );

    virtual void DoRun();

    NodeContainer m_machines;

    // 3D vector of NetDevices
    Tocino3DTorusNetDeviceContainer m_netDevices;

    TocinoTestResults m_results;
};

}

#endif // __TEST_TOCINO_3D_TORUS_INCAST_H__
