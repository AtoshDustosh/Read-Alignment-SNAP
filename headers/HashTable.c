#include "HashTable.h"

#include "AuxiliaryFunction.h"


static void _initHashTableTest();
static void _addHashCellTest();

static void randomString(char* str, uint64_t strLength);
static uint64_t ELFhash(char *str);

/**
 * A collection of test in this header file.
 */
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
//    uint64_t i = 0;
//    for(i = 0; i < tableSize; i++) {
//        HashCell cell = hashTable.hashList[i];
//        printf("cell key: %"PRIu64". ", cell.key);
//        printf("cell flag: %d.", cell.flag);
//        printf("next cell: 0x%p. ", cell.nextCell);
//        printf("\n");
//    }
}

/**
 * Test function addHashCell.
 */
static void _addHashCellTest() {
    printf("\n**************** _addHashCellTest ****************\n");
    HashTable hashTable;
    uint64_t tableSize = 50;
    printf("hash table size: %"PRIu64"\n", tableSize);

    initHashTable(tableSize, &hashTable);

    uint64_t i = 0;
    char str[12];
    uint64_t strLength = 10;
    for(i = 0; i < tableSize; i++) {
        randomString(str, strLength);
        addHashCell(str, i, &hashTable, tableSize);
    }

    displayHashTable(&hashTable, tableSize);
}





/*
 * Working functions.
 */


/**
 * Display the hash table.
 *
 * @param hashTable hash table
 * @param tableSize size of the table
 */
void displayHashTable(HashTable* hashTable, uint64_t tableSize) {
    uint64_t i = 0;

    uint64_t totalBucketLength = 0;
    float bucketUsedCount = 0;
    for(i = 0; i < tableSize; i++) {
        printf("%"PRIu64"\t", i);
        HashCell* hashCell = &(hashTable->hashList[i]);
        totalBucketLength = totalBucketLength + hashCell->flag;
        bucketUsedCount = bucketUsedCount + (hashCell->flag && 1);
        do {
            if(hashCell == NULL || hashCell->flag == 0) {
                break;
            } else {
                printf("->\t");
            }
            printf("(%"PRIu64", %d, 0x%p)\t", hashCell->key, hashCell->flag, hashCell->nextCell);
            hashCell = hashCell->nextCell;
        } while(1);
        printf("\n");
    }

    printf("average bucket length: %f\n", totalBucketLength / bucketUsedCount);
    printf("bucket usage ratio: %f\n", bucketUsedCount / tableSize);
}

/**
 * Add a hash string with specific key as a hash cell into hash table.
 *
 * @param str string
 * @param key key of the string
 * @param tableSize size of the hash table
 * @param hashTable hash table
 */
void addHashCell(char* str, uint64_t key, HashTable* hashTable, uint64_t tableSize) {
    uint64_t hashIndex = hashFunc(str, tableSize);
    HashCell* hashCell = &(hashTable->hashList[hashIndex]);
//    printf("str: %s, key: %"PRIu64", index: %"PRIu64"\n", str, key, hashIndex);

    // if there is no hash-cell using that hash index
    if(hashCell->flag == 0) {
        hashCell->key = key;
//        hashCell->str = "abcdef";
        hashCell->flag = 1;
        hashCell->nextCell = NULL;
        return;
    }

    // if the hash index is already occupied
//    printf("    collision occurs\n");
    do {
        // search to find a hash-cell whose next-hash-cell is NULL
        hashCell->flag++;   // use flag to count #(collisions)
//        printf("(%d, %s, %d, 0x%p)\t", hashCell->key, hashCell->str, hashCell->flag, hashCell->nextCell);
        if(hashCell->nextCell != NULL) {
            hashCell = hashCell->nextCell;
        } else {
            break;
        }
    } while(1);
//    printf("\n");
    // put a new hash-cell to the next-hash-cell
    HashCell* newHashCell = (HashCell*)malloc(sizeof(HashCell));
    newHashCell->key = key;
//    newHashCell->str = "aaaaaa";
    newHashCell->flag = 1;
    newHashCell->nextCell = NULL;
    hashCell->nextCell = newHashCell;
}

/**
 * Initialize a hash table of specific size.
 *
 * @param tableSize size of the hash table
 * @param hashTable hash table
 */
void initHashTable(uint64_t tableSize, HashTable* hashTable) {
    hashTable->hashList = (HashCell*)malloc(sizeof(HashCell) * tableSize);
    uint64_t i = 0;
    for(i = 0; i < tableSize; i++) {
        HashCell* hashCell = (HashCell*)malloc(sizeof(HashCell));
        hashCell->key = 0;
        hashCell->flag = 0;
        hashCell->nextCell = NULL;
        hashTable->hashList[i] = *hashCell;
    }
}


/**
 * Hash function used for calculating hash key of a string.
 *
 * @param str input string
 * @param tableSize size of the hash table
 * @return hash value
 */
uint64_t hashFunc(char *str, uint64_t tableSize) {
    return ELFhash(str) % tableSize;
}


/*
 * Static functions. (file-localized functions)
 */



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


/**
 * ELFHash function.
 *
 * @param str input string
 * @param hash key value
 */
static uint64_t ELFhash(char *str) {
    uint64_t hash = 0;

    while(*str != '\0') {
        uint64_t x = hash & 0xf000000000000000;
        hash = (hash << 4) + lowerCase(*str) - 'a';
        if(x != 0) {
            hash = hash ^ (x >> 60);
            hash = hash & ~x;
        }
        str++;  // use pointers to go forward on a string
    }
    return (hash & 0x7fffffffffffffff);
}
