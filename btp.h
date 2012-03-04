#define BTP_ID_EXT 0xFFFFFFFFFFFFFFFF
#define BTP_MSG_REQ_CHECKSUM 1
#define BTP_MSG_REQ_PACKET 2
#define BTP_MSG_SND_CHECKSUM 0x801

typedef struct _BTP_CHUNK_HEADER {
    uint64_t idx; // index of this chunk
    uint64_t size; // size of this chunk (should be 32768000 except last chunk)
    unsigned char checklist[4096]; // bitmap of each 1000-byte packet
    uint32_t hash; // hash for verification
    unsigned char data[32768000]; // contains the data
} BTP_CHUNK_HEADER;

typedef struct _BTP_FILE_HEADER {
    uint64_t size; // size of the file 64-bit
    FILE* hFile; // handle to the file
    uint64_t nChunks; // number of chunks in the file 64-bit
    uint64_t ib1; // index of the chunk loaded in the first buffer
    BTP_CHUNK_HEADER* pb1; // chunk header for the first buffer
    uint64_t ib2; // index of the chunk loaded in the second buffer
    BTP_CHUNK_HEADER* pb2; // chunk header for the second buffer
    uint64_t ibc; // index of the chunk loaded in the check buffer
    BTP_CHUNK_HEADER* pbc; // chunk header for the check buffer
} BTP_FILE_HEADER;

BTP_CHUNK_HEADER* btp_load_chunk(BTP_FILE_HEADER* pBFH, uint64_t idx);
BTP_FILE_HEADER* btp_load_file(char* filename);

uint32_t crc32(uint32_t crc, const void *buf, size_t size);
