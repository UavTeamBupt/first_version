//
// Generated file, do not edit! Created by nedtool 5.6 from inet/routing/dsdv/DsdvHello.msg.
//

#ifndef __INET_DSDVHELLO_M_H
#define __INET_DSDVHELLO_M_H

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

class DsdvHello;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address


namespace inet {

/**
 * Class generated from <tt>inet/routing/dsdv/DsdvHello.msg:23</tt> by nedtool.
 * <pre>
 * class DsdvHello extends FieldsChunk
 * {
 *     Ipv4Address srcAddress; //terminal que gerou o pacote
 *     unsigned int sequencenumber;//sequence number created by the source node(node's ID = srcIPAddress) of the hello msg and associated with that node
 *     Ipv4Address nextAddress; //terminal que re-/transmite o pacote
 *     int hopdistance; //distancia em hops/custo
 * }
 * </pre>
 */
class INET_API DsdvHello : public ::inet::FieldsChunk
{
  protected:
    Ipv4Address srcAddress;
    unsigned int sequencenumber = 0;
    Ipv4Address nextAddress;
    int hopdistance = 0;

  private:
    void copy(const DsdvHello& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const DsdvHello&);

  public:
    DsdvHello();
    DsdvHello(const DsdvHello& other);
    virtual ~DsdvHello();
    DsdvHello& operator=(const DsdvHello& other);
    virtual DsdvHello *dup() const override {return new DsdvHello(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Ipv4Address& getSrcAddress() const;
    virtual Ipv4Address& getSrcAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<DsdvHello*>(this)->getSrcAddress());}
    virtual void setSrcAddress(const Ipv4Address& srcAddress);
    virtual unsigned int getSequencenumber() const;
    virtual void setSequencenumber(unsigned int sequencenumber);
    virtual const Ipv4Address& getNextAddress() const;
    virtual Ipv4Address& getNextAddressForUpdate() { handleChange();return const_cast<Ipv4Address&>(const_cast<DsdvHello*>(this)->getNextAddress());}
    virtual void setNextAddress(const Ipv4Address& nextAddress);
    virtual int getHopdistance() const;
    virtual void setHopdistance(int hopdistance);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DsdvHello& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DsdvHello& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_DSDVHELLO_M_H

