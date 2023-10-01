#pragma once

#include <stdbool.h>
#include <stdint.h>

#pragma pack(push, 1)

#define MEMORY_X 409200

#define MEMORY_BLOCK_SIZE 32

typedef struct tunnel_memory_block_t {
    uint8_t free;
    void *address;
    unsigned int have;
} tunnel_memory_block_t;
typedef struct tunnel_memory_statistics_t {
    uint32_t memsize_kb;
    uint32_t blocks_allocated;
    char reserved[4];
} tunnel_memory_statistics_t;
typedef struct tunnel_memory_map_t {
    tunnel_memory_block_t meta[MEMORY_X];
    char blockdata[MEMORY_X][MEMORY_BLOCK_SIZE];
    tunnel_memory_statistics_t statistics;
} tunnel_memory_map_t;
#pragma pack(pop)

void __mm_setup(tunnel_memory_map_t *map);
int __mm_findoffset(int blocks, tunnel_memory_map_t *map);