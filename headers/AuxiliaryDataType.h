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
    char QNAME[BUFSIZ];
    int FLAG;
    char RNAME[BUFSIZ];
    int POS;
    float MAPQ;
    char CIGAR[BUFSIZ];
    char RNEXT[BUFSIZ];
    int PNEXT;
    int TLEN;
    char SEQ[BUFSIZ];
    char QUAL[BUFSIZ];
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
 * Initialize a string buffer with empty content.
 *
 * @param strBuf string buffer
 */
void initStringBuffer(StringBuffer* strBuf);

/**
 * Initialize a hex-coded string buffer with empty content.
 *
 * @param hexCodedStrBuf hex-coded string buffer
 */
void initHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf);

/**
 * Print a string buffer.
 *
 * @param strBuf string buffer
 */
void printStringBuffer(StringBuffer* strBuf);

/**
 * Print a hex-coded string buffer.
 *
 * @param hexCodedStrBuf hex-coded string buffer
 */
void printHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf);

/**
 * Initialize a struct Read.
 *
 * @param read pointer to a Read struct type
 */
void initializeRead(Read *read);

#endif // AUXILIARYDATATYPE_H_INCLUDED
