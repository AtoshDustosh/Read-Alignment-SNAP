#ifndef FILEOPERATION_H_INCLUDED
#define FILEOPERATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "HelperFunction.h"


/**
 * Planning to make the program read while processing instead of read all data
 * at the beginning, as that may cost a lot memory.
 * Maybe I will need to use a file pointer and transfer it between functions.
 */

int BWTFileSize(char* filePath, int* hexArrayLength, const int charNumPerHex);
void loadBWTFile(char* filePath, int bwtArrayLength, int* hexArrayLength, const int charNumPerHex,
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
void loadBWTFile(char* filePath, int bwtArrayLength, int* hexArrayLength, const int charNumPerHex,
                 int* BWT) {
////    printf("Loading data in %s... \n", filePath);
////    FILE* fp = fopen(filePath, "r");
////    int ifData = 0;
////    int bwtDataPointer = 0;
////
////    if(fp != NULL && bwtDataPointer < bwtArrayLength) {
////        char ch = fgetc(fp);
////        while(ch != EOF) {
////            if(ch == '\n' && !ifData) {
////                // according to format of *.bwt file
////                // data part is after the first line
////                ifData = 1;
////            }
////            if(ifData && ch != '\n') {
////                // if not '\n' and is already in the data part
////                // store char into the array
////                BWT[bwtDataPointer++] = lowerCase(ch);
////            }
////            ch = fgetc(fp);
////        }
////    } else {
////        printf("failed to open file %s", filePath);
////        exit(-1);
////    }
////    free(fp);
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
    } else {
        printf("failed to open file %s", filePath);
    }
//    printf("\n");

    // add the last part as a integer (incomplete)
    if(charCount != 0) {
        *hexArrayLength = *hexArrayLength + 1;
    }

    free(fp);
    return dataSize;
}


#endif // FILEOPERATION_H_INCLUDED
