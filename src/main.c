#include <stdio.h>
#include <stdlib.h>

#include "../headers/ArrayOperation.h"
#include "../headers/AuxiliaryDataType.h"
#include "../headers/AuxiliaryFunction.h"
#include "../headers/AVLTree.h"
#include "../headers/cDataType.h"
#include "../headers/EditDistance.h"
#include "../headers/FileOperation.h"
#include "../headers/HashTable.h"
#include "../headers/Queue.h"
#include "../headers/SNAP.h"



/*
 * Global variables for ?.fna file.
 */
static char* fnaFilePath = "data/fna/testdata_30.fna";

/*
 * Global variables for ?.fastq files.
 */
static char* fastqFilePath1 = "data/fastq/testdata_30_1.fastq";
static FILE* fpointer1 = NULL;
static Read read1;
//static char* fastqFilePath2 = "data/fastq/testdata_30_2.fastq";
//static FILE* fpointer2 = NULL;
//static Read read2;

void initialization();
void testSet();

static uint64_t DNAlength = 0;
static uint64_t* hexCodedRefDNA;

static SNAP* snap = NULL;
static uint64_t seedLength = 20;


int main() {
//    testSet();

    DNAlength = fnaDataSize(fnaFilePath);
    hexCodedRefDNA = (uint64_t*)malloc(sizeof(uint64_t) * DNAlength);
    loadFnaData(fnaFilePath, DNAlength, hexCodedRefDNA);

    snap = constructSNAP(hexCodedRefDNA, DNAlength, seedLength);
//    initialization();
//    loadOneRead(fastqFilePath1, &fpointer1, &read1);
//    loadOneRead(fastqFilePath1, &fpointer1, &read1);
//
    free(hexCodedRefDNA);
    free(snap);
    return 0;
}

void testSet() {
    _AuxiliaryDataTypeTestSet();
    _AuxiliaryFunctionTestSet();
    _AVLTreeTestSet();
    _ArrayOperationTestSet();
    _cDataTypeTestSet();
    _HashTableTestSet();
    _QueueTestSet();
    _EditDistanceTestSet();
    _SNAPTestSet();
}

void initialization() {
    initializeRead(&read1);
//    initializeRead(&read2);
}
