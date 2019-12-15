#ifndef DATATYPE_H_INCLUDED
#define DATATYPE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct _define_Read{
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
}Read;


/**
 * A collection of test in this header file.
 */
void _DataTypeTestSet();

/*
 * Working functions.
 */

/**
 * Initialize a struct Read.
 *
 * @param read pointer to a Read struct type
 */
void initializeRead(Read *read);



#endif // DATATYPE_H_INCLUDED
