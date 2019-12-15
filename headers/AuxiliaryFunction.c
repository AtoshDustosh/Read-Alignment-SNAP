#include "AuxiliaryFunction.h"

#define HEX_FOR_LETTER_A 0x0
#define HEX_FOR_LETTER_C 0x1
#define HEX_FOR_LETTER_G 0x2
#define HEX_FOR_LETTER_T 0x3


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
    int hexA = HEX_FOR_LETTER_A;
    int hexC = HEX_FOR_LETTER_C;
    int hexG = HEX_FOR_LETTER_G;
    int hexT = HEX_FOR_LETTER_T;
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
    const uint64_t charNumPerHex = CHAR_NUM_PER_HEX;
    uint64_t bufSize = CHAR_NUM_PER_HEX;
    char *buf = NULL;
    // 01010101 00100010 01110111 01010101 00000000 10101010 11111111 00000000
    // 0x5522775500AAFF00
    uint64_t hexInt = 0;

    bufSize = 32;
    buf = "ccccagagctctccccaaaaggggttttaaaa";
    // 01010101 00100010 01110111 01010101 00000000 10101010 11111111 00000000
    // 0x5522775500AAFF00
    hexInt = transBufToHex(buf, bufSize, charNumPerHex);
    printf("buf1: %s\n", buf);
    printf("hex_integer: %#"PRIx64"\n", hexInt);

    bufSize = 16;
    buf = "ccccagagctctcccc";
    hexInt = transBufToHex(buf, bufSize, charNumPerHex);
    printf("buf2: %s\n", buf);
    printf("hex_integer: %#"PRIx64"\n", hexInt);
}

/*
 * Working functions.
 */

/**
 * Transform characters stored in a buffer to an 64-bit unsigned hexadecimal
 * integer.
 *
 * @param buf char buffer
 * @param bufSize size of buffer
 * @param charNumPerHex #(chars) per hexadecimal number
 * @return 64-bit hexadecimal integer corresponding to buffer
 */
uint64_t transBufToHex(char* buf, uint64_t bufSize, uint64_t charNumPerHex) {
    uint64_t i = 0;
    uint64_t hexInt = 0x0;

    uint64_t bitInterval = sizeof(uint64_t) * 8 / charNumPerHex;
    for(i = 0; i < bufSize; i++) {
        uint64_t hexBit = charToHex(buf[i]);
        uint64_t bitShift = charNumPerHex - i - 1;
        hexInt = hexInt | (hexBit << (bitShift * bitInterval));
//        printf("%c, %#"PRIx64"\n", buf[i], hexInt);
    }
    return hexInt;
}

/**
 * Get the lower case of a character.
 *
 * @param ch an English letter
 * @return lower case of ch if ch is in upper case, i.e. 'A' -> 'a';
 *      ch otherwise, i.e. 'A' -> 'A', '*' -> '*'
 */
char lowerCase(char ch) {
    if(ch >= 'A' && ch <= 'Z') {
        return ch - ('A' - 'a');
    } else {
        return ch;
    }
}

/**
 * Transform hexadecimal numbers into characters (a, c, g, t)
 *
 * @param hexValue hexadecimal number
 * @return 'a' if 0x0; 'c' if 0x1;
 *         'g' if 0x2; 't' if 0x3;
 *         '*' otherwise.
 */
char hexToChar(uint64_t hex) {
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
 * @return 0x0 if ch == 'A' || ch == 'a';
 *         0x1 if ch == 'C' || ch == 'c';
 *         0x2 if ch == 'G' || ch == 'g';
 *         0x3 if ch == 'T' || ch == 't';
 *         0x0 otherwise.
 */
uint64_t charToHex(char ch) {
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
