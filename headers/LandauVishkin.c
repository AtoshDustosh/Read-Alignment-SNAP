#include "LandauVishkin.h"

static void calculateLandauVishkinScoringMatrix(uint64_t **matrix, StringBuffer* strRow,
        StringBuffer* strColumn, uint64_t EDmax);

/*
 * Declarations of tests.
 */
static void _calculateEditDistanceTest();


void _LandauVishkinTestSet() {
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

    strBuf1->buffer = "1234567";
    strBuf1->length = 7;
    strBuf2->buffer = "1234";
    strBuf2->length = 4;

    calculateEditDistance(strBuf1, strBuf2, 3);
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
    uint64_t matrix[rowNum][columnNum];

    for(uint64_t i = 0; i < rowNum; i++) {
        for(uint64_t j = 0; j < columnNum; j++) { // initialize scoring matrix
            matrix[i][j] = 0;
        }
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

    strBuf1 = (StringBuffer*)malloc(sizeof(StringBuffer));
    strBuf2 = (StringBuffer*)malloc(sizeof(StringBuffer));
    constructStringBuffer(strBuf1, strRow, rowNum);
    constructStringBuffer(strBuf2, strColumn, columnNum);

    /*
     * Start calculation.
     */
    calculateLandauVishkinScoringMatrix((uint64_t**)matrix, strBuf1, strBuf2, EDmax);

    return 0;
}


/*
 * Static functions. (file-localized functions)
 */

/**
 * Calculate the scoring matrix needed when using Landau-Vishkin algorithm.
 *
 * @param matrix scoring matrix - all values initialized as 0
 * @param strRow row string of the scoring matrix
 * @param strColumn column string of the scoring matrix
 * @param EDmax maximum edit distance that can be accepted
 */
static void calculateLandauVishkinScoringMatrix(uint64_t **matrix, StringBuffer* strRow,
        StringBuffer* strColumn, uint64_t EDmax) {
//    /**
//     * \note for matrix[i][j], use "matrix[row * rowNum + column]".
//     */
//    const uint64_t rowNum = strRow->length;
//    const uint64_t columnNum = strColumn->length;
//
//    struct Point {
//        int row;
//        int column;
//    };
//
//    uint64_t row = 0;
//    uint64_t column = 0;
//
//    uint64_t startRow = row;
//    uint64_t startColumn = column;
//
//    uint64_t endRow = row;
//    uint64_t endColumn = column;
//
//    while(1) {
//        /**< \note extend diagonally until encountering a mismatch or indel */
//        row = startRow;
//        column = startColumn;
//        while((row + 1) < strRow->length && (column + 1) < strColumn->length) {
//            if(strRow->buffer[row + 1] == strColumn->buffer[column + 1]) {
//                matrix[(row + 1) * rowNum + (column + 1)] = matrix[row * rowNum + column];
//                row++;
//                column++;
//            } else {
//                break;
//            }
//        }
//        endRow = row;
//        endColumn = column;
//
//        /**< \note try to change startPoint if cannot extend diagonally */
//        if(endRow == startRow && endColumn == startColumn) {
//            if((startColumn + 1) < strColumn->length
//                    && strRow->buffer[startRow] == strColumn->buffer[startColumn + 1]) {
//                /**< \note try to switch startPoint horizontally */
//                startColumn = startColumn + 1;
//                continue;
//            } else if((startRow + 1) < strRow->length
//                      && strRow->buffer[startRow + 1] == strColumn->buffer[startColumn]) {
//                /**< \note try to switch startPoint vertically */
//                startRow = startRow + 1;
//                continue;
//            } else {
//                /**< \note cannot do extension no matter how */
//                break;
//            }
//        }
//
//        /**< \note extend diagonally matched points horizontally and vertically */
//        row = startRow;
//        column = startColumn;
//        for(uint64_t i = 0;; row < startRow && column < endColumn; row++, column++) {
//            /**< \note extend horizontally */
//            i = column;
//            while((i + 1) < strColumn->length) {
//                if(strRow->buffer[row] != strColumn->buffer[i + 1]) {
//                    matrix[row * rowNum + (i + 1)] = matrix[row * rowNum + i] + 1;
//                } else {
//                    matrix[row * rowNum + (i + 1)] = matrix[row * rowNum + i];
//                }
//                i++;
//            }
//            /**< \note extend vertically */
//            i = row;
//            while((i + 1) < strRow->length) {
//                if(strRow->buffer[i + 1] != strColumn->buffer[column]) {
//                    matrix[(i + 1) * rowNum + column] = matrix[i * rowNum + column] + 1;
//                } else {
//                    matrix[(i + 1) * rowNum + column] = matrix[i * rowNum + column];
//                }
//            }
//        }
//    }
}


























