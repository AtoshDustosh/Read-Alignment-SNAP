#include "HashTable.h"


static void _initHashTableTest();
static void _addHashCellTest();

static void randomString(char* str, uint64_t strLength);
static uint64_t MyHash(char* str);
//static uint64_t BPHash(char* str);
//static uint64_t ELFhash(char *str);

void _HashTableTestSet() {
    _initHashTableTest();
    _addHashCellTest();
}

/*
 * Tests for working functions.
 */

/**
 * Test function initHashTable.
 */
static void _initHashTableTest() {
    printf("\n**************** _initHashTableTest ****************\n");
    printf("sizeof(HashCell): %d\n", sizeof(HashCell));
    HashTable hashTable;
    uint64_t tableSize = 10;

    initHashTable(tableSize, &hashTable);

    displayHashTable(&hashTable, tableSize);
}

/**
 * Test function addHashCell.
 */
static void _addHashCellTest() {
    printf("\n**************** _addHashCellTest ****************\n");
    HashTable hashTable;
    uint64_t tableSize = 500000;
    printf("hash table size: %"PRIu64"\n", tableSize);

    initHashTable(tableSize, &hashTable);

    uint64_t i = 0;
    char* str;
    uint64_t strLength = 20;
    for(i = 0; i < tableSize; i++) {
        str = (char*)malloc(sizeof(char) * strLength);
        randomString(str, strLength);
        addHashCell(str, i, &hashTable, tableSize);
    }

//    displayHashTable(&hashTable, tableSize);
    checkHashTablePerformance(&hashTable, tableSize);
}





/*
 * Working functions.
 */

void checkHashTablePerformance(HashTable* hashTable, uint64_t tableSize) {
    uint64_t i = 0;

    uint64_t totalBucketLength = 0;
    float bucketUsedCount = 0;
    for(i = 0; i < tableSize; i++) {
        HashCell* hashCell = &(hashTable->hashList[i]);
        totalBucketLength = totalBucketLength + hashCell->flag;
        bucketUsedCount = bucketUsedCount + (hashCell->flag && 1);
        do {
            if(hashCell == NULL || hashCell->flag == 0) {
                break;
            }
            hashCell = hashCell->nextCell;
        } while(1);
    }

    printf("total bucket length: %"PRIu64"\n", totalBucketLength);
    printf("average bucket length: %f\n",
           bucketUsedCount == 0 ? 0 : totalBucketLength / bucketUsedCount);
    printf("bucket usage ratio: %f\n", bucketUsedCount / tableSize);
}

void displayHashTable(HashTable* hashTable, uint64_t tableSize) {
    uint64_t i = 0;

    uint64_t maxBucketLength = 0;
    for(i = 0; i < tableSize; i++) {
        uint64_t tempLength = 0;
        printf("hash cell %"PRIu64"\t", i);
        HashCell* hashCell = &(hashTable->hashList[i]);
        do {
            if(hashCell == NULL || hashCell->flag == 0) {
                break;
            } else {
                printf("->\t");
            }
            printf("(%"PRIu64", %d, 0x%p)\t", hashCell->key, hashCell->flag,
                   hashCell->nextCell);
            tempLength++;
            hashCell = hashCell->nextCell;
        } while(1);
        printf("\n");
        if(tempLength > maxBucketLength){
            maxBucketLength = tempLength;
        }
    }
    printf("Maximum bucket length: %"PRIu64"\n", maxBucketLength);
}

void addHashCell(char* str, uint64_t key, HashTable* hashTable, uint64_t tableSize) {
    uint64_t index = hashIndex(str, tableSize);
    HashCell* hashCell = &(hashTable->hashList[index]);

    // if there is no hash-cell using that hash index
    if(hashCell->flag == 0) {
        hashCell->key = key;
        hashCell->flag = 1;
        hashCell->nextCell = NULL;
        return;
    }

    // if the hash index is already occupied
    do {
        // search to find a hash-cell whose next-hash-cell is NULL
        hashCell->flag++;   // use flag to count #(collisions)
        if(hashCell->nextCell != NULL) {
            hashCell = hashCell->nextCell;
        } else {
            break;
        }
    } while(1);
    // put a new hash-cell to the next-hash-cell
    HashCell* newHashCell = (HashCell*)malloc(sizeof(HashCell));
    newHashCell->key = key;
    newHashCell->flag = 1;
    newHashCell->nextCell = NULL;
    hashCell->nextCell = newHashCell;
}

void initHashTable(uint64_t tableSize, HashTable* hashTable) {
    hashTable->hashList = (HashCell*)malloc(sizeof(HashCell) * tableSize);
    uint64_t i = 0;
    if(hashTable->hashList == NULL) {
        printf("System memory not enough. \n");
        exit(EXIT_FAILURE);
    }
    for(i = 0; i < tableSize; i++) {
        HashCell* hashCell = (HashCell*)malloc(sizeof(HashCell));
        hashCell->key = 0;
        hashCell->flag = 0;
        hashCell->nextCell = NULL;
        hashTable->hashList[i] = *hashCell;
    }
}

uint64_t hashIndex(char *str, uint64_t tableSize) {
    return MyHash(str) % tableSize;
}





/*
 * Static functions. (file-localized functions)
 */




/**
 * My hash function.
 *
 * total bucket length: 5000000
 * average bucket length: 1.590123
 * bucket usage ratio: 0.628882
 *
 * @param str input string
 * @param hash value
 */
static uint64_t MyHash(char* str) {
    uint64_t hash = 0;

    while(*str != '\0') {
        uint64_t x = hash & 0xf000000000000000;
        hash = (hash << 2) + *str;
        if(x != 0) {
            hash = hash ^ (x >> 60);
            hash = hash & ~x;
        }
        str++;  // use pointers to go forward on a string
    }
    return (hash & 0x7fffffffffffffff);
}

///**
// * BPHash function. \note aborted
// *
// * total bucket length: 500000
// * average bucket length: 8.020018
// * bucket usage ratio: 0.124688
// *
// * @param str input string
// * @param hash value
// */
//static uint64_t BPHash(char* str) {
//    uint64_t hash = 0;
//    while(*str != '\0') {
//        hash = (hash << 7) ^ (*str);
//        str++;
//    }
//    return hash;
//}
//
///**
// * ELFHash function.
// *
// * total bucket length: 5000000
// * average bucket length: 1.801436
// * bucket usage ratio: 0.555113
// *
// * @param str input string
// * @param hash value
// */
//static uint64_t ELFhash(char *str) {
//    uint64_t hash = 0;
//
//    while(*str != '\0') {
//        uint64_t x = hash & 0xf000000000000000;
//        hash = (hash << 4) + *str;
//        if(x != 0) {
//            hash = hash ^ (x >> 60);
//            hash = hash & ~x;
//        }
//        str++;  // use pointers to go forward on a string
//    }
//    return (hash & 0x7fffffffffffffff);
//}

/**
 * Generate a random string at a specific length.
 *
 * @param str generated string
 * @param strLength length of string
 */
static void randomString(char* str, uint64_t strLength) {
    uint64_t i = 0;
    for(i = 0; i < strLength; i++) {
        char randChar = (rand() % 26) % 4 + 'a';
        str[i] = randChar;
    }
    str[i] = '\0';
}


