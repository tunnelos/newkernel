#include "../include/mm.h"

#include <stddef.h>

#include "../include/tunnel.h"
#include "../include/math.h"
#include "../include/serial.h"
#include "../include/stdlib.h"

int __mm_pointer = 0;
int __mm_index = 0;

void __mm_setup(tunnel_memory_map_t *map) {
    int m = MEMORY_X;
    int i = 0;
    while(i < m) {
        //__serial_write_fmt("CPU %d -> tos > Clean %d.\n", __tools_get_cpu() - 1, i);
        map->meta[i].address = &map->blockdata[i];
        map->meta[i].have = 0;
        map->meta[i].free = true;
        i++;
    }
    return;
}

int __mm_findoffset(int blocks, tunnel_memory_map_t *map) {
    int p = 0;
    int o = 0;
    goto repeat;
    repeat:
        if(o >= MEMORY_X) return -1;
        // find free block offset
        while(!map->meta[o].free) o++;
        if(o >= MEMORY_X) return -1;
        //f ind free blocks on this offset
        while(map->meta[o + p].free) p++;
        if(blocks <= p) return o;
        else {
            if(p == 0) p++;
            o += p;
            p = 0;
            goto repeat;
        }
    return -1;
}

void *malloc(size_t size) {
    if(size <= 0) return 0;
    int state[6];
    state[4] = (int)(ceil((float)size / 256.f));
    if(state[4] == 0) state[4] = 1;
    // state[4] - blocks to allocate
    // state[0] - block offset
    // __mm_index - blocks allocated
    state[3] = 0;
    state[2] = 0;
    state[1] = 0;
    state[0] = __mm_findoffset(state[4], tunnel_config.tmap);
    if(state[0] < 0) return NULL;
    __mm_index += state[4];
    tunnel_config.tmap->meta[state[0]].have = 0;
    tunnel_config.tmap->meta[state[0]].free = false;
    while(state[1] < state[4]) {
        tunnel_config.tmap->meta[state[1] + state[0]].free = false;
        tunnel_config.tmap->meta[state[0]].have++;
        state[1]++;
    }
    //__serial_write_fmt("CPU %d -> tos > Allocated %d blocks of memory on address %l %X (requested %d bytes)\r\n", __tools_get_cpu() - 1, state[4], (uint64_t)tunnelos_sysinfo.mm->meta[state[0]].address, size);
    __serial_write_fmt("Allocated %d blocks of memory of address ", state[4]);
    __serial_write_fmt("%X (requested ", (uint32_t)(tunnel_config.tmap->meta[state[0]].address));
    __serial_write_fmt("%d bytes)\r\n", size);

    memset(tunnel_config.tmap->meta[state[0]].address, 0, size);
    return tunnel_config.tmap->meta[state[0]].address;
    
    return NULL;
}

void *calloc(int count, size_t size) {
    void *ret = malloc(size * count);
    memset(ret, 0, size * count);
    return ret;
}

tunnel_memory_block_t __mm_get_blockinformation(void *address) {
    uint32_t adr = (uint32_t)address;
    uint32_t sadr = (uint32_t)(&tunnel_config.tmap->blockdata);
    uint32_t index = adr - sadr;
    uint32_t blk = floor((float)index / 256.f);
    tunnel_memory_block_t bl;
    bl.address = tunnel_config.tmap->meta[blk].address;
    bl.free = tunnel_config.tmap->meta[blk].free;
    bl.have = tunnel_config.tmap->meta[blk].have;
    return bl;
}

void *realloc(void *address, size_t size) {
    void *new_addr = malloc(size);
    void *old = address;
    int old_size = __mm_get_blockinformation(address).have;
    if(old_size == 0) old_size = 1;
    old_size *= 256;
    int i = 0;
    char *data_new = (char *)new_addr;
    char *data_old = (char *)old;
    while(i < old_size) {
        data_new[i] = data_old[i];
        i++;
    }
    free(address);
    __serial_write_fmt("Reallocated %d blocks\r\n", old_size / 256);
    return new_addr;
}

void free(void *address) {
    uint32_t adr = (uint32_t)address;
    uint32_t sadr = (uint32_t)(&tunnel_config.tmap->blockdata);
    uint32_t index = adr - sadr;
    int blk = floor((float)index / 256.f);
    int blks = 0;
    if(blk >= MEMORY_X) return;
    if(blk < 0) return;
    if(tunnel_config.tmap->meta[blk].free) return;
    int i = 0;
    blks = tunnel_config.tmap->meta[blk].have;
    if(blks == 0) blks = 1;
    while(i < blks) {
        tunnel_config.tmap->meta[blk + i].free = true;
        memset(tunnel_config.tmap->meta[blk + i].address, 0, 256);
        i++;
    }
    __mm_index -= blks;
    __serial_write_fmt("Freed %d blocks\r\n", blks);
    return;
}
