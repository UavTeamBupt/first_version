//
// Generated file, do not edit! Created by nedtool 5.6 from inet/common/ByteArray.msg.
//

#ifndef __INET_BYTEARRAY_M_H
#define __INET_BYTEARRAY_M_H

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

class ByteArray;
} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs


namespace inet {

/**
 * Class generated from <tt>inet/common/ByteArray.msg:25</tt> by nedtool.
 * <pre>
 * //
 * // Class that carries raw bytes.
 * // For example, used by ~RawPacket and some TCP queues.
 * //
 * class ByteArray extends cObject
 * {
 *     char data[];
 * }
 * </pre>
 */
class INET_API ByteArray : public ::omnetpp::cObject
{
  protected:
    char *data = nullptr;
    size_t data_arraysize = 0;

  private:
    void copy(const ByteArray& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ByteArray&);

  public:
    ByteArray();
    ByteArray(const ByteArray& other);
    virtual ~ByteArray();
    ByteArray& operator=(const ByteArray& other);
    virtual ByteArray *dup() const override {return new ByteArray(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual void setDataArraySize(size_t size);
    virtual size_t getDataArraySize() const;
    virtual char getData(size_t k) const;
    virtual void setData(size_t k, char data);
    virtual void insertData(char data);
    virtual void insertData(size_t k, char data);
    virtual void eraseData(size_t k);

  public:
    /**
     * Copy data from buffer
     * @param ptr: pointer to buffer
     * @param length: length of data
     */
    virtual void setDataFromBuffer(const void *ptr, unsigned int length);

    /**
     * Copy data from buffer
     * @param destOffset: first byte from buffer will be written to here
     * @param ptr: pointer to buffer
     * @param length: length of data
     */
    virtual void copyDataFromBuffer(unsigned int destOffset, const void *ptr, unsigned int length);

    /**
     * Copy data from other ByteArray
     * @param other: reference to other ByteArray
     * @param srcOffset: skipped first bytes from other
     * @param length: length of data
     */
    virtual void setDataFromByteArray(const ByteArray& other, unsigned int srcOffset, unsigned int length);

    /**
     * Copy data from other ByteArray
     * @param destOffset: first byte from other will be written to here
     * @param other: reference to other ByteArray
     * @param srcOffset: skipped first bytes from other
     * @param length: length of data from other
     */
    virtual void copyDataFromByteArray(unsigned int destOffset, const ByteArray& other, unsigned int srcOffset, unsigned int length);

    /**
     * Add data from buffer to the end of existing content
     * @param ptr: pointer to input buffer
     * @param length: length of data
     */
    virtual void addDataFromBuffer(const void *ptr, unsigned int length);

    /**
     * Copy data content to buffer
     * @param ptr: pointer to output buffer
     * @param length: length of buffer, maximum of copied bytes
     * @param srcOffs: number of skipped bytes from source
     * @return: length of copied data
     */
    virtual unsigned int copyDataToBuffer(void *ptr, unsigned int length, unsigned int srcOffs = 0) const;

    /**
     * Set buffer pointer and buffer length
     * @param ptr: pointer to new buffer, must created by `buffer = new char[length1];` where length1>=length
     * @param length: length of buffer
     */
    virtual void assignBuffer(void *ptr, unsigned int length);

    /**
     * Truncate data content
     * @param truncleft: The number of bytes from the beginning of the content be remove
     * @param truncright: The number of bytes from the end of the content be remove
     * Generate assert when not have enough bytes for truncation
     */
    virtual void truncateData(unsigned int truncleft, unsigned int truncright);

    /**
     * Expand data content
     * @param addLeft: The number of bytes will be added at beginning of the content
     * @param addRight: The number of bytes will be added at end of the content
     * added bytes are unfilled
     */
    virtual void expandData(unsigned int addLeft, unsigned int addRight);

    virtual const char *getDataPtr() const { return data; }
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ByteArray& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ByteArray& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_BYTEARRAY_M_H

