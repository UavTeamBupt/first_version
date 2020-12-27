//
// Generated file, do not edit! Created by nedtool 5.6 from inet/linklayer/xmac/XMacHeader.msg.
//

#ifndef __INET_XMACHEADER_M_H
#define __INET_XMACHEADER_M_H

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

class XMacHeader;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/linklayer/base/MacHeaderBase_m.h" // import inet.linklayer.base.MacHeaderBase


namespace inet {

/**
 * Enum generated from <tt>inet/linklayer/xmac/XMacHeader.msg:24</tt> by nedtool.
 * <pre>
 * // \@brief Types of messages (self messages and packets) the node can process
 * enum XMacTypes
 * {
 *     // packet types
 *     XMAC_PREAMBLE = 191;
 *     XMAC_DATA = 192;
 *     XMAC_ACK = 193;
 *     // self message types
 *     XMAC_RESEND_DATA = 194;
 *     XMAC_ACK_TIMEOUT = 195;
 *     XMAC_START_XMAC = 196;
 *     XMAC_WAKE_UP = 197;
 *     XMAC_SEND_ACK = 198;
 *     XMAC_CCA_TIMEOUT = 199;
 *     XMAC_ACK_TX_OVER = 200;
 *     XMAC_SEND_PREAMBLE = 201;
 *     XMAC_STOP_PREAMBLES = 202;
 *     XMAC_DATA_TX_OVER = 203;
 *     XMAC_DATA_TIMEOUT = 204;
 *     SWITCH_PREAMBLE_PHASE = 205;
 *     DELAY_FOR_ACK_WITHIN_REMOTE_RX = 206;
 *     XMAC_SWITCHING_FINISHED = 207;
 * }
 * </pre>
 */
enum XMacTypes {
    XMAC_PREAMBLE = 191,
    XMAC_DATA = 192,
    XMAC_ACK = 193,
    XMAC_RESEND_DATA = 194,
    XMAC_ACK_TIMEOUT = 195,
    XMAC_START_XMAC = 196,
    XMAC_WAKE_UP = 197,
    XMAC_SEND_ACK = 198,
    XMAC_CCA_TIMEOUT = 199,
    XMAC_ACK_TX_OVER = 200,
    XMAC_SEND_PREAMBLE = 201,
    XMAC_STOP_PREAMBLES = 202,
    XMAC_DATA_TX_OVER = 203,
    XMAC_DATA_TIMEOUT = 204,
    SWITCH_PREAMBLE_PHASE = 205,
    DELAY_FOR_ACK_WITHIN_REMOTE_RX = 206,
    XMAC_SWITCHING_FINISHED = 207
};

/**
 * Class generated from <tt>inet/linklayer/xmac/XMacHeader.msg:51</tt> by nedtool.
 * <pre>
 * //
 * // Frame for ~XMac. Frame size is configurable
 * // in the MAC layer. 
 * //
 * class XMacHeader extends MacHeaderBase
 * {
 *     XMacTypes type;
 *     long sequenceId; // Sequence Number to detect duplicate messages
 * }
 * </pre>
 */
class INET_API XMacHeader : public ::inet::MacHeaderBase
{
  protected:
    inet::XMacTypes type = static_cast<inet::XMacTypes>(-1);
    long sequenceId = 0;

  private:
    void copy(const XMacHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const XMacHeader&);

  public:
    XMacHeader();
    XMacHeader(const XMacHeader& other);
    virtual ~XMacHeader();
    XMacHeader& operator=(const XMacHeader& other);
    virtual XMacHeader *dup() const override {return new XMacHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual inet::XMacTypes getType() const;
    virtual void setType(inet::XMacTypes type);
    virtual long getSequenceId() const;
    virtual void setSequenceId(long sequenceId);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const XMacHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, XMacHeader& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_XMACHEADER_M_H

