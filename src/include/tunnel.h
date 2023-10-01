#pragma once

#include "terminal80x25.h"
#include "mm.h"

#include "external/multiboot.h"

typedef struct tunnel_configuration_t {
    terminal_t terminal;
    bool debug;
    tunnel_memory_map_t *tmap;
    multiboot_info_t *multiboot;
} tunnel_configuration_t;

extern tunnel_configuration_t tunnel_config;