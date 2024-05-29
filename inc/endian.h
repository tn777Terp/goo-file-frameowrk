#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BITMASK_1 0x0000000F
#define BITMASK_2 0x000000F0
#define BITMASK_3 0x00000F00
#define BITMASK_4 0x0000F000
#define BITMASK_5 0x000F0000
#define BITMASK_6 0x00F00000
#define BITMASK_7 0x0F000000
#define BITMASK_8 0xF0000000


bool is_little_endian();
inline void swap_bytes(void *data, size_t size);  // Converts between Big Endian and Little Endian

size_t fread_be2le(void *buffer, size_t size, size_t count, FILE *stream);      // Wrapper to fread() . Reads big endian. Converts to little endian
size_t fwrite_le2be(const void *ptr, size_t size, size_t nmemb, FILE *stream);  // Wrapper to fwrite(). Convert little endian to big endian before writing