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
inline void convert_to_le(void *data, size_t size);  // Converts big endian to little endian

// inline void convert_to_le16(void *data);
// inline void convert_to_le32(void *data);

size_t fread_le(void *buffer, size_t size, size_t count, FILE *stream); // fread() but in little endian