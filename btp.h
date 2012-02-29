#define BTP_ID_EXT 0xFFFFFFFFFFFFFFFF
#define BTP_MSG_REQ_CHECKSUM 1
#define BTP_MSG_REQ_PACKET 2
#define BTP_MSG_SND_CHECKSUM 0x801

typedef struct _BTP_CHUNK_HEADER {
    unsigned char checklist[4096];
    unsigned char hash[8];
    unsigned char data[32768000];
} BTP_CHUNK_HEADER;

typedef struct _BTP_FILE_HEADER {
    long long size; // size of the file 64-bit
    FILE* hFile; // handle to the file
    long long nChunks; // number of chunks in the file 64-bit
    long long ib1; // index of the chunk loaded in the first buffer
    BTP_CHUNK_HEADER* pb1; // chunk header for the first buffer
    long long ib2; // index of the chunk loaded in the second buffer
    BTP_CHUNK_HEADER* pb2; // chunk header for the second buffer
    long long ibc; // index of the chunk loaded in the check buffer
    BTP_CHUNK_HEADER* pbc; // chunk header for the check buffer
} BTP_FILE_HEADER;
