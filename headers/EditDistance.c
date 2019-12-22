#include "EditDistance.h"

#include <string.h>

#include "AuxiliaryFunction.h"

#define DIAGONALLYEXTENDED 1

static void extendEditDistanceMatrix(StringBuffer* strRow, StringBuffer* strColumn,
                                    uint64_t* EDmatrix, uint64_t* diagonallyExtendedMatrix, uint64_t startRow,
                                    uint64_t startColumn, uint64_t EDmax);

/*
 * Declarations of tests.
 */
static void _calculateEditDistanceTest();


void _EditDistanceTestSet() {
    _calculateEditDistanceTest();
}


/*
 * Tests for working functions.
 */

/**
 * Test function calculateEditDistance.
 */
static void _calculateEditDistanceTest() {
    printf("\n**************** _calculateEditDistanceTest ****************\n");
    StringBuffer* strBuf1 = (StringBuffer*)malloc(sizeof(StringBuffer));
    StringBuffer* strBuf2 = (StringBuffer*)malloc(sizeof(StringBuffer));
    initStringBuffer(strBuf1);
    initStringBuffer(strBuf2);

    strBuf1->buffer = "agtccg";
    strBuf1->length = (uint64_t)strlen(strBuf1->buffer);
    strBuf2->buffer = "agcgc";
    strBuf2->length = (uint64_t)strlen(strBuf2->buffer);

    uint64_t EDmax = 2;

//    calculateEditDistance(strBuf1, strBuf1, EDmax);
}

/*
 * Working functions.
 */
uint64_t calculateEditDistance(StringBuffer* strBuf1, StringBuffer* strBuf2, uint64_t EDmax) {
    /*
     * Actually, considering the size of EDmax, we don't need to use uint64_t, and uint8_t
     * is enough for EDmax and scoreMatrix.
     * But for better correctness, we leave optimizations for future work.
     */
    const uint64_t rowNum = strBuf1->length + 1;
    const uint64_t columnNum = strBuf2->length + 1;

    /*
     * Initializations.
     */
    char* strRow = (char*)malloc(sizeof(char) * (rowNum + 1));
    char* strColumn = (char*)malloc(sizeof(char) * (columnNum + 1));
    uint64_t EDmatrix[rowNum][columnNum];
    uint64_t diagonallyExtendedMatrix[rowNum][columnNum];

    for(uint64_t i = 0; i < rowNum; i++) {      // initialize edit-distance matrix
        for(uint64_t j = 0; j < columnNum; j++) {
            EDmatrix[i][j] = 0;
            diagonallyExtendedMatrix[i][j] = 0;
        }
    }
    for(uint64_t i = 0; i < rowNum; i++) {      // initialize first row (bounder) of edit-distance matrix
        EDmatrix[i][0] = i;
    }
    for(uint64_t i = 0; i < columnNum; i++) { // initialize first column (bounder) of edit-distance matrix
        EDmatrix[0][i] = i;
    }
    for(uint64_t i = 0; i < rowNum; i++) {      // copy strBuf1
        strRow[i + 1] = strBuf1->buffer[i];
    }
    strRow[0] = ' ';
    strRow[rowNum] = '\0';
    for(uint64_t i = 0; i < columnNum; i++) {   // copy strBuf2
        strColumn[i + 1] = strBuf2->buffer[i];
    }
    strColumn[0] = ' ';
    strColumn[columnNum] = '\0';

    StringBuffer* strBufRow = (StringBuffer*)malloc(sizeof(StringBuffer));
    StringBuffer* strBufColumn = (StringBuffer*)malloc(sizeof(StringBuffer));
    constructStringBuffer(strBufRow, strRow, rowNum);
    constructStringBuffer(strBufColumn, strColumn, columnNum);

//    printStringBuffer(strBufRow);
//    printStringBuffer(strBufColumn);

    /*
     * Calculate the edit-distance matrix.
     */
    printf("initialized ED matrix:\n");
    for(uint64_t i = 0; i < rowNum; i++) {
        for(uint64_t j = 0; j < columnNum; j++) {
            printf("%d\t", EDmatrix[i][j]);
        }
        printf("\n\n");
    }

    extendEditDistanceMatrix(strBufRow, strBufColumn, (uint64_t*)EDmatrix,
                                          (uint64_t*)diagonallyExtendedMatrix, 0, 0, EDmax);


    printf("ED matrix:\n");
    for(uint64_t i = 0; i < rowNum; i++) {
        for(uint64_t j = 0; j < columnNum; j++) {
            printf("%d\t", EDmatrix[i][j]);
        }
        printf("\n\n");
    }


    return 0;
}


/*
 * Static functions. (file-localized functions)
 */

/**
 * Extend the edit-distance matrix of 2 strings from (startRow, startColumn) to the end, or until
 * extensions cannot be made any more.
 *
 * @param strRow row string of the edit-distance matrix
 * @param strColumn column string of the edit-distance matrix
 * @param EDmatrix edit-distance matrix - for i = 0 : n-1 {EDmatrix[0][i] = EDmatrix[i][0] = i};
 *      all other values are initialized as 0
 * @param diagonallyExtendedMatrix flags marking whether a point has been tried to extend diagonally
 * @param startRow row of start point (startRow >= 1)
 * @param startColumn column of start point (startColumn >= 1)
 * @param EDmax maximum edit distance that can be allowed
 * @return whether extension succeeds or not
 */
static void extendEditDistanceMatrix(StringBuffer* strRow, StringBuffer* strColumn,
                                    uint64_t* EDmatrix, uint64_t* diagonallyExtendedMatrix, uint64_t startRow,
                                    uint64_t startColumn, uint64_t EDmax) {
    /**
     * \note for "matrix[i][j]", use "matrix[row * rowNum + column]",
     *       or "*(matrix + row * rowNum + column)".
     */

    /**< \todo */


}


























