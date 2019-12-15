#ifndef AUXILIARYFUNCTIONS_H_INCLUDED
#define AUXILIARYFUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "MyArgs.h"

/**
 * A collection of test in this header file.
 */
void _AuxiliaryFunctionTestSet();



/*
 * Tests for working functions.
 */

/**
 * Test function charToHex.
 */
void _charToHexTest();

/**
 * Test function hexToChar.
 */
void _hexToCharTest();

/**
 * Test function lowerCase.
 */
void _lowerCaseTest();

/**
 * Test function transBufToHexInt.
 */
void _transBufToHexIntTest();



/*
 * Working functions.
 */

/**
 * Transform characters stored in a char array buffer to an 64-bit unsigned
 * hexadecimal integer.
 *
 * @param buf char buffer
 * @param contentSize size of content
 * @param charNumPerHex #(chars) per hexadecimal number
 * @return 64-bit hexadecimal integer corresponding to buffer
 */
uint64_t transBufToHex(char* buf, uint64_t contentSize, uint64_t charNumPerHex);

/**
 * Get the lower case of a character.
 *
 * @param ch an English letter
 * @return lower case of ch if ch is in upper case, i.e. 'A' -> 'a';
 *      ch otherwise, i.e. 'A' -> 'A', '*' -> '*'
 */
char lowerCase(char ch);

/**
 * Transform hexadecimal numbers into characters (a, c, g, t)
 *
 * @param hexValue hexadecimal number
 * @return 'a' if 0x0; 'c' if 0x1;
 *         'g' if 0x2; 't' if 0x3;
 *         '*' otherwise.
 */
char hexToChar(uint64_t hex);

/**
 * Transform characters (A, C, G, T) into hexadecimal numbers.
 *
 * @param ch character
 * @return 0x0 if ch == 'A' || ch == 'a';
 *         0x1 if ch == 'C' || ch == 'c';
 *         0x2 if ch == 'G' || ch == 'g';
 *         0x3 if ch == 'T' || ch == 't';
 *         0x0 otherwise.
 */
uint64_t charToHex(char ch);





#endif // AUXILIARYFUNCTIONS_H_INCLUDED
