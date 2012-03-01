#define __USE_FILE_OFFSET64
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "btp.h"

BTP_FILE_HEADER* btp_load_file(char* filename){
    // this loads a file, indexes it, then returns a handle
    FILE* hFile=NULL;
    off_t size=0;
    uint32_t bytesperchunk=32768000;
    int res=0;

    hFile = fopen64(filename, "r");
    if(!hFile)return NULL;
    // get size
    res=fseek(hFile, 0, SEEK_END);
    if(res) printf("Error seeking: %s\n", strerror(errno));
    printf("Getting size\n");
    size=ftello64(hFile);
    printf("Got size\n");
    printf("size: %lld\n", size);
    printf("Printed\n");
    BTP_FILE_HEADER* pBFH = calloc(1, sizeof(BTP_FILE_HEADER));
    pBFH->size = size;
    pBFH->hFile=hFile;
    pBFH->nChunks=size/bytesperchunk+1;
    printf("Number of chunks: %lld\n", pBFH->nChunks);
    printf("  As signed 64 bit decimal: %Ld\n", pBFH->nChunks);
    printf("  As unsigned 64 bit hex: 0x%016LX\n", pBFH->nChunks);
    printf("  Low dword in hex: 0x%08X\n", pBFH->nChunks);
    printf("  High dword in hex: 0x%08X\n", pBFH->nChunks >> 32);
    printf("Total size of chunks: %lld\n", pBFH->nChunks*bytesperchunk);
    return pBFH;
}
