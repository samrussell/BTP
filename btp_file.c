#include <stdlib.h>
#include <stdio.h>
#include "btp.h"

BTP_FILE_HEADER* btp_load_file(char* filename){
    // this loads a file, indexes it, then returns a handle
    FILE* hFile=NULL;
    long long size=0;

    hFile = fopen64(filename, "r");
    if(!hFile)return NULL;
    // get size
    long long seek=0;
    fseeko64(hFile, 0, SEEK_END);
    printf("Getting size\n");
    size=ftello64(hFile);
    printf("Got size\n");
    printf("size: %d\n", ftello64(hFile));
    printf("Printed\n");
    BTP_FILE_HEADER* pBFH = calloc(1, sizeof(BTP_FILE_HEADER));
    pBFH->size = size;
    pBFH->hFile=hFile;
    pBFH->nChunks=size/32768000 + 1;
    return pBFH;
}
