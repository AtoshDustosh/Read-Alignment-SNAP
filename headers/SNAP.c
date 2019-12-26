#include "SNAP.h"


#include <string.h>


#include "MyArgs.h"
#include "AuxiliaryFunction.h"
#include "AVLTree.h"
#include "EditDistance.h"
#include "Queue.h"


#define INFINITE 9999999



static Queue* constructSeedQueue(Read* read, uint64_t seedLength);
static Queue* getLocationQueueOfSeed(HexCodedStringBuffer* seedHexCodedStrBuf, SNAP* snap);
static AVLNode* accumulateLocationsUsingAVLTree(AVLNode* tree, Queue* locationQueue,
        uint64_t seedOffset);
static uint64_t getEDofBestAlignment( SNAP* snap, uint64_t* mostHittingLocations,
                                      uint64_t mostHittingLocationsNum, uint64_t d_limit,
                                      uint64_t* bestAlignmentLocation);
static void updateBestAndSecondBest(uint64_t* d_best, uint64_t* d_bestRefOffset,
                                    uint64_t* d_second, uint64_t* d_secondRefOffset,
                                    uint64_t d_new, uint64_t d_newRefOffset);





static void _extractHexCodedFragmentFromRefTest();



void _SNAPTestSet() {
    _extractHexCodedFragmentFromRefTest();
}



/*
 * Test functions.
 */

static void _extractHexCodedFragmentFromRefTest() {
    printf("\n*************** _extractHexCodedFragmentFromRefTest ***************\n");
    uint64_t hexCodedDNA[] = {0x27fd3de1e41a90ce, 0x27fd3de1e41a90ce};
    // agcttttcattctgactgcaacgggcaatatg
    //

    uint64_t refArrayLength = 2;
    uint64_t DNAlength = 64;
    uint64_t seedLength = 0;
    uint64_t DNAoffset = 0;
    HexCodedStringBuffer* refHexCodedStrBuf =
        constructHexCodedStringBuffer(hexCodedDNA, refArrayLength, DNAlength);
    StringBuffer* refStrBuf =
        transHexCodedStringBufferToStringBuffer(refHexCodedStrBuf, CHAR_NUM_PER_HEX);
    HexCodedStringBuffer* seedHexCodedStrBuf = NULL;
    StringBuffer* seedStrBuf = NULL;

    printf("Reference sequence: \n");
    printHexCodedStringBuffer(refHexCodedStrBuf);
    printStringBuffer(refStrBuf);

    seedLength = 20;
    DNAoffset = 3;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedFragmentFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: ttttcattctgactgcaacg\n");
    seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);
    clearStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 20;
    DNAoffset = 20;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedFragmentFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: acgggcaatatgagcttttc\n");
    seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);
    clearStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 32;
    DNAoffset = 16;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedFragmentFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: tgcaacgggcaatatgagcttttcattctgac\n");
    seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);
    clearStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 32;
    DNAoffset = 0;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedFragmentFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: agcttttcattctgactgcaacgggcaatatg\n");
    seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);
    clearStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 48;
    DNAoffset = 16;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedFragmentFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: tgcaacgggcaatatgagcttttcattctgactgcaacgggcaatatg\n");
    seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);
    clearStringBuffer(seedStrBuf);


    clearHexCodedStringBuffer(seedHexCodedStrBuf);
    clearStringBuffer(refStrBuf);
    clearHexCodedStringBuffer(refHexCodedStrBuf);
}


/*
 * Working functions.
 */


SNAP* constructSNAP(uint64_t* hexCodedRefDNA, uint64_t DNAlength, uint64_t seedLength) {
    uint64_t tableSize = DNAlength - seedLength + 1;
    SNAP* snap = (SNAP*)malloc(sizeof(SNAP));

    snap->hexCodedRefDNA = hexCodedRefDNA;
    snap->hashTable = initHashTable(tableSize);
    snap->DNAlength = DNAlength;
    snap->seedLength = seedLength;
    snap->read = NULL;

    /** < \note construct hash table */
    StringBuffer* seedStrBuf = NULL;
    for(uint64_t refOffset = 0; refOffset < tableSize; refOffset++) {
        HexCodedStringBuffer* seedHexCodedStrBuf =
            extractHexCodedFragmentFromRef(hexCodedRefDNA, DNAlength, seedLength, refOffset);
//        printHexCodedStringBuffer(seedHexCodedStrBuf);
        seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
//        printStringBuffer(seedStrBuf);
        addHashCell(seedStrBuf->buffer, refOffset, snap->hashTable, tableSize);
        clearStringBuffer(seedStrBuf);
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

HexCodedStringBuffer* extractHexCodedFragmentFromRef(uint64_t* refSeq, uint64_t refLength,
        uint64_t fragmentLength, uint64_t refOffset) {
    if(fragmentLength + refOffset > refLength) {
        printf("ERROR: fragment out of reference sequence - ref offset: %"PRIu64", fragment "
               "length: %"PRIu64"\n", refOffset, fragmentLength);
        exit(EXIT_FAILURE);
    }

    uint64_t fragmentArrayLength = 0;
    if(fragmentLength % CHAR_NUM_PER_HEX == 0) {
        fragmentArrayLength = fragmentLength / CHAR_NUM_PER_HEX;
    } else {
        fragmentArrayLength = fragmentLength / CHAR_NUM_PER_HEX + 1;
    }
    uint64_t* hexArray = (uint64_t*)malloc(sizeof(uint64_t) * fragmentLength);

    uint64_t bitInterval = sizeof(uint64_t) * 8 / CHAR_NUM_PER_HEX;
    uint64_t fragmentHexIntIndex = 0;
    uint64_t fragmentCharHexIndex = 0;

    uint64_t fragmentHexInt = 0x0;
    for(uint64_t i = 0; i < fragmentLength; i++) {
        uint64_t refHexIntIndex = (refOffset + i) / CHAR_NUM_PER_HEX;
        uint64_t refHexInt = *(refSeq + refHexIntIndex);
        uint64_t refHexIntOffset = (i + (refOffset % CHAR_NUM_PER_HEX)) % CHAR_NUM_PER_HEX;
        uint64_t charHex = extractCharBitFromHexInt(refHexIntOffset, refHexInt, CHAR_NUM_PER_HEX);
//        char tempChar = hexToChar(charHex);
        charHex = charHex << ((CHAR_NUM_PER_HEX - 1 - i) * bitInterval);
        fragmentHexInt = fragmentHexInt | charHex;
        fragmentCharHexIndex++;
//        printf("%"PRIu64"\t(%c) -> %#"PRIx64"\n", i, tempChar, fragmentHexInt);
        if(fragmentCharHexIndex == CHAR_NUM_PER_HEX || i == fragmentLength - 1) {
            hexArray[fragmentHexIntIndex++] = fragmentHexInt;
            fragmentCharHexIndex = 0;
            fragmentHexInt = 0x0;
        }
    }
    return constructHexCodedStringBuffer(hexArray, fragmentArrayLength, fragmentLength);
}


uint64_t alignReadUsingSNAP(SNAP* snap, uint64_t seedLength, uint64_t EDmax,
                            uint64_t hitMax, uint64_t confidenceThreshold) {
    const uint64_t d_max = EDmax;
    uint64_t d_best = INFINITE;
    uint64_t d_bestRefOffset = 0;
    uint64_t d_second = INFINITE;
    uint64_t d_secondRefOffset = 0;
    uint64_t d_limit = EDmax;

    char* readSeq = snap->read->SEQ;
    uint64_t readLength = (uint64_t)strlen(readSeq);
    StringBuffer* readStrBuf = constructStringBuffer(readSeq, readLength);
    HexCodedStringBuffer* readHexCodedStrBuf =
        transStringBufferToHexCodedStringBuffer(readStrBuf, CHAR_NUM_PER_HEX);

    /** < \note construct a seed queue for processing seeds in a specific order.
        Queue cells contain offsets of seeds on the read */
    Queue* seedQueue = constructSeedQueue(snap->read, seedLength);

//    printQueue(seedQueue);
    /**< \todo  */
    AVLNode* locationAVLTree = NULL;
    uint64_t seedSeqNum = 0;
    /** < \note process seeds one by one */
    QueueCell* seedQueueCell = newQueueCell(0);
    while(isQueueEmpty(seedQueue) != QUEUE_EMPTY) {
        deQueue(seedQueue, seedQueueCell);

        uint64_t seedOffset = seedQueueCell->data;
        HexCodedStringBuffer* seedHexCodedStrBuf = extractHexCodedFragmentFromRef(
                    readHexCodedStrBuf->hexArray, readLength, seedLength, seedOffset);

        StringBuffer* seedStrBuf = transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf,
                                   CHAR_NUM_PER_HEX);
        printf("%"PRIu64"\t-> seed seq: ", seedSeqNum);
        printStringBuffer(seedStrBuf);

        /** < \note find locations exactly matched with the seed on hash table of ref DNA.
            Queue cells contain offsets of locations on the ref DNA, and this set of locations
            correspond to one seed of the read */
        Queue* locationQueue = getLocationQueueOfSeed(seedHexCodedStrBuf, snap);
//        printQueue(locationQueue);

        /** < \note accumulate locations using AVL data structure for later procedure */
        locationAVLTree = accumulateLocationsUsingAVLTree(locationAVLTree, locationQueue,
                          seedOffset);

        /** < \note find locations that have the most seeds matched there (maybe more than 1) */
        uint64_t mostHittingLocationsNum = 0;
        AVLNode** mostHittingLocationsAVLNodes = findNodeswithMaxData(locationAVLTree,
                &mostHittingLocationsNum);
        uint64_t* mostHittingLocations =
            (uint64_t*)malloc(sizeof(uint64_t) * mostHittingLocationsNum);
        printf("Most hitting locations: \n");
        for(uint64_t i = 0; i < mostHittingLocationsNum; i++) {
            mostHittingLocations[i] = mostHittingLocationsAVLNodes[i]->key;
            uint64_t hitCount = mostHittingLocationsAVLNodes[i]->data;
            printf("location: %"PRIu64", hitCount: %"PRIu64"\n", mostHittingLocations[i], hitCount);
        }

        /** < \note update d_limit to speed up subsequent alignment */
        if(d_best > d_max) {
            d_limit = d_max + confidenceThreshold - 1;
        } else if (d_second >= d_best + confidenceThreshold) {
            d_limit = d_best + confidenceThreshold - 1;
        } else {
            d_limit = d_best - 1;
        }

        /** < \note compute the best edit-distances of these locations */
        uint64_t d_newRefOffset = 0;
//        printf("... calculate edit-distance of best alignment with d_limit:%"PRIu64"\n", d_limit);
        uint64_t d_new = getEDofBestAlignment(snap, mostHittingLocations, mostHittingLocationsNum,
                                              d_limit, &d_newRefOffset);
        printf("d_best: %"PRIu64", best alignment location: %"PRIu64"\n", d_new, d_newRefOffset);

        /** < \note update d_best and d_second according to d_new */
        updateBestAndSecondBest(&d_best, &d_bestRefOffset, &d_second, &d_secondRefOffset,
                                d_new, d_newRefOffset);




        seedSeqNum++;
        clearQueue(locationQueue);
        free(mostHittingLocations);
        free(mostHittingLocationsAVLNodes);
        printf("\n");
    }
    updateBestAndSecondBest(&d_best, &d_bestRefOffset, &d_second, &d_secondRefOffset,
                            36, 25626);

//    printf("\nAVL tree of locations: \n");
//    traversePrintAVLTree(locationAVLTree);


    clearQueue(seedQueue);
    clearAVLTree(locationAVLTree);
    return 0;
}


/**
 * Construct a seed queue that will be aligned by a specific order.
 * First, align non-overlapping seeds. Second, align mid-seeds among the non-overlapping seeds.
 * Third, align mid-seeds among seeds that are aligned in the second step. Finally, align the
 * remained seeds.
 *
 * @param read a Read structure
 * @param seedLength length of a seed
 * @return a queue of seeds containing queue cells whose data represents offset of seeds on the read
 */
static Queue* constructSeedQueue(Read* read, uint64_t seedLength) {
    uint64_t readLength = strlen(read->SEQ);
    uint64_t seedNum = readLength - seedLength + 1;
    uint64_t seeds[seedNum];

    printf("seed length: %"PRIu64", seedNum: %"PRIu64"\n", seedLength, seedNum);
    for(uint64_t i = 0; i < seedNum; i++) {
        seeds[i] = i;
    }

    Queue* seedQueue = initQueue();
    for(uint64_t i = 0; i < seedNum; i++) {
        if(i % seedLength == 0) {
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]);
            enQueue(seedQueue, newQueueCell(seeds[i]));
        }
    }
    for(uint64_t i = 0; i < seedNum; i++) {
        if(i % seedLength != 0 && i % (seedLength / 2) == 0) {
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]);
            enQueue(seedQueue, newQueueCell(seeds[i]));
        }
    }
    for(uint64_t i = 0; i < seedNum; i++) {
        if(i % seedLength != 0 && i % (seedLength / 2) != 0 && i % (seedLength / 3) == 0) {
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]);
            enQueue(seedQueue, newQueueCell(seeds[i]));
        }
    }
    for(uint64_t i = 0; i < seedNum; i++) {
        if(i % seedLength != 0 && i % (seedLength / 2) != 0 && i % (seedLength / 3) != 0) {
//            printf("i: %"PRIu64"\t-> %#"PRIx64"\n", i, seeds[i]);
            enQueue(seedQueue, newQueueCell(seeds[i]));
        }
    }
    printf("... seed queue constructed. \n");
    return seedQueue;
}


/**
 * Get a queue for locations corresponding to hits on ref DNA of a seed.
 *
 * @param seedHexCodedStrBuf a seed stored with hex-coded string buffer
 * @param snap an SNAP structure containing a hash table of all s-mers of ref DNA
 * @return a queue for locations corresponding to hits on ref DNA of the seed
 */
static Queue* getLocationQueueOfSeed(HexCodedStringBuffer* seedHexCodedStrBuf, SNAP* snap) {
    Queue* locationQueue = initQueue();

    StringBuffer* seedStrBuf =
        transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, CHAR_NUM_PER_HEX);
    uint64_t seedLength = seedStrBuf->length;

    HashCell* hashCell =
        searchHashIndexOfString(seedStrBuf->buffer, snap->hashTable, snap->hashTable->tableSize);

    while(hashCell != NULL) {
        uint64_t refOffset = hashCell->data;
        HexCodedStringBuffer* refSmerHexCodedStrBuf = extractHexCodedFragmentFromRef(
                    snap->hexCodedRefDNA, snap->DNAlength, seedLength, refOffset);
//        StringBuffer* refSmerStrBuf = transHexCodedStringBufferToStringBuffer(refSmerHexCodedStrBuf,
//                                      CHAR_NUM_PER_HEX);

        uint64_t compareResult = compareHexCodedStringBuffer(refSmerHexCodedStrBuf,
                                 seedHexCodedStrBuf);
//        printf("\t");
//        printf("compare result: %"PRIu64"\t", compareResult);
//        printStringBuffer(refSmerStrBuf);

        if(compareResult == HEX_CODED_STRINGBUFFER_SAME) {
            enQueue(locationQueue, newQueueCell(refOffset));
        }
        hashCell = hashCell->nextCell;
    }

    return locationQueue;
}

/**
 * Accumulate locations of hitting that belong to a seed using an AVL tree.
 *
 * @param tree an AVL tree
 * @param Queue a queue of locations of seed-hitting
 * @param seedOffset offset of the seed on read
 * @return new root node of the AVL tree
 */
static AVLNode* accumulateLocationsUsingAVLTree(AVLNode* tree, Queue* locationQueue,
        uint64_t seedOffset) {
    AVLNode* node = NULL;
    QueueCell* queueCell = (QueueCell*)malloc(sizeof(QueueCell));

    while(isQueueEmpty(locationQueue) != QUEUE_EMPTY) {
        deQueue(locationQueue, queueCell);
        uint64_t hitOffset = queueCell->data;
        uint64_t locationOffset = hitOffset - seedOffset;
        node = findAVLNode(tree, locationOffset);
        if(node == NULL) {
//            printf("... add new AVL node (%"PRIu64", 1)\n", locationOffset, 1);
            AVLNode* newRoot = insertAVLNode(tree, createAVLNode(locationOffset, 1, NULL, NULL));
            tree = newRoot;
        } else {
//            printf("... accumulate AVL node (%"PRIu64", %"PRIu64")\n",
//                   locationOffset, node->data);
            node->data = node->data + 1;
        }
    }

    free(queueCell);
    return tree;
}

/**
 * Get the edit-distance of the best alignment of an array of locations with the most hitting.
 * The edit-distance is within a specific limit.
 *
 * @param snap an SNAP structure
 * @param mostHittingLocations locations with the most hitting
 * @param mostHittingLocationsNum number of locations
 * @param d_limit limit of edit distance, which means EDmax for the calculation process of ED.
 * @param / @return bestAlignmentLocation location of the best alignment
 * @return edit-distance of the best alignment
 */
static uint64_t getEDofBestAlignment(SNAP* snap, uint64_t* mostHittingLocations,
                                     uint64_t mostHittingLocationsNum, uint64_t d_limit,
                                     uint64_t* bestAlignmentLocation) {
    const uint64_t* refHexCodedDNA = snap->hexCodedRefDNA;
    const uint64_t refLength = snap->DNAlength;
    char* readSeq = snap->read->SEQ;
    const uint64_t readLength = (uint64_t)strlen(readSeq);
    StringBuffer* readStrBuf = constructStringBuffer(readSeq, readLength);


    uint64_t bestED = INFINITE;

    for(uint64_t locationSeqNum = 0; locationSeqNum < mostHittingLocationsNum; locationSeqNum++) {
        uint64_t location = mostHittingLocations[locationSeqNum];
        uint64_t refSegmentLength = readLength + d_limit;
        for(uint64_t i = 0; i < d_limit; i++) {
            char CIGARbuffer[BUFSIZ];
            uint64_t refSegmentOffset = location - i;
            if(refSegmentOffset < 0) {
                break;
            }
            printf("ref length:%"PRIu64", refSegmentLength:%"PRIu64", refSegmentOffset:%"PRIu64"\n",
                   refLength, refSegmentLength, refSegmentOffset);
            HexCodedStringBuffer* refSegmentHexCodedStrBuf = extractHexCodedFragmentFromRef(
                        refHexCodedDNA, refLength, refSegmentLength, refSegmentOffset);
            StringBuffer* refSegmentStrBuf = transHexCodedStringBufferToStringBuffer(
                                                 refSegmentHexCodedStrBuf, CHAR_NUM_PER_HEX);
//            printf("### ");
//            printStringBuffer(refSegmentStrBuf);
            uint64_t EDvalue = calculateEditDistance(readStrBuf, refSegmentStrBuf, d_limit,
                               CIGARbuffer, BUFSIZ);
//            printf("edit distance: %"PRIu64"\n", EDvalue);
//            printf("CIGAR: %s\n", CIGARbuffer);
            if(EDvalue < bestED) {
                bestED = EDvalue;
                *bestAlignmentLocation = refSegmentOffset;
            }
        }
    }

//    clearStringBuffer(readStrBuf);
    return bestED;
}

/**
 * Update d_best and d_second according to d_new (one step of the SNAP procedure).
 *
 * @param / @return d_best best ED value up to now
 * @param / @return d_bestRefOffset offset on ref corresponding to d_best
 * @param / @return d_second second best ED value up to now
 * @param / @return d_secondRefOffset offset on ref corresponding to d_second
 * @param d_new new ED value calculated
 * @param d_newRefOffset offset on ref corresponding to d_new
 */
static void updateBestAndSecondBest(uint64_t* d_best, uint64_t* d_bestRefOffset,
                                    uint64_t* d_second, uint64_t* d_secondRefOffset,
                                    uint64_t d_new, uint64_t d_newRefOffset) {
    if(d_new < *d_best) {
        *d_second = *d_best;
        *d_secondRefOffset = *d_bestRefOffset;
        *d_best = d_new;
        *d_bestRefOffset = d_newRefOffset;
    } else if (d_new >= *d_best && d_new < *d_second) {
        *d_second = d_new;
        *d_secondRefOffset = d_newRefOffset;
    } else {
        return;
    }
    return;
}






