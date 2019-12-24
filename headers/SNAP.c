#include "SNAP.h"

#include "MyArgs.h"
#include "AuxiliaryFunction.h"


static void _extractHexCodedSeedFromRefTest();



void _SNAPTestSet() {
    _extractHexCodedSeedFromRefTest();
}



/*
 * Test functions.
 */

static void _extractHexCodedSeedFromRefTest(){
    printf("\n*************** _extractHexCodedSeedFromRefTest ***************\n");
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
    seedHexCodedStrBuf = extractHexCodedSeedFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: ttttcattctgactgcaacg\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 20;
    DNAoffset = 20;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: acgggcaatatgagcttttc\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 32;
    DNAoffset = 16;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: tgcaacgggcaatatgagcttttcattctgac\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);

    printf("\n");

    seedLength = 32;
    DNAoffset = 0;
    printf("seed length: %"PRIu64", offset: %"PRIu64"\n", seedLength, DNAoffset);
    seedHexCodedStrBuf = extractHexCodedSeedFromRef(hexCodedDNA, DNAlength, seedLength, DNAoffset);
    printf("expected: agcttttcattctgactgcaacgggcaatatg\n");
    transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
    printHexCodedStringBuffer(seedHexCodedStrBuf);
    printStringBuffer(seedStrBuf);
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
            extractHexCodedSeedFromRef(hexCodedRefDNA, DNAlength, seedLength, offset);
//        printHexCodedStringBuffer(seedHexCodedStrBuf);
        transHexCodedStringBufferToStringBuffer(seedHexCodedStrBuf, seedStrBuf, CHAR_NUM_PER_HEX);
//        printStringBuffer(seedStrBuf);
        addHashCell(seedStrBuf->buffer, offset, snap->hashTable, tableSize);
    }

    checkHashTablePerformance(snap->hashTable, tableSize);

    return snap;
}


HexCodedStringBuffer* extractHexCodedSeedFromRef(uint64_t* hexCodedDNA, uint64_t DNAlength,
        uint64_t seedLength, uint64_t DNAoffset) {
    if(seedLength > CHAR_NUM_PER_HEX || seedLength <= 0){
        printf("ERROR: length of a seed is too long or not valid - %"PRIu64"\n", seedLength);
        exit(EXIT_FAILURE);
    }
    if(seedLength + DNAoffset > DNAlength){
        printf("ERROR: seed out of reference DNA - offset: %"PRIu64"\n", DNAoffset);
        exit(EXIT_FAILURE);
    }

    HexCodedStringBuffer* seedHexCodedStrBuf =
        (HexCodedStringBuffer*)malloc(sizeof(HexCodedStringBuffer));
    uint64_t* hexArray = (uint64_t*)malloc(sizeof(uint64_t));
    uint64_t arrayLength = 1;
    uint64_t strLength = seedLength;

    uint64_t hexInt = 0x0;  // the hex-coded seed string
//    printf("???\n");
    for(uint64_t i = 0; i < seedLength; i++){
        uint64_t DNAhexIntIndex = (DNAoffset + i) / CHAR_NUM_PER_HEX;
        uint64_t DNAhexInt = *(hexCodedDNA + DNAhexIntIndex);
        uint64_t hexIntOffset = (i + (DNAoffset % CHAR_NUM_PER_HEX)) % CHAR_NUM_PER_HEX;
        uint64_t charHex = extractCharBitFromHexInt(hexIntOffset, DNAhexInt, CHAR_NUM_PER_HEX);
        uint64_t bitInterval = sizeof(uint64_t) * 8 / CHAR_NUM_PER_HEX;
//        printf("%"PRIu64"\t->\t%#"PRIx64"\t(%c)\n", hexIntOffset, charHex, hexToChar(charHex));
        charHex = charHex << ((CHAR_NUM_PER_HEX - 1 - i) * bitInterval);
        hexInt = hexInt | charHex;
//        printf("%#"PRIx64"\n", hexInt);
    }
//    printf("hexInt: %#"PRIx64"\n", hexInt);

    hexArray[0] = hexInt;
    constructHexCodedStringBuffer(seedHexCodedStrBuf, hexArray, arrayLength, strLength);
    return seedHexCodedStrBuf;
}
