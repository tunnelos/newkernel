#pragma once

#include <stdint.h>

unsigned int __tools_get_cpu();

void wait(uint32_t ms);

char __tools_getDriveLetter(int id);