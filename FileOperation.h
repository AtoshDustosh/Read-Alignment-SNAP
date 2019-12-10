#ifndef FILEOPERATION_H_INCLUDED
#define FILEOPERATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "HelperFunction.h"



int BWTFileSize(char* filePath, int* hexArrayLength, const int charNumPerHex);
void loadBWTFile(char* filePath, int bwtArrayLength, int hexArrayLength, const int charNumPerHex,
                 int* BWT);

/**
 * Load ?.bwt file and read data into an array BWT[] whose length is designated.
 *
 * \note this method is not responsible for requesting memory.
 * \note BWT is an integer array and uses hexadecimal to store chars.
 *
 * @param filePath file path
 * @param bwtArrayLength length of BWT array
 * @param hexArrayLength length of hex array (number of integers)
 * @param charNumPerHex #(char) per hexadecimal number
 * @param BWT[] array used for storing data
 */
void loadBWTFile(char* filePath, int bwtArrayLength, int hexArrayLength, const int charNumPerHex,
                 int* BWT) {
    printf("Loading data in %s... \n", filePath);

    int ifData = 0;   // if the file pointer is now in the data part

    int i = 0; // pointer to bwt data file
    int bwtArrayPointer = 0; // pointer to hexadecimal array

    int hexInteger = 0x00000000; // store hexNumbers transformed out of chars

    FILE* fp = fopen(filePath, "r");
    if(fp != NULL && i < bwtArrayLength) {
        char ch = fgetc(fp);
        while(ch != EOF) {
            if(ch == '\n' && !ifData) {
                // according to format of *.bwt file
                // data part is after the first line
                ifData = 1;
            }
            if(ifData && ch != '\n') {
                // if not '\n' and is already in the data part
                // store char into the array
                int temp = charToHex(ch) << (4 * (charNumPerHex - 1 - i % charNumPerHex));

                hexInteger = hexInteger | temp;
//                printf("%d,\t%c, 0x%8x, %d\n", i, ch, hexInteger, hexInteger);
                i++;

                // when reaches #(charNumPerHex), store hexInteger into BWT.
                if(i % charNumPerHex == 0) {
                    BWT[bwtArrayPointer++] = hexInteger;
                    hexInteger = 0x00000000;
                }
            }
            ch = fgetc(fp);
        }
        if(hexInteger != 0){
            BWT[bwtArrayPointer++] = hexInteger;
        }
    } else {
        printf("failed to open file %s", filePath);
        exit(-1);
    }

    printf("int* BWT[]: \n");
    for(i = 0; i < hexArrayLength; i++){
        printf("0x%8x, ", BWT[i]);
        if((i + 1) % 8 == 0){
            printf("\n");
        }
    }
    printf("\n");

    free(fp);
}

/**
 * Get the size of data of a ?.bwt file.
 *
 * @param filePath ?.bwt file path
 * @param hexArrayLength length of hex array (number of integers)
 * @param charNumPerHex #(char) per hexadecimal number
 * @return dataSize length of BWT array
 */
int BWTFileSize(char* filePath, int* hexArrayLength, const int charNumPerHex) {
    printf("Calculating size of the bwt data file ... \n");

    int ifData = 0;   // if the file pointer is now in the data part

    int dataSize = 0;   // length of data (number of chars)

    int charCount = 0;  // #(char) added to an 32-bit integer

    FILE* fp = fopen(filePath, "r");
    if(fp != NULL) {
        char ch = fgetc(fp);
        while(ch != EOF) {
            if(ch == '\n' && !ifData) {
                // according to format of *.bwt file
                // data part is after the first line
                ifData = 1;
            }
            if(ifData && ch != '\n') {
//                printf("%c", ch);
                // if not '\n' and is already in the data part
                charCount++;
                dataSize++;
                if(charCount == 8) {
//                    printf(" ");
                    charCount = 0;
                    *hexArrayLength = *hexArrayLength + 1;  // "++" operation won't work
                }
            }
            ch = fgetc(fp);
        }
//        printf("\n");
        // add the last part as a integer (incomplete)
        if(charCount != 0) {
            *hexArrayLength = *hexArrayLength + 1;
        }
    } else {
        printf("failed to open file %s", filePath);
    }

    printf("bwtArrayLength: %d\n", dataSize);
    printf("hexArrayLength: %d\n", *hexArrayLength);

    printf("\n");

    free(fp);

    return dataSize;
}


#endif // FILEOPERATION_H_INCLUDED
