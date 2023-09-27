#pragma once

#include "terminal80x25.h"
#include "mm.h"

typedef struct tunnel_configuration_t {
    terminal_t terminal;
    bool debug;
    tunnel_memory_map_t *tmap;
} tunnel_configuration_t;

extern tunnel_configuration_t tunnel_config;