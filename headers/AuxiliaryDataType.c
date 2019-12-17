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
    initStringBuffer(strBuf1);
    initStringBuffer(strBuf2);

    strBuf1->buffer = "1234567";
    strBuf1->length = 7;
    strBuf2->buffer = "1234";
    strBuf2->length = 4;

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
    initHexCodedStringBuffer(hexCodedStrBuf1);
    initHexCodedStringBuffer(hexCodedStrBuf2);

    uint64_t arrayForTest1[] = {1, 2};
    uint64_t arrayLength1 = 2;
    uint64_t arrayForTest2[] = {0x0123456789abcdef};
    uint64_t arrayLength2 = 1;

    hexCodedStrBuf1->hexArray = arrayForTest1;
    hexCodedStrBuf1->arrayLength = arrayLength1;
    hexCodedStrBuf1->strLength = 34;

    hexCodedStrBuf2->hexArray = arrayForTest2;
    hexCodedStrBuf2->arrayLength = arrayLength2;
    hexCodedStrBuf2->strLength = 30;

    printHexCodedStringBuffer(hexCodedStrBuf1);
    printHexCodedStringBuffer(hexCodedStrBuf2);
}




/*
 * Working functions.
 */




void initStringBuffer(StringBuffer* strBuf) {
    strBuf->buffer = NULL;
    strBuf->length = 0;
}

void initHexCodedStringBuffer(HexCodedStringBuffer* hexCodedStrBuf) {
    hexCodedStrBuf->hexArray = NULL;
    hexCodedStrBuf->arrayLength = 0;
    hexCodedStrBuf->strLength = 0;
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


