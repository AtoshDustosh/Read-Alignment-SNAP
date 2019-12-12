/**
 * \note about implementation
 *  1. planning to make the program read while processing instead of read all data in the
 *      beginning, as that may cost a lot memory. Maybe I will need to use a file pointer
 *      and transfer it between functions.
 *  2. recommend to use a struct type to store a read or an alignment result.
 *      i.e. struct{ sequence(...); quality(...)} for a read from ?.fastq file.
 *  date: 2019.12.12 22:09
 *      About the choice of algorithms, I find BWA and Bowtie are similar fundamentally.
 *  To be specific, they use identical method for exact matching. As for the in-exact
 *  matching, Bowtie uses the same method as exact matching with a little replacement,
 *  while BWA uses exact matching with interval backtracking and error-tolerance.
 *  So I think maybe if I can just apply a similar algorithm while not necessarily
 *  following their procedures. And it seems not very difficult.
 *
 *  date: 2019.12.12 22:34
 *      BWA and Bowtie are both just using BWT arrays of X and X_inverse to implement
 *  read-alignment. BWA permits insertion and deletion while Bowtie cannot implement them
 *  because of its backtracking method using replacement of base-pairs.
 *      Again I think it's feasible to directly build an algorithm while referring to
 *  theses papers.
 *
 */

/**
 * \note about ?.sam file:
 *  1. special header file needed for ?.sam file processing;
 *  2. not all fields are needed. I can just choose only the necessary.
 *  3. I think it's better to read reads to be aligned one by one instead of read them all
 *      at once in the beginning, which could cost a lot of memory.
 *  4. one thought - why must I obey the regulations declared in the SAM regulation manual?
 *      I can just use my own format to explain those fields as the SAM regulation and then
 *      transform the file into ?.sam file (^o')
 *      ...
 *      on second thought, this is even more troublesome.
 *
 *
 * \questions:
 *  1. should I fprintf results of read alignment one by one or store the results and
 *      fprintf them all in the end?
 *      - no. Because in SAM file, some fields of an alignment points to the next alignment.
 *      And on account of this, another question - should I store all results of alignment
 *      in memory before fprintf, or there is another better way to do this?
 *  2. ... can I set all fields whose representation meaning is confused for me as
 *      unavailable?
 *      - you'd better not ...
 *  3. some other questions are annotated in the SAM format manual.
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


