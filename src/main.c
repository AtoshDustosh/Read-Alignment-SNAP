#include <stdio.h>
#include <stdlib.h>

#include "../headers/AuxiliaryFunction.h"
#include "../headers/FileOperation.h"
#include "../headers/DataType.h"
#include "../headers/ArrayOperation.h"


char* fnaFilePath = "data/fna/testdata_100.fna";

void testSet();

int dataLength = 0;
int* T;


int main() {
    testSet();

    dataLength = fnaDataSize(fnaFilePath);
    T = (int*)malloc(sizeof(int) * dataLength);
    loadFnaData(fnaFilePath, dataLength, T);


    free(T);
    return 0;
}

void testSet(){
    _AuxiliaryFunctionTestSet();
    _ArrayOperationTestSet();
    _DataTypeTest();
}
