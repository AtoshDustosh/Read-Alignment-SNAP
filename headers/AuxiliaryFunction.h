#ifndef AUXILIARYFUNCTIONS_H_INCLUDED
#define AUXILIARYFUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * A collection of test in this header file.
 */
void _AuxiliaryFunctionTestSet();

/*
 * Working functions.
 */

/**
 * Transform a 64-bit unsigned hexadecimal integer to a string.
 *
 * \note clear buffer before putting it int this method
 *
 * @param hexInt 64-bit hexadecimal integer
 * @param beginIndex beginning index of string in the hexInt
 * @param endIndex ending index of string in the hexInt
 * @param buf buffer of string transformed from the hexInt
 * @param charNumPerHex #(chars) per hexadecimal number
 */
void transHexToBuf(uint64_t hexInt, uint64_t beginIndex, uint64_t endIndex,
                   char* buf, uint64_t charNumPerHex);

/**
 * Extract the hexadecimal number of a char compressed in a 64-bit hexInt.
 *
 * @param charIndex the sequence index of the char to be extracted
 * @param hexInt a 64-bit hexadecimal integer
 * @param charNumPerHex #(chars) per hexadecimal number
 * @return extracted hexadecimal number to the corresponding index
 */
uint64_t extractCharHex(uint64_t charIndex, uint64_t hexInt, uint64_t charNumPerHex);

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
