#include <stdlib.h>
#include <stdio.h>

#include "AuxiliaryFunction.h"

#define HEX_FOR_LETTER_A 0x1
#define HEX_FOR_LETTER_C 0x2
#define HEX_FOR_LETTER_G 0x4
#define HEX_FOR_LETTER_T 0x8


/**
 * A collection of test in this header file.
 */
void _AuxiliaryFunctionTestSet() {
    _charToHexTest();
    _hexToCharTest();
    _lowerCaseTest();
    _transBufToHexIntTest();
}

/*
 * Tests for working functions.
 */

/**
 * Test function charToHex.
 */
void _charToHexTest() {
    printf("\n**************** _charToHexTest ****************\n");
    char a = 'a';
    char A = 'A';
    char c = 'c';
    char C = 'C';
    char g = 'g';
    char G = 'G';
    char t = 't';
    char T = 'T';
    printf("%c, 0x%x | %c, 0x%x\n", a, charToHex(a), A, charToHex(A));
    printf("%c, 0x%x | %c, 0x%x\n", c, charToHex(c), C, charToHex(C));
    printf("%c, 0x%x | %c, 0x%x\n", g, charToHex(g), G, charToHex(G));
    printf("%c, 0x%x | %c, 0x%x\n", t, charToHex(t), T, charToHex(T));
    printf("%c, 0x%x\n", '$', charToHex('$'));
    printf("%c, 0x%x\n", '2', charToHex('2'));
}

/**
 * Test function hexToChar.
 */
void _hexToCharTest() {
    printf("\n**************** _hexToCharTest ****************\n");
    int hexA = 0x1;
    int hexC = 0x2;
    int hexG = 0x4;
    int hexT = 0x8;
    int hexWTF = 0xa;
    printf("0x%x -> %c\n", hexA, hexToChar(hexA));
    printf("0x%x -> %c\n", hexC, hexToChar(hexC));
    printf("0x%x -> %c\n", hexG, hexToChar(hexG));
    printf("0x%x -> %c\n", hexT, hexToChar(hexT));
    printf("0x%x -> %c\n", hexWTF, hexToChar(hexWTF));
}

/**
 * Test function lowerCase.
 */
void _lowerCaseTest() {
    printf("\n**************** _lowerCaseTest ****************\n");
    printf("lowerCase(%c) -> %c\n", 'A', lowerCase('A'));
    printf("lowerCase(%c) -> %c\n", 'a', lowerCase('a'));
    printf("lowerCase(%c) -> %c\n", '#', lowerCase('#'));
}

/**
 * Test function transBufToHexInt.
 */
void _transBufToHexIntTest() {
    printf("\n**************** _transBufToHexIntTest ****************\n");
    const bufSize = 8;
    char buf1[9] = {'a', 'a', 'c', 'g', 't', 'g', 't', 'c', '\0'};
    int hexInt = 0;

    hexInt = transBufToHexInt(buf1, bufSize);
    printf("buf1: %s\n", buf1);
    printf("hex_integer: 0x%x\n", hexInt);

    char buf2[9] = {'a', 'a', 'c', ' ', ' ', ' ', ' ', ' ', '\0'};
    hexInt = transBufToHexInt(buf2, bufSize);
    printf("buf2: %s\n", buf2);
    printf("hex_integer: 0x%x\n", hexInt);
}

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
int transBufToHexInt(char buf[], int bufSize) {
    int i = 0;
    int hexInt = 0x0;

    for(i = 0; i < bufSize; i++){
        int hexBit = charToHex(buf[i]);
        hexInt = hexInt | (hexBit << ((bufSize - i - 1) * 4));
//        printf("0x%x\n", hexInt);
    }
    return hexInt;
}

/**
 * Get the lower case of a character.
 *
 * @param ch an English letter
 * @return lower case of ch if ch is in upper case; ch otherwise.
 */
char lowerCase(char ch) {
    if(ch >= 'A' && ch <= 'Z') {
        return ch - ('A' - 'a');
    } else {
        return ch;
    }
}

/**
 * Transform hexadecimal numbers into characters (a, c, g, t, $)
 *
 * @param hexValue hexadecimal number
 * @return 'a' if 0x1; 'c' if 0x2;
 *         'g' if 0x4; 't' if 0x8;
 *         '*' otherwise.
 */
char hexToChar(int hex) {
    switch(hex) {
    case HEX_FOR_LETTER_A:
        return 'a';
    case HEX_FOR_LETTER_C:
        return 'c';
    case HEX_FOR_LETTER_G:
        return 'g';
    case HEX_FOR_LETTER_T:
        return 't';
    default:
        return '*';
    }
}

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
int charToHex(char ch) {
    ch = lowerCase(ch);
    switch(ch) {
    case 'a':
        return HEX_FOR_LETTER_A;
    case 'c':
        return HEX_FOR_LETTER_C;
    case 'g':
        return HEX_FOR_LETTER_G;
    case 't':
        return HEX_FOR_LETTER_T;
    default:
        return 0x0;
    }
}
