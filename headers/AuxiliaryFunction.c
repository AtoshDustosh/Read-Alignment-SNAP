#include "AuxiliaryFunction.h"

#include "MyArgs.h"

#define HEX_FOR_LETTER_A 0x0
#define HEX_FOR_LETTER_C 0x1
#define HEX_FOR_LETTER_G 0x2
#define HEX_FOR_LETTER_T 0x3


static void _charToHexTest();
static void _hexToCharTest();
static void _lowerCaseTest();
static void _transBufToHexIntTest();
static void _extractCharHexTest();
static void _transHexToBufTest();


/**
 * A collection of test in this header file.
 */
void _AuxiliaryFunctionTestSet() {
    _charToHexTest();
    _hexToCharTest();
    _lowerCaseTest();
    _transBufToHexIntTest();
    _extractCharHexTest();
    _transHexToBufTest();
}


/*
 * Tests for working functions.
 */

/**
 * Test function charToHex.
 */
static void _charToHexTest() {
    printf("\n**************** _charToHexTest ****************\n");
    char a = 'a';
    char A = 'A';
    char c = 'c';
    char C = 'C';
    char g = 'g';
    char G = 'G';
    char t = 't';
    char T = 'T';
    printf("%c, 0x%"PRIx64" | %c, 0x%"PRIx64"\n", a, charToHex(a), A, charToHex(A));
    printf("%c, 0x%"PRIx64" | %c, 0x%"PRIx64"\n", c, charToHex(c), C, charToHex(C));
    printf("%c, 0x%"PRIx64" | %c, 0x%"PRIx64"\n", g, charToHex(g), G, charToHex(G));
    printf("%c, 0x%"PRIx64" | %c, 0x%"PRIx64"\n", t, charToHex(t), T, charToHex(T));
    printf("%c, 0x%"PRIx64"\n", '$', charToHex('$'));
    printf("%c, 0x%"PRIx64"\n", '2', charToHex('2'));
}

/**
 * Test function hexToChar.
 */
static void _hexToCharTest() {
    printf("\n**************** _hexToCharTest ****************\n");
    uint64_t hexA = HEX_FOR_LETTER_A;
    uint64_t hexC = HEX_FOR_LETTER_C;
    uint64_t hexG = HEX_FOR_LETTER_G;
    uint64_t hexT = HEX_FOR_LETTER_T;
    uint64_t hexWTF = 0xa;
    printf("0x%"PRIx64" -> %c\n", hexA, hexToChar(hexA));
    printf("0x%"PRIx64" -> %c\n", hexC, hexToChar(hexC));
    printf("0x%"PRIx64" -> %c\n", hexG, hexToChar(hexG));
    printf("0x%"PRIx64" -> %c\n", hexT, hexToChar(hexT));
    printf("0x%"PRIx64" -> %c\n", hexWTF, hexToChar(hexWTF));
}

/**
 * Test function lowerCase.
 */
static void _lowerCaseTest() {
    printf("\n**************** _lowerCaseTest ****************\n");
    printf("lowerCase(%c) -> %c\n", 'A', lowerCase('A'));
    printf("lowerCase(%c) -> %c\n", 'a', lowerCase('a'));
    printf("lowerCase(%c) -> %c\n", '#', lowerCase('#'));
}

/**
 * Test function transBufToHexInt.
 */
static void _transBufToHexIntTest() {
    printf("\n**************** _transBufToHexIntTest ****************\n");
    const uint64_t charNumPerHex = CHAR_NUM_PER_HEX;
    uint64_t contentSize = CHAR_NUM_PER_HEX;
    char *buf = NULL;
    // 01010101 00100010 01110111 01010101 00000000 10101010 11111111 00000000
    // 0x5522775500AAFF00
    uint64_t hexInt = 0;

    contentSize = 32;
    buf = "ccccagagctctccccaaaaggggttttaaaa";
    // 01010101 00100010 01110111 01010101 00000000 10101010 11111111 00000000
    // 0x5522775500AAFF00
    hexInt = transBufToHex(buf, contentSize, charNumPerHex);
    printf("buf1: %s\n", buf);
    printf("hex_integer: 0x%16"PRIx64"\n", hexInt);

    contentSize = 16;
    buf = "ccccagagctctcccc";
    hexInt = transBufToHex(buf, contentSize, charNumPerHex);
    printf("buf2: %s\n", buf);
    printf("hex_integer: 0x%16"PRIx64"\n", hexInt);
}

/**
 * Test function extractCharHex.
 */
static void _extractCharHexTest() {
    printf("\n**************** _extractCharHexTest ****************\n");
    uint64_t hexInt = 0x27fd3de1e41a90ce;
    char* charSequence = "AGCTTTTCATTCTGACTGCAACGGGCAATATG";
    uint64_t i = 0;
    uint64_t length = CHAR_NUM_PER_HEX;

    printf("0x%16"PRIx64"\n", hexInt);
    printf("%s\n", charSequence);
    for(i = 0; i < length; i++) {
        int index = i % CHAR_NUM_PER_HEX;
        uint64_t extractedHex = extractCharHex(index, hexInt, CHAR_NUM_PER_HEX);
        printf("%c-0x%"PRIx64" ", charSequence[i], extractedHex);
        if((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
}

/**
 * Test function transHexToStr.
 */
static void _transHexToBufTest() {
    printf("\n**************** _transHexToBufTest ****************\n");
    uint64_t hexInt = 0x27fd3de1e41a90ce;
    char* buf = (char*)malloc(sizeof(char) * BUFSIZ);

    uint64_t beginIndex = 0;
    uint64_t endIndex = CHAR_NUM_PER_HEX - 1;

    printf("hexInt: 0x%"PRIx64"\n", hexInt);
    transHexToBuf(hexInt, beginIndex, endIndex, buf, CHAR_NUM_PER_HEX);
    printf("buf: %s\n", buf);
}

















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
                   char* buf, uint64_t charNumPerHex) {
    uint64_t i = 0;
    uint64_t length = endIndex - beginIndex + 1;

    for(i = 0; i < length; i++) {
        uint64_t charHex = extractCharHex(beginIndex + i, hexInt, charNumPerHex);
        buf[i] = hexToChar(charHex);
        printf("charHex: 0x%"PRIx64", char: %c\n", charHex, buf[i]);
    }
    buf[i] = '\0';
}


/**
 * Extract the hexadecimal number of a char compressed in a 64-bit hexInt.
 *
 * @param charIndex the sequence index of the char to be extracted
 *      (i.e. index is like 0, 1, 2, ... , maxLength - 1)
 * @param hexInt a 64-bit hexadecimal integer
 * @param charNumPerHex #(chars) per hexadecimal number
 * @return extracted hexadecimal number to the corresponding index
 */
uint64_t extractCharHex(uint64_t charIndex, uint64_t hexInt, uint64_t charNumPerHex) {
    uint64_t bitInterval = sizeof(uint64_t) * 8 / charNumPerHex;
    uint64_t bitShiftLeft = charIndex * bitInterval;
    uint64_t bitShiftRight = bitInterval * (charNumPerHex - 1);

    return (hexInt << bitShiftLeft) >> bitShiftRight;
}

/**
 * Transform characters stored in a char array buffer to an 64-bit unsigned
 * hexadecimal integer.
 *
 * @param buf char buffer
 * @param contentSize size of content
 * @param charNumPerHex #(chars) per hexadecimal number
 * @return 64-bit hexadecimal integer corresponding to buffer
 */
uint64_t transBufToHex(char* buf, uint64_t contentSize, uint64_t charNumPerHex) {
    uint64_t i = 0;
    uint64_t hexInt = 0x0;

    uint64_t bitInterval = sizeof(uint64_t) * 8 / charNumPerHex;
    for(i = 0; i < contentSize; i++) {
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
