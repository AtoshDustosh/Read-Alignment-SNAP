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
    const uint64_t charNumPerHex = CHAR_NUM_PER_HEX;
    FILE* fp = fopen(filePath, "r");
    uint64_t dataZone = 0;   // if the file pointer is now in the data zone

    if(fp == NULL) {
        printf("failed to open file %s\n", filePath);
        exit(EXIT_FAILURE);
    }

    char ch = fgetc(fp);
    StringBuffer* strBuf = (StringBuffer*)malloc(sizeof(StringBuffer));
    HexCodedStringBuffer* hexCodedStrBuf =
        (HexCodedStringBuffer*)malloc(sizeof(HexCodedStringBuffer));
    uint64_t i = 0;

    strBuf->buffer = (char*)malloc(sizeof(char) * (charNumPerHex + 1));
    strBuf->length = 0;
    hexCodedStrBuf->hexArray = (uint64_t*)malloc(sizeof(uint64_t) * 1);
    hexCodedStrBuf->arrayLength = 1;
    hexCodedStrBuf->strLength = 0;

    uint64_t hexInt = 0;
    while(ch != EOF && i < dataLength) {
        if(ch == '\n' && !dataZone) {
            // according to format of *.fna file
            // data part is after the first line
            dataZone = 1;
        }
        if(dataZone && ch != '\n') {
            // if not '\n' and is already in the data zone
            strBuf->buffer[hexCodedStrBuf->strLength++] = ch;
            if(hexCodedStrBuf->strLength % charNumPerHex == 0) {
                strBuf->buffer[hexCodedStrBuf->strLength] = '\0';
                transStringBufferToHexCodedStringBuffer(strBuf, hexCodedStrBuf, charNumPerHex);
                hexInt = hexCodedStrBuf->hexArray[0];

                printf("0x%16"PRIx64"\t", hexInt);
                if((i + 1) % 4 == 0) {
                    printf("\n");
                }
                T[i++] = hexInt;
                initStringBuffer(strBuf);
                strBuf->buffer = (char*)malloc(sizeof(char) * (charNumPerHex + 1));
                strBuf->length = 0;
                initHexCodedStringBuffer(hexCodedStrBuf);
                hexCodedStrBuf->hexArray = (uint64_t*)malloc(sizeof(uint64_t) * 1);
                hexCodedStrBuf->arrayLength = 1;
                hexCodedStrBuf->strLength = 0;
            }
        }
        ch = fgetc(fp);
    }
    strBuf->buffer[hexCodedStrBuf->strLength] = '\0';
    transStringBufferToHexCodedStringBuffer(strBuf, hexCodedStrBuf, charNumPerHex);
    hexInt = hexCodedStrBuf->hexArray[0];
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
 * @param read a read
 */
static void loadOneRead_projectBufferToRead(char* buffer, uint64_t fastqLine, Read* read) {
//    printf("fastq line: %"PRIu64"\n", fastqLine);

    switch(fastqLine) {
    case 0:
        strcpy(read->QNAME, buffer);
        break;
    case 1:
        strcpy(read->SEQ, buffer);
        break;
    case 2:
        break;
    case 3:
        strcpy(read->QUAL, buffer);
        break;
    default:
        printf("Function loadOneRead_projectBufferToRead args error. \n");
        exit(EXIT_FAILURE);
    }
}























