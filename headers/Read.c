#include "Read.h"



void initRead(Read *read) {
    if(read == NULL) {
        printf("ERROR: null pointer occurred when initializing a read. \n");
        exit(EXIT_FAILURE);
    }
    read->QNAME = (char*)malloc(sizeof(char) * BUFSIZ);
    read->QNAME[0] = '\0';
    read->FLAG = 0x0;
    read->RNAME = (char*)malloc(sizeof(char) * BUFSIZ);
    read->RNAME[0] = '\0';
    read->POS = 0;
    read->MAPQ = 0;
    read->CIGAR = (char*)malloc(sizeof(char) * BUFSIZ);
    read->CIGAR[0] = '\0';
    read->RNEXT = (char*)malloc(sizeof(char) * BUFSIZ);
    read->RNEXT[0] = '\0';
    read->PNEXT = 0;
    read->TLEN = 0;
    read->SEQ = (char*)malloc(sizeof(char) * BUFSIZ);
    read->SEQ[0] = '\0';
    read->QUAL = (char*)malloc(sizeof(char) * BUFSIZ);
    read->QUAL[0] = '\0';
}




void printRead(Read* read) {
    printf("QNAME\t%s\n", read->QNAME);
    printf("FLAG\t0x%x\n", read->FLAG);
    printf("RNAME\t%s\n", read->RNAME);
    printf("POS\t%d\n", read->POS);
    printf("MAPQ\t%f\n", read->MAPQ);
    printf("CIGAR\t%s\n", read->CIGAR);
    printf("RNEXT\t%s\n", read->RNEXT);
    printf("PNEXT\t%d\n", read->PNEXT);
    printf("TLEN\t%d\n", read->TLEN);
    printf("SEQ\t%s\n", read->SEQ);
    printf("QUAL\t%s\n", read->QUAL);
    printf("\n");

}










