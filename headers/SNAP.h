#ifndef SNAP_H_INCLUDED
#define SNAP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "HashTable.h"
#include "AuxiliaryDataType.h"

/**
 * A struct type for SNAP.
 */
typedef struct _define_SNAP {
    uint64_t* hexCodedRefDNA;   // hex-coded reference DNA
    uint64_t DNAlength;         // length of DNA
    uint64_t seedLength;      // length of a seed
    HashTable* hashTable;       // hash table constructed out of reference DNA
    Read* read;                 // a read to be aligned
} SNAP;


/**
 * A collection of test in this header file.
 */
void _SNAPTestSet();




/*
 * Working functions.
 */


/**
 * Construct the basic information of a SNAP structure.
 *
 * @param hexCodedRefDNA hex-coded reference DNA
 * @param DNAlength length of DNA
 * @param seedLength length of seed
 * @return a SNAP structure
 */
SNAP* constructSNAP(uint64_t* hexCodedRefDNA, uint64_t DNAlength, uint64_t seedLength);


/**
 * Extract a seed from reference DNA and put it into a hex-coded string buffer.
 *
 * @param hexCodedRefDNA hex-coded reference DNA
 * @param DNAlength length of DNA
 * @param seedLength length of seed (must be <= 32)
 * @param DNAoffset offset of the seed on ref
 * @return hex-coded string buffer of the seed
 */
HexCodedStringBuffer* extractHexCodedSeedFromRef(uint64_t* hexCodedDNA, uint64_t DNAlength,
                                        uint64_t seedLength, uint64_t DNAoffset);

#endif // SNAP_H_INCLUDED
