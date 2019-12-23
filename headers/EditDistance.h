#ifndef LANDAUVISHKIN_H_INCLUDED
#define LANDAUVISHKIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "AuxiliaryDataType.h"

/**
 * A collection of test in this header file.
 */
void _EditDistanceTestSet();

/*
 * Working functions.
 */

/**
 * Calculate edit distance between 2 strings.
 *
 * @param strBuf1 string buffer 1
 * @param strBuf2 string buffer 2
 * @param EDmax maximum edit distance that can be accepted
 * @param CIGARbuffer buffer for CIGAR string
 * @param maxBufLen maximum length of buffer for CIGAR string
 * @return return edit distance between str1 and str2 if distance is within EDmax;
 *      return EDmax if out of EDmax.
 */
uint64_t calculateEditDistance(StringBuffer* strBuf1, StringBuffer* strBuf2, uint64_t EDmax,
                               char* CIGARbuffer, uint64_t maxBufLen);

#endif // LANDAUVISHKIN_H_INCLUDED
