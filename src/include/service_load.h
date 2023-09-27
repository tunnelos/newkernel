#pragma once

#include <stdbool.h>

void __service_startInitService(void (*init_function)(), const char *name, bool transparent);