#include <drivers/block_device/def.h>

#include <stdlib.h>

RSB_ARRAY_IMPL_GEN(block_device_def, block_device_def);

rsb_array_block_device_def *__block_devices = NULL;

void __block_device_init() {
    __block_devices = RSBCreateArrayblock_device_def();
}
