#include <stdio.h>
#include <stdlib.h>

#include "FileOperation.h"
#include "HelperFunction.h"

/*
 * Files' paths.
 */
char* BWTFILEPATH = "bwtfiles/testdata_1.bwt";
char* FASTQFILEPATH = "fastqfiles/unitData.fastq";
char* FNAFILEPATH = "fnafiles/testdata_1.fna";

/*
 * Global variables.
 */
/**
 * \note 2bit - 1char (0x1 - A, 0x2 - C, 0x3 - G, 0x4 - T, 0x0 - $).
 * Use length of array to decide whether a "0x0" is '$' or just an empty number.
 */
const int charNumPerHex = 16;   // #(character) per hexadecimal number

int hexArrayLength = 0;
int BWTARRAYLENGTH = 0; // length of BWT array

int* BWT = NULL;    // array of BWT - compressed using hexadecimal number


void testSet();


int main()
{
    testSet();

    BWTARRAYLENGTH = BWTFileSize(BWTFILEPATH, &hexArrayLength, charNumPerHex);
    printf("bwtArrayLength: %d\n", BWTARRAYLENGTH);
    printf("hexArrayLength: %d\n", hexArrayLength);

    return 0;
}






void testSet(){
    _char2HexTest();
//    _hexadecimalTest();
}
