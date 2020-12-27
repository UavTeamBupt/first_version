//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/arp/ipv4/ArpPacket.msg.
//

#ifndef __INET_ARPPACKET_M_H
#define __INET_ARPPACKET_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class ArpPacket;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address


namespace inet {

/**
 * Enum generated from <tt>inet/networklayer/arp/ipv4/ArpPacket.msg:30</tt> by nedtool.
 * <pre>
 * //
 * // The list of practically important ARP opcodes
 * //
 * enum ArpOpcode
 * {
 *     ARP_REQUEST = 1;      // Request. RFC 826
 *     ARP_REPLY = 2;        // Reply. RFC 826, RFC 1868
 *     ARP_RARP_REQUEST = 3; // Request Reverse. RFC 903
 *     ARP_RARP_REPLY = 4;   // Reply Reverse. RFC 903
 * }
 * </pre>
 */
enum ArpOpcode {
    ARP_REQUEST = 1,
    ARP_REPLY = 2,
    ARP_RARP_REQUEST = 3,
    ARP_RARP_REPLY = 4
};

/**
 * Class generated from <tt>inet/networklayer/arp/ipv4/ArpPacket.msg:50</tt> by nedtool.
 * <pre>
 * //
 * // ARP packet. This is a specialized version: prepared for IEEE 802 hardware
 * // addresses and IPv4. Packet fields are therefore represented by C++ classes
 * // MACAddress and IPv4Address. Also, some ARP protocol header fields are
 * // not modelled explicitly (their values are implied):
 * //   - hardwareType (not needed for modelling);
 * //   - protocol type (0x800 IPv4)
 * //   - hardware address length (6)
 * //   - protocol address length (4)
 * //
 * class ArpPacket extends FieldsChunk
 * {
 *     // ARP header length for IPv4 (4-byte addresses) and 802 LANs (6-byte MAC addrs)
 *     chunkLength = B(28);
 *     ArpOpcode opcode;
 *     MacAddress srcMacAddress;
 *     MacAddress destMacAddress;
 *     Ipv4Address srcIpAddress;
 *     Ipv4Address destIpAddress;
 * }
 * </pre>
 */
class INET_API ArpPacket : public ::inet::FieldsChunk
{
  protected:
    inet::ArpOpcode opcode = static_cast<inet::ArpOpcode>(-1);
    MacAddress srcMacAddress;
    MacAddress destMacAddress;
    Ipv4Address srcIpAddress;
    Ipv4Address destIpAddress;

  private:
    void copy(const ArpPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ArpPacket&);

  public:
    ArpPacket();
    ArpPacket(const ArpPacket& other);
    virtual ~ArpPacket();
    ArpPacket& operator=(const ArpPacket& other);
    virtual ArpPacket *dup() const override {return new ArpPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::ArpOpcode getOpcode() const;
    virtual void setOpcode(inet::ArpOpcode opcode);
    virtual const MacAddress& getSrcMacAddress() const;
    virtual MacAddress& getSrcMacAddressForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<ArpPacket*>(this)->getSrcMacAddress());}
    virtual void setSrcMacAddress(const MacAddress& srcMacAddress);
    virtual const MacAddress& getDestMacAddress() const;
    virtual MacAddress& getDestMacAddressForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<ArpPacket*>(this)->getDestMacAddress());}
    virtual void setDestMacAddress(const MacAddress& destMacAddress);
    virtual const Ipv4Address& getSrcIpAddress() const;
    virtual Ipv4Address& getSrcIpAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<ArpPacket*>(this)->getSrcIpAddress());}
    virtual void setSrcIpAddress(const Ipv4Address& srcIpAddress);
    virtual const Ipv4Address& getDestIpAddress() const;
    virtual Ipv4Address& getDestIpAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<ArpPacket*>(this)->getDestIpAddress());}
    virtual void setDestIpAddress(const Ipv4Address& destIpAddress);

  public:
    virtual std::string str() const override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ArpPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ArpPacket& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_ARPPACKET_M_H

