#ifndef AUXILIARYDATATYPE_H_INCLUDED
#define AUXILIARYDATATYPE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * A type used for storing the alignment results of a read.
 *
 */
typedef struct _define_Read {
    char QNAME[BUFSIZ]; // name of read
    int FLAG;           // bit-flags
    char RNAME[BUFSIZ]; // name of reference
    int POS;            // offset on ref
    float MAPQ;         // (pass)
    char CIGAR[BUFSIZ]; // CIGAR
    char RNEXT[BUFSIZ]; // name of reference of mate read alignment
    int PNEXT;          // offset on ref of mate read
    int TLEN;           // length of template
    char SEQ[BUFSIZ];   // sequence of read
    char QUAL[BUFSIZ];  // quality of read
} Read;

/**
 * A type used for storing a string.
 *
 * \note need to apply cpu memory for its buffer before usage
 */
typedef struct _define_StringBuffer {
    char* buffer;    // buffer used to store a string
    uint64_t length; // length of the string stored in this StringBuffer
} StringBuffer;

/**
 * A type used for storing a hexadecimal-coded string.
 *
 * \note a string is coded into one or multiple 64-bit unsigned hexadecimals and stored
 * in this HexadecimalStringBuffer. This type will store all hexadecimals, length of the
 * hex-array, and length of the string.
 *
 * \note need to apply cpu memory for its buffer before usage
 */
typedef struct _define_HexCodedStringBuffer {
    uint64_t* hexArray; // an array of 64-bit hexadecimal numbers
    uint64_t arrayLength;   // length of the hexArray
    uint64_t strLength; // length of the string i.e. #(characters or letters)
} HexCodedStringBuffer;







/**
 * A collection of test in this header file.
 */
void _AuxiliaryDataTypeTestSet();



/*
 * Working functions.
 */

/**
 * Construct a hex-coded string buffer with input (hexArray, arrayLength, strLength) by copying
 * hexArray.
 *
 * @param hexCodedStrBuf hex-coded string buffer to be constructed - cannot be NULL pointer
 * @param hexArray hex-coded array
 * @param arrayLength length of array
 * @param strLength length of string
 */
void constructHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf, uint64_t* hexArray,
                                   uint64_t arrayLength, uint64_t strLength);

/**
 * Construct a string buffer with input (buffer, length) by copying buffer.
 *
 * @param strBuf string buffer to be constructed - cannot be NULL pointer
 * @param buffer string
 * @param length string length
 */
void constructStringBuffer(StringBuffer* strBuf, char* buffer, uint64_t length);

/**
 * Initialize a string buffer with empty content.
 *
 * @param strBuf string buffer - cannot be NULL pointer
 */
void initStringBuffer(StringBuffer* strBuf);

/**
 * Initialize a hex-coded string buffer with empty content.
 *
 * @param hexCodedStrBuf hex-coded string buffer - cannot be NULL pointer
 */
void initHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf);

/**
 * Print a string buffer.
 *
 * @param strBuf string buffer - cannot be NULL pointer
 */
void printStringBuffer(StringBuffer* strBuf);

/**
 * Print a hex-coded string buffer.
 *
 * @param hexCodedStrBuf hex-coded string buffer - cannot be NULL pointer
 */
void printHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf);

/**
 * Initialize a struct Read.
 *
 * @param read pointer to a Read struct type - cannot be NULL pointer
 */
void initializeRead(Read *read);

#endif // AUXILIARYDATATYPE_H_INCLUDED
