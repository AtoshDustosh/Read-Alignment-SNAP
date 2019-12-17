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
    uint64_t s_mer_length;  // length of an s-mer
    HashTable* hashTable;   // hash table constructed out of reference DNA
    Read* read; // a read to be aligned
} SNAP;



#endif // SNAP_H_INCLUDED
