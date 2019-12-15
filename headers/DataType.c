#include "DataType.h"


static void _uint64_tTest();


/**
 * A collection of test in this header file.
 */
void _DataTypeTestSet() {
    _uint64_tTest();
}


/*
 * Functions for testing.
 */

/**
 * Test data type "uint64_t".
 */
static void _uint64_tTest() {
    printf("\n**************** _uint64_tTest ****************\n");
    uint64_t num1 = 8914584519061689668;
    uint64_t num1_hex = 0x7BB6F7637ADE5544;
    uint64_t num2 = 8914584519061689668 >> 1;
    uint64_t num2_hex = 0x7BB6F7637ADE5544 >> 1;
    printf("uint64_t num1: %"PRIu64"\n", num1);
    printf("uint64_t num1_hex: %#"PRIx64"\n", num1_hex);
    printf("uint64_t num2: %"PRIu64"\n", num2);
    printf("uint64_t num2_hex: %#"PRIx64"\n", num2_hex);

    printf("num1 ^ num2: %#"PRIx64"\n", num1_hex ^ num2_hex);
    printf("num1 & num2: %#"PRIx64"\n", num1_hex & num2_hex);

    // bit-shifting will not affect the symbol of uint64_t
    printf("(num1 << 1) >> 1: %#"PRIx64"\n", (num1 << 1) >> 1);
}

/*
 * Working functions.
 */

/**
 * Initialize a struct Read.
 *
 * @param read pointer to a Read struct type
 */
void initializeRead(Read *read) {
//    read->QNAME = (char*)malloc(sizeof(char) * BUFSIZ);
    read->FLAG = 0x0;
//    read->RNAME = (char*)malloc(sizeof(char) * BUFSIZ);
    read->POS = 0;
    read->MAPQ = 0;
//    read->CIGAR = (char*)malloc(sizeof(char) * BUFSIZ);
//    read->RNEXT = (char*)malloc(sizeof(char) * BUFSIZ);
    read->PNEXT = 0;
    read->TLEN = 0;
//    read->SEQ = (char*)malloc(sizeof(char) * BUFSIZ);
//    read->QUAL = (char*)malloc(sizeof(char) * BUFSIZ);
}














