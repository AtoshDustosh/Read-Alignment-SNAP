#include "FileOperation.h"

#include <string.h>

#include "ArrayOperation.h"
#include "AuxiliaryFunction.h"
#include "MyArgs.h"


static void loadOneRead_projectBufferToRead(char* buffer, uint64_t fastqLine, Read* read);


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

    printf("data size in file %s is %"PRIu64"\n", filePath, dataLength);
    return dataLength;
}

void loadFnaData(char* filePath, uint64_t dataLength, uint64_t* T) {
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
    uint64_t i = 0;
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
//                hexInt = transBufTo64BitHex(buffer, CHAR_NUM_PER_HEX);
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
//    hexInt = transBufTo64BitHex(buffer, CHAR_NUM_PER_HEX);
    printf("0x%16"PRIx64" ", hexInt);
    T[i++] = hexInt;

    free(fp);
}

void loadOneRead(char* filePath, FILE** fpointer, Read* readPointer) {
    printf("\n");
    if(*fpointer == NULL) {
        printf("Open file %s\n", filePath);
        *fpointer = fopen(filePath, "r");
    }

    if(*fpointer == NULL) {
        printf("failed to open file %s", filePath);
        exit(EXIT_FAILURE);
    }

    uint64_t bufPointer = 0;
    char buffer[BUFSIZ];
    clearCharArray(buffer, BUFSIZ);

    uint64_t fastqLine = 0;

    printf("Load a read form file %s ... \n", filePath);
    char ch = ' ';
    while(ch != EOF && fastqLine < 4) {
        ch = fgetc(*fpointer);
        if(ch == '\n') {
            buffer[bufPointer] = '\0';
            bufPointer = 0;
            loadOneRead_projectBufferToRead(buffer, fastqLine, readPointer);
            clearCharArray(buffer, BUFSIZ);
            fastqLine++;
            continue;
        }
        switch(fastqLine) {
        case 0: // header line
            buffer[bufPointer++] = ch;
            break;
        case 1: // sequence line
            buffer[bufPointer++] = ch;
            break;
        case 2: // supplementary line
            break;
        case 3: // quality line
            buffer[bufPointer++] = ch;
            break;
        default:
            return;
        }
    }
}




/*
 * Static functions. (file-localized functions)
 */

/**
 * Project the information in buffer to struct type Read.
 *
 * @param buffer buffer that stores information loaded from ?.fastq file
 * @param fastqLine line index of a read's information in ?.fastq file
 * @param readPointer pointer to a read of struct type
 */
static void loadOneRead_projectBufferToRead(char* buffer, uint64_t fastqLine, Read* readPointer) {
//    printf("fastq line: %"PRIu64"\n", fastqLine);

    switch(fastqLine) {
    case 0:
        strcpy(readPointer->QNAME, buffer);
        break;
    case 1:
        strcpy(readPointer->SEQ, buffer);
        break;
    case 2:
        break;
    case 3:
        strcpy(readPointer->QUAL, buffer);
        break;
    default:
        printf("Function loadOneRead_projectBufferToRead args error. \n");
        exit(EXIT_FAILURE);
    }
}























