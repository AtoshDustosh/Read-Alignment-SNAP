#include "DataType.h"

/**
 * A collection of test in this header file.
 */
void _DataTypeTest() {
    _uint64_tTest();
}


/*
 * Functions for testing.
 */

/**
 * Test data type "uint64_t".
 */
void _uint64_tTest() {
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
