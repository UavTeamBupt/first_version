//
// Generated file, do not edit! Created by nedtool 5.6 from inet/linklayer/common/InterfaceTag.msg.
//

#ifndef __INET_INTERFACETAG_M_H
#define __INET_INTERFACETAG_M_H

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

class InterfaceTagBase;
class InterfaceReq;
class InterfaceInd;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/TagBase_m.h" // import inet.common.TagBase


namespace inet {

/**
 * Class generated from <tt>inet/linklayer/common/InterfaceTag.msg:11</tt> by nedtool.
 * <pre>
 * class InterfaceTagBase extends TagBase
 * {
 *     int interfaceId = -1; // a locally unique (network node) identifier that determines the interface registered in the ~InterfaceTable  
 * }
 * </pre>
 */
class INET_API InterfaceTagBase : public ::inet::TagBase
{
  protected:
    int interfaceId = -1;

  private:
    void copy(const InterfaceTagBase& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const InterfaceTagBase&);

  public:
    InterfaceTagBase();
    InterfaceTagBase(const InterfaceTagBase& other);
    virtual ~InterfaceTagBase();
    InterfaceTagBase& operator=(const InterfaceTagBase& other);
    virtual InterfaceTagBase *dup() const override {return new InterfaceTagBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getInterfaceId() const;
    virtual void setInterfaceId(int interfaceId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const InterfaceTagBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, InterfaceTagBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/common/InterfaceTag.msg:19</tt> by nedtool.
 * <pre>
 * //
 * // Determines the outgoing interface where the packet should leave the network node.
 * //
 * class InterfaceReq extends InterfaceTagBase
 * {
 * }
 * </pre>
 */
class INET_API InterfaceReq : public ::inet::InterfaceTagBase
{
  protected:

  private:
    void copy(const InterfaceReq& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const InterfaceReq&);

  public:
    InterfaceReq();
    InterfaceReq(const InterfaceReq& other);
    virtual ~InterfaceReq();
    InterfaceReq& operator=(const InterfaceReq& other);
    virtual InterfaceReq *dup() const override {return new InterfaceReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const InterfaceReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, InterfaceReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/common/InterfaceTag.msg:26</tt> by nedtool.
 * <pre>
 * //
 * // Specifies the incoming interface where the packet has arrived at the network node.
 * //
 * class InterfaceInd extends InterfaceTagBase
 * {
 * }
 * </pre>
 */
class INET_API InterfaceInd : public ::inet::InterfaceTagBase
{
  protected:

  private:
    void copy(const InterfaceInd& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const InterfaceInd&);

  public:
    InterfaceInd();
    InterfaceInd(const InterfaceInd& other);
    virtual ~InterfaceInd();
    InterfaceInd& operator=(const InterfaceInd& other);
    virtual InterfaceInd *dup() const override {return new InterfaceInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const InterfaceInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, InterfaceInd& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_INTERFACETAG_M_H

