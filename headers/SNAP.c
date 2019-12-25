#include "SNAP.h"


#include <string.h>


#include "MyArgs.h"
#include "AuxiliaryFunction.h"
#include "Queue.h"


#define INFINITE 9999999



static void constructSeedQueue(Read* read, Queue* seedQueue, uint64_t seedLength);








static void _extractHexCodedSeedFromDNATest();



void _SNAPTestSet() {
    _extractHexCodedSeedFromDNATest();
}



/*
 * Test functions.
 */

static void _extractHexCodedSeedFromDNATest() {
    printf("\n*************** _extractHexCodedSeedFromDNATest ***************\n");
    uint64_t hexCodedDNA[] = {0x27fd3de1e41a90ce, 0x27fd3de1e41a90ce};
    // agcttttcattctgactgcaacgggcaatatg
    //
    uint64_t DNAlength = 64;
    uint64_t seedLength = 20;
    uint64_t DNAoffset = 0;
    HexCodedStringBuffer* seedHexCodedStrBuf = NULL;
    StringBuffer* seedStrBuf = (StringBuffer*)malloc(sizeof(StringBuffer));

    seedLength = 20;
    DNAoffset = 3;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromDNA(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: ttttcattctgactgcaacg\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 20;
    DNAoffset = 20;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromDNA(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: acgggcaatatgagcttttc\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 32;
    DNAoffset = 16;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromDNA(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: tgcaacgggcaatatgagcttttcattctgac\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 32;
    DNAoffset = 0;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromDNA(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: agcttttcattctgactgcaacgggcaatatg\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    clearStringBuffer(seedStrBuf);
    clearHexCodedStringBuffer(seedHexCodedStrBuf);
}


/*
 * Working functions.
 */


SNAP* constructSNAP(uint64_t* hexCodedRefDNA, uint64_t DNAlength, uint64_t seedLength) {
    SNAP* snap = (SNAP*)malloc(sizeof(SNAP));

    snap->hexCodedRefDNA = hexCodedRefDNA;
    snap->hashTable = (HashTable*)malloc(sizeof(HashTable));
    snap->DNAlength = DNAlength;
    snap->seedLength = seedLength;
    snap->read = NULL;

    uint64_t tableSize = DNAlength - seedLength + 1;
    initHashTable(tableSize, snap->hashTable);

    /** < \note construct hash table */
    StringBuffer* seedStrBuf = (StringBuffer*)malloc(sizeof(StringBuffer));
    for(uint64_t offset = 0; offset < tableSize; offset++) {
        HexCodedStringBuffer* seedHexCodedStrBuf =
            extractHexCodedSeedFromDNA(hexCodedRefDNA, DNAlength, seedLength, offset);
//        printHexCodedStringBuffer(seedHexCodedStrBuf);
        transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
//        printStringBuffer(seedStrBuf);
        addHashCell(seedStrBuf->buffer, offset, snap->hashTable, tableSize);
    }

    printf("\n... hash table for reference DNA constructed. \n");
    checkHashTablePerformance(snap->hashTable, tableSize);

    return snap;
}

void loadOneReadIntoSNAP(Read* read, SNAP* snap) {
    if(snap == NULL || read == NULL) {
        printf("ERROR: null pointer occurs when loading a read into SNAP. \n");
        exit(EXIT_FAILURE);
    }
    snap->read = read;
}

HexCodedStringBuffer* extractHexCodedSeedFromDNA(uint64_t* hexCodedDNA, uint64_t DNAlength,
        uint64_t seedLength, uint64_t DNAoffset) {
    if(seedLength > CHAR_NUM_PER_HEX || seedLength <= 0) {
        printf("ERROR: length of a seed is too long or not valid - %"PRIu64"\n", seedLength);
        exit(EXIT_FAILURE);
    }
    if(seedLength + DNAoffset > DNAlength) {
        printf("ERROR: seed out of reference DNA - offset: %"PRIu64"\n", DNAoffset);
        exit(EXIT_FAILURE);
    }

    HexCodedStringBuffer* seedHexCodedStrBuf =
        (HexCodedStringBuffer*)malloc(sizeof(HexCodedStringBuffer));
    uint64_t* hexArray = (uint64_t*)malloc(sizeof(uint64_t));
    uint64_t arrayLength = 1;
    uint64_t strLength = seedLength;

    uint64_t hexInt = 0x0;  // the hex-coded seed string
    for(uint64_t i = 0; i < seedLength; i++) {
        uint64_t DNAhexIntIndex = (DNAoffset + i) / CHAR_NUM_PER_HEX;
        uint64_t DNAhexInt = *(hexCodedDNA + DNAhexIntIndex);
        uint64_t hexIntOffset = (i + (DNAoffset % CHAR_NUM_PER_HEX)) % CHAR_NUM_PER_HEX;
        uint64_t charHex = extractCharBitFromHexInt(hexIntOffset, DNAhexInt, CHAR_NUM_PER_HEX);
        uint64_t bitInterval = sizeof(uint64_t) * 8 / CHAR_NUM_PER_HEX;
//        printf("%"PRIu64"\t->\t%#"PRIx64"\t(%c)\t(%"PRIu64")%#"PRIx64"\n",
//                hexIntOffset, charHex, hexToChar(charHex), DNAhexIntIndex, DNAhexInt);
        charHex = charHex << ((CHAR_NUM_PER_HEX - 1 - i) * bitInterval);
        hexInt = hexInt | charHex;
//        printf("%#"PRIx64"\n", hexInt);
    }
//    printf("hexInt: %#"PRIx64"\n", hexInt);

    hexArray[0] = hexInt;
    constructHexCodedStringBuffer(seedHexCodedStrBuf, hexArray, arrayLength, strLength);
    return seedHexCodedStrBuf;
}


uint64_t alignReadUsingSNAP(SNAP* snap, uint64_t seedLength, uint64_t EDmax, uint64_t hitMax,
                            uint64_t confidenceThreshold) {
    uint64_t d_best = INFINITE;
    uint64_t d_second = INFINITE;
    Queue* seedQueue = (Queue*)malloc(sizeof(Queue));

    initQueue(seedQueue);
    constructSeedQueue(snap->read, seedQueue, seedLength);

    /**< \todo  */

    return 0;
}


/**
 * Construct a seed queue that will be aligned by a specific order.
 * First, align non-overlapping seeds. Second, align mid-seeds among the non-overlapping seeds.
 * Third, align mid-seeds among seeds that are aligned in the second step. Finally, align the
 * remained seeds.
 *
 * @param read a Read structure
 * @param / @return seedQueue a queue of seeds
 * @param seedLength length of a seed
 */
static void constructSeedQueue(Read* read, Queue* seedQueue, uint64_t seedLength) {
    uint64_t readLength = strlen(read->SEQ);
    uint64_t seedNum = readLength - seedLength + 1;
    HexCodedStringBuffer* seeds[seedNum];
    StringBuffer* readStrBuf = (StringBuffer*)malloc(sizeof(StringBuffer));
    HexCodedStringBuffer* readHexCodedStrBuf =
        (HexCodedStringBuffer*)malloc(sizeof(HexCodedStringBuffer));

    constructStringBuffer(readStrBuf, read->SEQ, readLength);
    transStringBufferToHexCodedStringBuffer(readStrBuf, readHexCodedStrBuf, CHAR_NUM_PER_HEX);

    printf("seed length: %"PRIu64", seedNum: %"PRIu64"\n", seedLength, seedNum);
    for(uint64_t i = 0; i < seedNum; i++) {
        HexCodedStringBuffer* seedHexCodedStrBuf =
            extractHexCodedSeedFromDNA(readHexCodedStrBuf->hexArray, readHexCodedStrBuf->strLength,
                                       seedLength, i);
        seeds[i] = seedHexCodedStrBuf;
    }

//    // print seeds
//    for(uint64_t i = 0; i < seedNum; i++){
//        HexCodedStringBuffer* seedHexCodedStrBuf = seeds[i];
//        StringBuffer* seedStrBuf = (StringBuffer*)malloc(sizeof(StringBuffer));
//        transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
//        printf("i:%"PRIu64"\t", i);
////        printStringBuffer(seedStrBuf);
//        printHexCodedStringBuffer(seedHexCodedStrBuf);
//        clearStringBuffer(seedStrBuf);
//    }
    for(uint64_t i = 0; i < seedNum; i++){
        if(i % seedLength == 0){
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]->hexArray[0]);
            enQueue(seedQueue, newQueueCell(seeds[i]->hexArray[0]));
        }
    }
    for(uint64_t i = 0; i < seedNum; i++){
        if(i % seedLength != 0 && i % (seedLength / 2) == 0){
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]->hexArray[0]);
            enQueue(seedQueue, newQueueCell(seeds[i]->hexArray[0]));
        }
    }
    for(uint64_t i = 0; i < seedNum; i++){
        if(i % seedLength != 0 && i % (seedLength / 2) != 0 && i % (seedLength / 3) == 0){
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]->hexArray[0]);
            enQueue(seedQueue, newQueueCell(seeds[i]->hexArray[0]));
        }
    }
    for(uint64_t i = 0; i < seedNum; i++){
        if(i % seedLength != 0 && i % (seedLength / 2) != 0 && i % (seedLength / 3) != 0){
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]->hexArray[0]);
            enQueue(seedQueue, newQueueCell(seeds[i]->hexArray[0]));
        }
    }
//    printQueue(seedQueue);
}











