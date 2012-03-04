#define __USE_FILE_OFFSET64
#define _FILE_OFFSET_BITS 64
#define _LARGEFILE64_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include "btp.h"

BTP_CHUNK_HEADER* btp_load_chunk(BTP_FILE_HEADER* pBFH, uint64_t idx){
    // use the index to fine a 32768000 byte chunk
    // seek to it, then populate a header

    // allocate header, zero out start (but not 32MB of data)
    BTP_CHUNK_HEADER* pBCH = malloc(sizeof(BTP_CHUNK_HEADER));
    memset(pBCH, 0, sizeof(uint64_t)+4096+sizeof(uint32_t));

    // set index and load from position
    pBCH->idx = idx;
    fseeko64(pBFH->hFile, idx*32768000, SEEK_SET);
    pBCH->size = fread(pBCH->data, 1, 3276800, pBFH->hFile);

    // generate hash
    pBCH->hash = crc32(0, pBCH->data, pBCH->size);

    // return chunk
    return pBCH;
}

int btp_check_chunk(BTP_CHUNK_HEADER* pBCH){
    // check parts received
    // either here or before fill in "size" and "hash"
    // hash will come from a request
    // size will be either 32768000 or come from size of file if last chunk
    // i always feel self-conscious at this stage of a project
    // like if my code works it's because im lucky and not because it's well designed
    // this time it will be different though
    int i;
    uint32_t crc;
    for(i=0; i<4096; i++){
        if(pBCH->checklist[i]!=0xFF){
            // get packet resent
            // if at end of chunk, break loop
        }
    }
    // now run checksum
    crc = crc32(0, pBCH->data, pBCH->size);
    if(crc != pBCH->hash){
        // get it to resend in halves
        // maybe just throw an error for the test
        printf("chunk CRC failed\n");
    }
    return 0;
}

BTP_FILE_HEADER* btp_load_file(char* filename){
    // this loads a file, indexes it, then returns a handle
    FILE* hFile=NULL;
    uint64_t size=0;
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
    pBFH->nChunks=size/32768000+1;
    printf("Number of chunks: %lld\n", pBFH->nChunks);
    printf("Total size of chunks: %lld\n", pBFH->nChunks*bytesperchunk);
    return pBFH;
}
