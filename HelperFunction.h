#ifndef HELPERFUNCTION_H_INCLUDED
#define HELPERFUNCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Test funcs.
 */
void _myStrLengthTest();
void _lowerCaseTest();
void _hexadecimalTest();
void _charToHexTest();

/*
 * Important funcs.
 */
int charToHex(char ch);
int myStrLength(char str[]);
char lowerCase(char ch);



/**
 * Test my-string-length function.
 */
void _myStrLengthTest() {
    printf("\n**************** _myStrLengthTest ****************\n");
    char str[] = {'1', '2', '3', '\0'};
    char *ch = &str[0];
    int strlength = 0;
    int i = 0;
    for(i = 0; i < 3; i++) {
        printf("%c ", str[i]);
    }
    printf("\n");

    while(*ch != '\0') {
        printf("%c ", *ch);
        strlength++;
        ch = ch + 1;
    }

    printf("\n");
}

/**
 * Test lowerCase function.
 */
void _lowerCaseTest() {
    printf("\n**************** _lowerCaseTest ****************\n");
    printf("%c\t%c\t%c\n", lowerCase('A'), lowerCase('a'), lowerCase('D'));
    printf("\n");
}

/**
 * Test hexadecimal alignment to speed up the character alignment.
 */
void _hexadecimalTest() {
    printf("\n**************** _hexadecimalTest ****************\n");
    int a = 0x00000123;
    int b = 0x00004123;

    // print the 8-char integer (32bit - 4bit ~ 1 char)
    printf("a = 0x%x, %d\n", a, a);
    printf("b = 0x%x, %d\n", b, b);

    // print the alignment result of a & b and a & a
    printf("a & a = 0x%x. %d\n", a & a, (a & a) == a && (a & a) == a);
    printf("a & b = 0x%x. %d\n", a & b, (a & b) == a && (a & b) == b);

    printf("\n");
}

/**
 * Test char-to-hex function.
 */
void _charToHexTest() {
    printf("\n**************** _char2HexTest ****************\n");
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

    printf("\n");
}

/**
 * Transform characters (A, C, G, T, $) into hexadecimal numbers.
 *
 * @param ch character
 * @return 0x1 if ch == 'A' || ch == 'a';
 *         0x2 if ch == 'C' || ch == 'c';
 *         0x3 if ch == 'G' || ch == 'g';
 *         0x4 if ch == 'T' || ch == 't';
 *         0x5 if ch == '$'; -1 otherwise.
 */
int charToHex(char ch) {
    switch(ch) {
    case 'A':
    case 'a':
        return 0x1;
    case 'C':
    case 'c':
        return 0x2;
    case 'G':
    case 'g':
        return 0x3;
    case 'T':
    case 't':
        return 0x4;
    case '$':
        return 0x5;
    default:
        return -1;
    }
}

/**
 * Get the length of a string. (including the character '\0')
 *
 * @param str input string
 */
int myStrLength(char str[]) {
    char *ch = &str[0];
    int strlength = 0;

    while(*ch != '\0') {
        strlength++;
        ch = ch + 1;
    }

    return strlength;
}

/**
 * Get the lower case of a letter.
 *
 * @param ch a letter
 * @return lower case of ch; ch if it's not a letter or it is already lower case
 */
char lowerCase(char ch) {
    if(ch >= 'A' && ch <= 'Z') {
        return ch - ('A' - 'a');
    } else {
        return ch;
    }
}



#endif // HELPERFUNCTION_H_INCLUDED
