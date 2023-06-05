#pragma once

#include <stdbool.h>
#include <stdint.h>

#pragma pack(push, 1)

#define MEMORY_X 156 * 2 * 1

typedef struct tunnel_memory_block_t {
    bool free;
    void *address;
    int have;
} tunnel_memory_block_t;
typedef struct tunnel_memory_map_t {
    tunnel_memory_block_t meta[MEMORY_X];
    char blockdata[MEMORY_X][256];
    uint32_t memsize_kb;
} tunnel_memory_map_t;
#pragma pack(pop)

void __mm_setup(tunnel_memory_map_t *map);
int __mm_findoffset(int blocks, tunnel_memory_map_t *map);