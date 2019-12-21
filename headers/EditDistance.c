#include "EditDistance.h"

#include "AuxiliaryFunction.h"

#define DIAGONALLYEXTENDED 1

static int extendEditDistanceMatrix(StringBuffer* strRow, StringBuffer* strColumn,
                                    int** EDmatrix, int** diagonallyExtendedMatrix, int startRow,
                                    int startColumn, int EDmax);

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
    strBuf1->length = strlen(strBuf1->buffer);
    strBuf2->buffer = "agcgc";
    strBuf2->length = strlen(strBuf2->buffer);

    uint64_t EDmax = 2;

    calculateEditDistance(strBuf1, strBuf1, EDmax);
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
    const int rowNum = strBuf1->length + 1;
    const int columnNum = strBuf2->length + 1;

    /*
     * Initializations.
     */
    char* strRow = (char*)malloc(sizeof(char) * (rowNum + 1));
    char* strColumn = (char*)malloc(sizeof(char) * (columnNum + 1));
    int EDmatrix[rowNum][columnNum];
    int diagonallyExtendedMatrix[rowNum][columnNum];

    for(int i = 0; i < rowNum; i++) {      // initialize edit-distance matrix
        for(int j = 0; j < columnNum; j++) {
            EDmatrix[i][j] = 10000;
            diagonallyExtendedMatrix[i][j] = 0;
        }
    }
    for(int i = 0; i < rowNum; i++) {      // initialize first row (bounder) of edit-distance matrix
        EDmatrix[i][0] = i;
    }
    for(int i = 0; i < columnNum; i++) { // initialize first column (bounder) of edit-distance matrix
        EDmatrix[0][i] = i;
    }
    for(int i = 0; i < rowNum; i++) {      // copy strBuf1
        strRow[i + 1] = strBuf1->buffer[i];
    }
    strRow[0] = ' ';
    strRow[rowNum] = '\0';
    for(int i = 0; i < columnNum; i++) {   // copy strBuf2
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
    for(int i = 0; i < rowNum; i++) {
        for(int j = 0; j < columnNum; j++) {
            printf("%d\t", EDmatrix[i][j]);
        }
        printf("\n\n");
    }
    int result = extendEditDistanceMatrix(strBufRow, strBufColumn, (int**)EDmatrix,
                                          (int**)diagonallyExtendedMatrix, 0, 0, (int)EDmax);


    printf("ED matrix:\n");
    for(int i = 0; i < rowNum; i++) {
        for(int j = 0; j < columnNum; j++) {
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
static int extendEditDistanceMatrix(StringBuffer* strRow, StringBuffer* strColumn,
                                    int** EDmatrix, int** diagonallyExtendedMatrix, int startRow,
                                    int startColumn, int EDmax) {
    /**
     * \note for "matrix[i][j]", use "matrix[row * rowNum + column]",
     *       or "*(matrix + row * rowNum + column)".
     */
    const int rowNum = strRow->length;
    const int columnNum = strColumn->length;

    int row = startRow;
    int column = startColumn;

    int endRow = startRow;
    int endColumn = startColumn;

    printf("--------------------extend edit-distance matrix\n");
    printf("startRow: %d, startColumn: %d\n", startRow, startColumn);
    printStringBuffer(strRow);
    printStringBuffer(strColumn);
    printf("ED max: %d\n", EDmax);
    printf("ED matrix: \n");
    for(int i = 0; i < rowNum; i++) {
        for(int j = 0; j < columnNum; j++) {
            printf("%d\t", (int)EDmatrix[i * rowNum + j]);
        }
        printf("\n\n");
    }

    if(startRow < 0 || startColumn < 0) {
        printf("Parameter not valid in method extendEditDistanceMatrix. \n");
        exit(-1);
    }

    /**< \note extend diagonally until extensions cannot be made any more */
    endRow = startRow;
    endColumn = startColumn;
    for(row = startRow + 1, column = startColumn + 1; row < rowNum
            && column < columnNum; row++, column++) {
        char charOfThisRow = strRow->buffer[row];
        char charOfThisColumn = strColumn->buffer[column];
        int EDofLastPoint = (int)EDmatrix[(row - 1) * rowNum + (column - 1)];
        printf("ED of last point: %d\n", EDofLastPoint);

        if(charOfThisRow == charOfThisColumn) {
            *(EDmatrix + row * rowNum + column) = (int*)EDofLastPoint;
            *(diagonallyExtendedMatrix + row * rowNum + column) = (int*)DIAGONALLYEXTENDED;
            endRow++;
            endColumn++;
        } else {
            *(EDmatrix + row * rowNum + column) = (int*)(EDofLastPoint + 1);
            *(diagonallyExtendedMatrix + row * rowNum + column) = (int*)DIAGONALLYEXTENDED;
            break;
        }
    }
    printf(">>>>>>>>>>>> after diagonal extension - ED matrix: \n");
    for(int i = 0; i < rowNum; i++) {
        for(int j = 0; j < columnNum; j++) {
            printf("%d\t", (int)EDmatrix[i * rowNum + j]);
        }
        printf("\n\n");
    }

    /**< \note extend from all points that are just extended diagonally */
    for(row = startRow, column = startColumn; row < endRow && column < endColumn; row++, column++) {
        /**< \note extend horizontally */
        for(int i = column + 1; i < columnNum; i++) {
            if(row == 0) {
                continue;
            }
            int EDofLastPoint = (int)(*(EDmatrix + (row - 1) * rowNum + (i - 1)));
            int EDofLeftPoint = (int)(*(EDmatrix + row * rowNum + (i - 1)));
            int EDofUpperPoint = (int)(*(EDmatrix + (row - 1) * rowNum + i));
            int value = minInt(minInt(EDofLastPoint, EDofLeftPoint),
                                minInt(EDofLastPoint, EDofUpperPoint)) + 1;
            *(EDmatrix + row * rowNum + i) = (int*)value;
            printf("(%d,%d) - EDofLastPoint:%d, EDofLeftPoint:%d, EDofUpperPoint:%d -> %d\n",
                   row, i, EDofLastPoint, EDofLeftPoint, EDofUpperPoint, value);
            if(value > EDmax) {
                break;
            }
        }
        /**< \note extend vertically */
        for(int i = row + 1; i < rowNum; i++) {
            if(column == 0) {
                continue;
            }
            int EDofLastPoint = (int)(*(EDmatrix + (i - 1) * rowNum + (column - 1)));
            int EDofLeftPoint = (int)(*(EDmatrix + i * rowNum + (column - 1)));
            int EDofUpperPoint = (int)(*(EDmatrix + (i - 1) * rowNum + column));
            int value = minInt(minInt(EDofLastPoint, EDofLeftPoint),
                               minInt(EDofLastPoint, EDofUpperPoint)) + 1;
            EDmatrix[i * rowNum + column] = (int*)value;
            if(value > EDmax) {
                break;
            }
        }
    }
    printf(">>>>>>>>>>>> after horizontal and vertical extension - ED matrix: \n");
    for(int i = 0; i < rowNum; i++) {
        for(int j = 0; j < columnNum; j++) {
            printf("%d\t", (int)EDmatrix[i * rowNum + j]);
        }
        printf("\n\n");
    }

    int startRow_next = endRow + 1;
    int startColumn_next = endColumn + 1;

    // start recursion
    if(startRow_next == rowNum && startColumn_next == columnNum) {
        /**< \note reaches the end of the matrix */
        return 1;
    } else if(startRow_next == rowNum && startColumn_next != columnNum) {
        /**< \note reaches the end of row, but not the column */
        return extendEditDistanceMatrix(strRow, strColumn, EDmatrix, diagonallyExtendedMatrix,
                                        endRow, startColumn_next, EDmax);
    } else if(startRow_next != rowNum && startColumn_next == columnNum) {
        /**< \note reaches the end of column, but not the row */
        return extendEditDistanceMatrix(strRow, strColumn, EDmatrix, diagonallyExtendedMatrix,
                                        startRow_next, endColumn, EDmax);
    } else if(startRow_next != rowNum && startColumn_next != columnNum) {
        /**< \note still within range of the matrix */
        if(EDmatrix[startRow_next * rowNum + startColumn_next] <= (int*)EDmax) {
            /**< \note mismatch occurs but still within EDmax */
            if(diagonallyExtendedMatrix[startRow_next * rowNum + startColumn_next]
                    != (int*)DIAGONALLYEXTENDED) {
                /**< \note startPoint_next is not diagonally extended yet */
                return extendEditDistanceMatrix(strRow, strColumn, EDmatrix, diagonallyExtendedMatrix,
                                                startRow_next, startColumn_next, EDmax);
            } else {
                /**< \note startPoint_next has already been extended */
                return 0;
            }
        } else {
            /**< \note mismatch occurs and out of range of EDmax */
            int switchPointVertically = 0;
            int switchPointHorizontally = 0;
            if(diagonallyExtendedMatrix[startRow_next * rowNum + endColumn] != (int*)DIAGONALLYEXTENDED
                    && EDmatrix[startRow * rowNum + endColumn] <= (int*)EDmax) {
                /**< \note try to switch to the lower point and extend diagonally */
                switchPointVertically = extendEditDistanceMatrix(strRow, strColumn, EDmatrix,
                                        diagonallyExtendedMatrix, startRow_next, endColumn, EDmax);
            }
            if(diagonallyExtendedMatrix[endRow * rowNum + startColumn_next] != (int*)DIAGONALLYEXTENDED
                    && EDmatrix[endRow * rowNum + startColumn_next] <= (int*)EDmax) {
                /**< \note try to switch to the right point and extend diagonally */
                switchPointHorizontally = extendEditDistanceMatrix(strRow, strColumn, EDmatrix,
                                          diagonallyExtendedMatrix, endRow, startColumn_next, EDmax);
            }
            return switchPointVertically || switchPointHorizontally;
        }
    }
    // this line will never be reached
    return 0;
}


























