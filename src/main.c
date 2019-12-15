#include <stdio.h>
#include <stdlib.h>

#include "../headers/AuxiliaryFunction.h"
#include "../headers/FileOperation.h"
#include "../headers/DataType.h"
#include "../headers/ArrayOperation.h"

char* fnaFilePath = "data/fna/testdata_100.fna";

void testSet();

uint64_t dataLength = 0;
uint64_t* T;


int main() {
    testSet();

    dataLength = fnaDataSize(fnaFilePath);
    T = (uint64_t*)malloc(sizeof(uint64_t) * dataLength);
    loadFnaData(fnaFilePath, dataLength, T);


    free(T);
    return 0;
}

void testSet() {
    _AuxiliaryFunctionTestSet();
    _ArrayOperationTestSet();
    _DataTypeTest();
}
