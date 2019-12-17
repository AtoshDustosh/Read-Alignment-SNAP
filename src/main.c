#include <stdio.h>
#include <stdlib.h>

#include "../headers/AuxiliaryDataType.h"
#include "../headers/AuxiliaryFunction.h"
#include "../headers/FileOperation.h"
#include "../headers/cDataType.h"
#include "../headers/ArrayOperation.h"
#include "../headers/HashTable.h"


/*
 * Global variables for ?.fna file.
 */
static char* fnaFilePath = "data/fna/testdata_100.fna";

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

static uint64_t dataLength = 0;
static uint64_t* T;


int main() {
    testSet();

    dataLength = fnaDataSize(fnaFilePath);
    T = (uint64_t*)malloc(sizeof(uint64_t) * dataLength);
    loadFnaData(fnaFilePath, dataLength, T);

    initialization();
    loadOneRead(fastqFilePath1, &fpointer1, &read1);
    loadOneRead(fastqFilePath1, &fpointer1, &read1);

    free(T);
    return 0;
}

void testSet() {
    _AuxiliaryDataTypeTestSet();
    _AuxiliaryFunctionTestSet();
    _ArrayOperationTestSet();
    _cDataTypeTestSet();
    _HashTableTestSet();
}

void initialization(){
    initializeRead(&read1);
//    initializeRead(&read2);
}
