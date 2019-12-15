#include "FileOperation.h"

#include "ArrayOperation.h"
#include "AuxiliaryFunction.h"
#include "MyArgs.h"


/**
 * Get the size of data (DNA sequence) of a ?.fna file.
 *
 * @param filePath file path
 * @return data size of ?.fna file
 */
uint64_t fnaDataSize(char* filePath) {
    printf("\nCalculating size of file %s ... \n", filePath);
    FILE* fp = fopen(filePath, "r");
    uint64_t dataZone = 0;   // if the file pointer is now in the data zone
    uint64_t dataLength = 0;

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
 * Load ?.fna data file into memory - stored in an uint64_t[] array.
 *
 * @param filePath file Path
 * @param dataLength length of ?.fna data
 * @param T uint64_t[] array used to store data
 */
void loadFnaData(char* filePath, uint64_t dataLength, uint64_t* T) {
    uint64_t i = 0;
    printf("\nLoading data from file %s ...\n", filePath);
    FILE* fp = fopen(filePath, "r");
    uint64_t dataZone = 0;   // if the file pointer is now in the data zone

    if(fp == NULL) {
        printf("failed to open file %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    char ch = fgetc(fp);
    char buffer[BUFSIZ];
    uint64_t contentSize = 0;
    uint64_t hexInt = 0;
    while(ch != EOF && i < dataLength) {
        if(ch == '\n' && !dataZone) {
            // according to format of *.fna file
            // data part is after the first line
            dataZone = 1;
        }
        if(dataZone && ch != '\n') {
            // if not '\n' and is already in the data zone
            buffer[contentSize++] = ch;
            if(contentSize == CHAR_NUM_PER_HEX) {
                buffer[contentSize] = '\0';
                hexInt = transBufToHex(buffer, contentSize, CHAR_NUM_PER_HEX);
                printf("0x%16"PRIx64"\t", hexInt);
                if((i + 1) % 4 == 0) {
                    printf("\n");
                }
                T[i++] = hexInt;
                contentSize = 0;
                clearCharArray(buffer, CHAR_NUM_PER_HEX);
            }
        }
        ch = fgetc(fp);
    }
    hexInt = transBufToHex(buffer, contentSize, CHAR_NUM_PER_HEX);
    printf("0x%16"PRIx64" ", hexInt);
    T[i++] = hexInt;

    free(fp);
}
