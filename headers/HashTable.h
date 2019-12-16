#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef struct _define_HashCell {
    uint64_t key;
//    char* str;
    int flag;
    struct _define_HashCell* nextCell;
} HashCell;

typedef struct _define_HashTable {
    HashCell* hashList;
} HashTable;


/**
 * A collection of test in this header file.
 */
void _HashTableTestSet();






/*
 * Working functions.
 */





/**
 * Display the hash table.
 *
 * @param hashTable hash table
 * @param tableSize size of the table
 */
void displayHashTable(HashTable* hashTable, uint64_t tableSize);

/**
 * Add a hash string with specific key as a hash cell into hash table.
 *
 * @param str string
 * @param key key of the string
 * @param tableSize size of the hash table
 * @param hashTable hash table
 */
void addHashCell(char* str, uint64_t key, HashTable* hashTable, uint64_t tableSize);

/**
 * Initialize a hash table of specific size.
 *
 * @param tableSize size of the hash table
 * @param hashTable hash table
 */
void initHashTable(uint64_t tableSize, HashTable* hashTable);

/**
 * Hash function used for calculating hash key of a string.
 *
 * @param str input string
 * @param tableSize size of the hash table
 * @return hash value
 */
uint64_t hashFunc(char *str, uint64_t tableSize);

#endif // HASHTABLE_H_INCLUDED
