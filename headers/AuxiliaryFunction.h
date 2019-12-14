#ifndef AUXILIARYFUNCTIONS_H_INCLUDED
#define AUXILIARYFUNCTIONS_H_INCLUDED


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
 * Transform characters stored in a buffer to an hexadecimal integer.
 *
 * @param buf buffer
 * @param bufSize size of buffer
 * @return hexadecimal integer corresponding to buffer
 */
int transBufToHexInt(char buf[], int bufSize);

/**
 * Get the lower case of a character.
 *
 * @param ch an English letter
 * @return lower case of ch if ch is in upper case; ch otherwise.
 */
char lowerCase(char ch);

/**
 * Transform hexadecimal numbers into characters (a, c, g, t, $)
 *
 * @param hexValue hexadecimal number
 * @return 'a' if 0x1; 'c' if 0x2;
 *         'g' if 0x4; 't' if 0x8;
 *         '*' otherwise.
 */
char hexToChar(int hex);

/**
 * Transform characters (A, C, G, T) into hexadecimal numbers.
 *
 * @param ch character
 * @return 0x1 if ch == 'A' || ch == 'a';
 *         0x2 if ch == 'C' || ch == 'c';
 *         0x4 if ch == 'G' || ch == 'g';
 *         0x8 if ch == 'T' || ch == 't';
 *         0x0 otherwise.
 */
int charToHex(char ch);





#endif // AUXILIARYFUNCTIONS_H_INCLUDED
