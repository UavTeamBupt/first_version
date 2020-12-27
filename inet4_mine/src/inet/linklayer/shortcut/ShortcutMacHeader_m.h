//
// Generated file, do not edit! Created by nedtool 5.6 from inet/linklayer/shortcut/ShortcutMacHeader.msg.
//

#ifndef __INET_SHORTCUTMACHEADER_M_H
#define __INET_SHORTCUTMACHEADER_M_H

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

class ShortcutMacHeader;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Protocol_m.h" // import inet.common.Protocol

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/linklayer/shortcut/ShortcutMacHeader.msg:25</tt> by nedtool.
 * <pre>
 * class ShortcutMacHeader extends FieldsChunk
 * {
 *     const Protocol *payloadProtocol = nullptr;
 * }
 * </pre>
 */
class INET_API ShortcutMacHeader : public ::inet::FieldsChunk
{
  protected:
    const Protocol * payloadProtocol = nullptr;

  private:
    void copy(const ShortcutMacHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ShortcutMacHeader&);

  public:
    ShortcutMacHeader();
    ShortcutMacHeader(const ShortcutMacHeader& other);
    virtual ~ShortcutMacHeader();
    ShortcutMacHeader& operator=(const ShortcutMacHeader& other);
    virtual ShortcutMacHeader *dup() const override {return new ShortcutMacHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const Protocol * getPayloadProtocol() const;
    virtual void setPayloadProtocol(const Protocol * payloadProtocol);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ShortcutMacHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ShortcutMacHeader& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_SHORTCUTMACHEADER_M_H

