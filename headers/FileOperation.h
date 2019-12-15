#ifndef FILEOPERATION_H_INCLUDED
#define FILEOPERATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/**
 * Get the size of data (DNA sequence) of a ?.fna file.
 *
 * @param filePath file path
 * @return data size of ?.fna file
 */
int fnaDataSize(char* filePath);

/**
 * Load ?.fna data file into memory - stored in an int[] array.
 *
 * @param filePath file Path
 * @param dataLength length of ?.fna data
 * @param T int[] array used to store data
 */
void loadFnaData(char* filePath, int dataLength, int* T);


#endif // FILEOPERATION_H_INCLUDED
