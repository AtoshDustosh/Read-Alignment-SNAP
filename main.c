#include <stdio.h>
#include <stdlib.h>

#include "FileOperation.h"
#include "HelperFunction.h"

/*
 * Files' paths.
 */
char* BWTFILEPATH = "bwtfiles/testdata_100.bwt";
char* FASTQFILEPATH = "fastqfiles/unitData.fastq";

/*
 * Global variables.
 */
/**
 * \note 4bit - 1char (0x1 - A, 0x2 - C, 0x3 - G, 0x4 - T, 0x5 - $).
 * Use length of array to decide whether a "0x0" is '$' or just an empty number.
 */
const int charNumPerHex = 8;   // #(character) per hexadecimal number

int hexArrayLength = 0;
int BWTARRAYLENGTH = 0; // length of BWT array

int* BWT = NULL;    // array of BWT - compressed using hexadecimal number


void testSet();


int main()
{
    testSet();

    BWTARRAYLENGTH = BWTFileSize(BWTFILEPATH, &hexArrayLength, charNumPerHex);

    BWT = (int*)malloc(sizeof(int) * BWTARRAYLENGTH);

    loadBWTFile(BWTFILEPATH, BWTARRAYLENGTH, hexArrayLength, charNumPerHex, BWT);


    free(BWT);
    return 0;
}






void testSet(){
    _charToHexTest();
//    _hexadecimalTest();
}
