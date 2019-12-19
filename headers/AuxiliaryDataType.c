#include "AuxiliaryDataType.h"

#include <string.h>


static void _StringBufferTest();
static void _HexCodedStringBufferTest();

void _AuxiliaryDataTypeTestSet() {
    _StringBufferTest();
    _HexCodedStringBufferTest();
}



/**
 * Test the data type StringBuffer.
 */
static void _StringBufferTest() {
    printf("\n**************** _StringBufferTest ****************\n");
    StringBuffer* strBuf1 = (StringBuffer*)malloc(sizeof(StringBuffer));
    StringBuffer* strBuf2 = (StringBuffer*)malloc(sizeof(StringBuffer));

    char* str1 = "1234567";
    char* str2 = "1234";
    constructStringBuffer(strBuf1, str1, strlen(str1));
    constructStringBuffer(strBuf2, str2, strlen(str2));

    printStringBuffer(strBuf1);
    printStringBuffer(strBuf2);

    printf("... do string copy from string buffer 1 to string buffer 2\n");
//    strcpy(strBuf2->buffer, strBuf1->buffer); // this will result in an error
    strBuf2->buffer = strBuf1->buffer;

    printStringBuffer(strBuf1);
    printStringBuffer(strBuf2);
}

/**
 * Test the data type HexCodedStringBuffer.
 */
static void _HexCodedStringBufferTest() {
    printf("\n**************** _HexCodedStringBufferTest ****************\n");
    HexCodedStringBuffer* hexCodedStrBuf1 =
        (HexCodedStringBuffer*)malloc(sizeof(HexCodedStringBuffer));
    HexCodedStringBuffer* hexCodedStrBuf2 =
        (HexCodedStringBuffer*)malloc(sizeof(HexCodedStringBuffer));

    uint64_t arrayForTest1[] = {1, 2};
    uint64_t arrayLength1 = 2;
    uint64_t strLength1 = 34;
    uint64_t arrayForTest2[] = {0x0123456789abcdef};
    uint64_t arrayLength2 = 1;
    uint64_t strLength2 = 30;

    constructHexCodedStringBuffer(hexCodedStrBuf1, arrayForTest1, arrayLength1, strLength1);
    constructHexCodedStringBuffer(hexCodedStrBuf2, arrayForTest2, arrayLength2, strLength2);

    printHexCodedStringBuffer(hexCodedStrBuf1);
    printHexCodedStringBuffer(hexCodedStrBuf2);
}




/*
 * Working functions.
 */


void constructHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf, uint64_t* hexArray,
                                   uint64_t arrayLength, uint64_t strLength) {
    free(hexCodedStrBuf->hexArray);
    hexCodedStrBuf->hexArray = hexArray;
    hexCodedStrBuf->arrayLength = arrayLength;
    hexCodedStrBuf->strLength = strLength;
}

void constructStringBuffer(StringBuffer* strBuf, char* buffer, uint64_t length) {
    free(strBuf->buffer);
    strBuf->buffer = buffer;
    strBuf->length = length;
}

void initStringBuffer(StringBuffer* strBuf) {
    constructStringBuffer(strBuf, NULL, 0);
}

void initHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf) {
    constructHexCodedStringBuffer(hexCodedStrBuf, NULL, 1, 0);
}

void printStringBuffer(StringBuffer* strBuf) {
    printf("string buffer (0x%p) - (%s, %"PRIu64")\n",
           strBuf, strBuf->buffer, strBuf->length);
}

void printHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf) {
    uint64_t i = 0;
    printf("hex-coded string buffer (0x%p) - ({", hexCodedStrBuf);
    uint64_t arrayLength = hexCodedStrBuf->arrayLength;
    for(i = 0; i < arrayLength; i++) {
        printf("%#16"PRIx64"", hexCodedStrBuf->hexArray[i]);
        if(i != hexCodedStrBuf->arrayLength - 1) {
            printf(",");
        }
    }
    printf("}, %"PRIu64", %"PRIu64")\n",
           hexCodedStrBuf->arrayLength, hexCodedStrBuf->strLength);
}


void initializeRead(Read *read) {
//    read->QNAME = (char*)malloc(sizeof(char) * BUFSIZ);
    read->FLAG = 0x0;
//    read->RNAME = (char*)malloc(sizeof(char) * BUFSIZ);
    read->POS = 0;
    read->MAPQ = 0;
//    read->CIGAR = (char*)malloc(sizeof(char) * BUFSIZ);
//    read->RNEXT = (char*)malloc(sizeof(char) * BUFSIZ);
    read->PNEXT = 0;
    read->TLEN = 0;
//    read->SEQ = (char*)malloc(sizeof(char) * BUFSIZ);
//    read->QUAL = (char*)malloc(sizeof(char) * BUFSIZ);
}


