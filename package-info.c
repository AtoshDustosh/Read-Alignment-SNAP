/**
 * \note about implementation
 *  1. planning to make the program read while processing instead of read all data in the
 *      beginning, as that may cost a lot memory. Maybe I will need to use a file pointer
 *      and transfer it between functions.
 *  2. recommend to use a struct type to store a read or an alignment result.
 *      i.e. struct{ sequence(...); quality(...)} for a read from ?.fastq file.
 *
 */

/**
 * \note about ?.sam file:
 *  1. special header file needed for ?.sam file processing;
 *  2. not all fields are needed. I can just choose only the necessary and then implement.
 *  3. I think it's better to read reads to be aligned one by one instead of read them all
 *      at once in the beginning, which could cost a lot of memory.
 *  4. one question - why must I obey the regulations declared in the SAM regulation manual?
 *      I can just use my own format to explain those fields as the SAM regulation and then
 *      transform the file into ?.sam file (^o')
 *
 *
 *
 * \note format of ?.sam file chosen to implement in this program.
 * @HD VN:1.6
 * @
 *
 *
 * QUESTIONS:
 *  1. should I fprintf results of read alignment one by one or store the results and
 *      fprintf them all in the end?
 *  2. ... can I set all fields whose representation meaning is confused for me as
 *      unavailable?
 */

/**
 * \note about ?.bwt file:
 *  1. need to process the first line of bwt file and get name of the reference sequence.
 *  2.
 *
 *
 * \note format of ?.bwt file implemented in this program.
 *  1) header line: ">gi|110640213|ref|NC_008253.1| Escherichia coli 536, bwt array"
 *  2) ">gi|110640213|ref|NC_008253.1|" is the necessary identifier of the genome sequence.
 *  3) the name after "|ref|" is the name of the genome sequence - to be extracted for
 *      the construction of ?.sam file.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


