#pragma once

#include "terminal80x25.h"

typedef struct tunnel_configuration_t {
    terminal_t terminal;
} tunnel_configuration_t;

extern tunnel_configuration_t tunnel_config;