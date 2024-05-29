#pragma once

#include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
// #include <string.h>

#include "fonts.h" // For colored printf

#define DEBUG

#ifdef DEBUG
  #define PRINT_DBG(format, ...) fprintf(stderr, BI_ORANGE "\nDEBUG: %s:%d:%s():\n" NOC format, \
                                  __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
  #define PRINT_DBG(format, ...)
#endif

#define PRINT_ERR(format, ...) fprintf(stderr, BI_ORANGE "\nDEBUG: %s:%d:%s():\n" NOC format, \
                                  __FILE__, __LINE__, __func__, ##__VA_ARGS__)

