#include "SAM.h"



SAM* constructSAM(char* filePath) {
    SAM* sam = (SAM*)malloc(sizeof(SAM));
    FILE* fpointer = fopen(filePath, "w");

    sam->filePath = filePath;
    if(fpointer == NULL){
        printf("ERROR: cannot create new file under file path - %s\n", filePath);
        exit(EXIT_FAILURE);
    }
    sam->fpointer = fpointer;
    sam->lastRead = NULL;
    sam->newRead = NULL;
    fprintf(sam->fpointer, "%s\n", "@HD VN:version");
    fprintf(sam->fpointer, "%s\n", "@SQ SN:ref_name LN:ref_length");
    return sam;
}


void fprintReadUsingSAM(Read* read, SAM* sam) {
    if(sam->newRead == NULL){
        sam->newRead = read;
    } else if(sam->newRead != NULL && sam->lastRead == NULL) {
        sam->lastRead = sam->newRead;
        sam->newRead = read;
    } else {
        clearRead(sam->lastRead);
        sam->lastRead = sam->newRead;
        sam->newRead = read;
    }
    fprintf(sam->fpointer, "%s\t", sam->newRead->QNAME);
    fprintf(sam->fpointer, "%d\t", sam->newRead->FLAG);
    fprintf(sam->fpointer, "%s\t", sam->newRead->RNAME);
    fprintf(sam->fpointer, "%d\t", sam->newRead->POS);
    fprintf(sam->fpointer, "%f\t", sam->newRead->MAPQ);
    fprintf(sam->fpointer, "%s\t", sam->newRead->CIGAR);
    fprintf(sam->fpointer, "%s\t", sam->newRead->RNEXT);
    fprintf(sam->fpointer, "%d\t", sam->newRead->PNEXT);
    fprintf(sam->fpointer, "%d\t", sam->newRead->TLEN);
    fprintf(sam->fpointer, "%d\t", sam->newRead->FLAG);
    fprintf(sam->fpointer, "%s\t", sam->newRead->SEQ);
    fprintf(sam->fpointer, "%s\t", sam->newRead->QUAL);
    fprintf(sam->fpointer, "\n");

}
