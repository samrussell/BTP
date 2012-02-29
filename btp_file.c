#include <stdlib.h>
#include <stdio.h>
#include "btp.h"

BTP_FILE_HEADER* btp_load_file(char* filename){
    // this loads a file, indexes it, then returns a handle
    FILE* hFile=NULL;
    long long size=0;

    hFile = fopen(filename, "r");
    if(!hFile) return NULL;
    // get size
    fseek(hFile, 0, SEEK_END);
    size=ftello64(hFile);
    printf("size: %L\n", size);
}
