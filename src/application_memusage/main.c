#include <tunnel.h>

#include <stdio.h>

#include <math.h>

void __application_memusage_init() {
    puts("current memory usage:\n");

    float allocated = (float)(tunnel_config.tmap->statistics.blocks_allocated * MEMORY_BLOCK_SIZE);
    float have = (float)(MEMORY_X * MEMORY_BLOCK_SIZE);

    printf(" - %d KB / %dKB (%d percent usage)\n", ceil(allocated / 1024.f), ceil(have / 1024.f), (int)(allocated / have * 100.f)); 
    printf(" - %d blocks allocated\n", tunnel_config.tmap->statistics.blocks_allocated); 
}