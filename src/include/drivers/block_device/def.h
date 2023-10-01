#pragma once

#include <stddef.h>

typedef struct block_device_def {
    unsigned int size; // in kilobytes

    char naming[3]; // naming

    unsigned char data[256]; // internal data that block device implementations can use
    
    void (*write)(struct block_device_def *device, void *buffer, unsigned int sectors, unsigned int offset);
    void *(*read)(struct block_device_def *device, unsigned int sectors, unsigned int offset); // memory should be freed
} block_device_def;

#include <external/rsb_array_gen.h>

RSB_ARRAY_DEF_GEN(block_device_def, block_device_def);

extern rsb_array_block_device_def *__block_devices;

// extern block_device_def *__block_devices;
// extern unsigned int __block_devices_length;

void __block_device_init(); // allocates block device list