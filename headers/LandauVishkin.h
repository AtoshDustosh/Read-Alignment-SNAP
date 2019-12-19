#ifndef LANDAUVISHKIN_H_INCLUDED
#define LANDAUVISHKIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "AuxiliaryDataType.h"

/**
 * A collection of test in this header file.
 */
void _LandauVishkinTestSet();

/*
 * Working functions.
 */

/**
 * Calculate edit distance between 2 strings.
 *
 * @param str1 string 1
 * @param str2 string 2
 * @param EDmax maximum edit distance that can be accepted
 * @return return edit distance between str1 and str2 if distance is within EDmax;
 *      return EDmax if out of EDmax.
 */
uint64_t calculateEditDistance(StringBuffer* str1, StringBuffer* str2, uint64_t EDmax);

#endif // LANDAUVISHKIN_H_INCLUDED
