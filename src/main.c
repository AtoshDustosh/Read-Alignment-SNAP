#include <stdio.h>
#include <stdlib.h>

#include <string.h>

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
static char* fnaFileHeader = NULL;

/*
 * Global variables for ?.fastq files.
 */
/** < \note remained to be optimized (structural problems) */
static char* fastqFilePath = "data/fastq/testdata_30_1.fastq";
static FILE* fpointer = NULL;
static Read* read = NULL;


static uint64_t DNAlength = 0;
static uint64_t* hexCodedRefDNA = NULL;

static SNAP* snap = NULL;
static uint64_t seedLength = 20;
static uint64_t EDmax = 7;
static uint64_t hitMax = 200;
static uint64_t confidenceThreshold = 3;



void testSet();



int main() {
//    testSet();

    DNAlength = fnaDataSize(fnaFilePath);
    fnaFileHeader = (char*)malloc(sizeof(char) * BUFSIZ);
    hexCodedRefDNA = (uint64_t*)malloc(sizeof(uint64_t) * DNAlength);
    loadFnaData(fnaFilePath, DNAlength, hexCodedRefDNA, fnaFileHeader);
    printf("\nreference DNA name: %s\n", fnaFileHeader);

    snap = constructSNAP(hexCodedRefDNA, DNAlength, seedLength);

    read = (Read*)malloc(sizeof(Read));
    initRead(read);
    loadOneReadFromFile(fastqFilePath, &fpointer, read);
    printRead(read);

    loadOneReadIntoSNAP(read, snap);
    strcpy(read->RNAME, fnaFileHeader);
    printf("align one read with seedLength:%"PRIu64", EDmax:%"PRIu64", hitMax:%"PRIu64", "
           "confidence threshold:%"PRIu64"\n", seedLength, EDmax, hitMax, confidenceThreshold);
    uint16_t result = alignOneReadUsingSNAP(snap, seedLength, EDmax, hitMax, confidenceThreshold);

    printf("align result: ");
    if(result == SINGLE_HIT){
        printf("single hit.\n");
    } else if (result == MULTIPLE_HITS){
        printf("multiple hit.\n");
    } else{
        printf("not found\n");
    }

    printRead(read);
//    loadOneReadFromFile(fastqFilePath, &fpointer, read);
//    printRead(read);





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

