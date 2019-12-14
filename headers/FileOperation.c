#include <stdio.h>
#include <stdlib.h>

#include "FileOperation.h"
#include "AuxiliaryFunction.h"

#define NUM_OF_CHAR_PER_HEX 8

/**
 * Get the size of data (DNA sequence) of a ?.fna file.
 *
 * @param filePath file path
 * @return data size of ?.fna file
 */
int fnaDataSize(char* filePath) {
    printf("Calculating size of file %s ... \n", filePath);
    FILE* fp = fopen(filePath, "r");
    int dataZone = 0;   // if the file pointer is now in the data zone
    int dataLength = 0;

    if(fp != NULL) {
        char ch = fgetc(fp);
        while(ch != EOF) {
            if(ch == '\n' && !dataZone) {
                // according to format of *.fna file
                // data part is after the first line
                dataZone = 1;
            }
            if(dataZone && ch != '\n') {
                // if not '\n' and is already in the data zone
                dataLength++;
            }
            ch = fgetc(fp);
        }
    } else {
        printf("failed to open file %s", filePath);
    }
    free(fp);
    return dataLength;
}

/**
 * Load ?.fna data file into memory - stored in an int[] array.
 *
 * @param filePath file Path
 * @param dataLength length of ?.fna data
 * @param T int[] array used to store data
 */
void loadFnaData(char* filePath, int dataLength, int* T) {
    int i = 0;
    printf("Loading data from file %s ...\n", filePath);
    FILE* fp = fopen(filePath, "r");
    int dataZone = 0;   // if the file pointer is now in the data zone

    if(fp == NULL) {
        printf("failed to open file %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    char ch = fgetc(fp);
    char buffer[NUM_OF_CHAR_PER_HEX];
    int bufferCount = 0;
    int hexInt = 0;
    while(ch != EOF && i < dataLength) {
        if(ch == '\n' && !dataZone) {
            // according to format of *.fna file
            // data part is after the first line
            dataZone = 1;
        }
        if(dataZone && ch != '\n') {
            // if not '\n' and is already in the data zone
            buffer[bufferCount++] = ch;
            if(bufferCount == NUM_OF_CHAR_PER_HEX) {
                hexInt = transBufToHexInt(buffer, NUM_OF_CHAR_PER_HEX);
                printf("0x%x ", hexInt);
                if((i + 1) % NUM_OF_CHAR_PER_HEX == 0){
                    printf("\n");
                }
                T[i++] = hexInt;
                bufferCount = 0;
                clearCharArray(buffer, NUM_OF_CHAR_PER_HEX);
            }
        }
        ch = fgetc(fp);
    }
    hexInt = transBufToHexInt(buffer, NUM_OF_CHAR_PER_HEX);
    printf("0x%x ", hexInt);
    T[i++] = hexInt;

    free(fp);
}
