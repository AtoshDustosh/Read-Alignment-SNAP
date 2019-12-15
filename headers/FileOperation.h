#ifndef FILEOPERATION_H_INCLUDED
#define FILEOPERATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * Get the size of data (DNA sequence) of a ?.fna file.
 *
 * @param filePath file path
 * @return data size of ?.fna file
 */
uint64_t fnaDataSize(char* filePath);

/**
 * Load ?.fna data file into memory - stored in an uint64_t[] array.
 *
 * @param filePath file Path
 * @param dataLength length of ?.fna data
 * @param T uint64_t[] array used to store data
 */
void loadFnaData(char* filePath, uint64_t dataLength, uint64_t* T);


#endif // FILEOPERATION_H_INCLUDED
