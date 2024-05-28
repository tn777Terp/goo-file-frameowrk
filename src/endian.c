#include <stdlib.h>
#include <errno.h>
#include "endian.h"
#include "commons.h"

bool is_little_endian(){
    uint16_t number = 0x1;
    char *numPtr = (char*)&number;
    return (numPtr[0] == 1);
}

/// @brief Coverts data of any size from big endian to little endian
/// @param data Pointer to data
/// @param size Size of datatype
inline void convert_to_le(void *data, size_t size){
  // Swap bytes based on datasize
  switch(size){
    case 1: break;  // No need for swapping for single byte data
    case 2: 
      *(uint16_t*)data = (*(uint16_t*)data  << 8) | (*(uint16_t*)data  >> 8);
      break;
    case 4:
      *(uint32_t*)data = ((*(uint32_t*)data << 8) & 0xFF00FF00U ) | ((*(uint32_t*)data >> 8) & 0x00FF00FFU );
      *(uint32_t*)data = (*(uint32_t*)data << 16) | (*(uint32_t*)data >> 16);
      break;
    case 8: 
      *(uint64_t*)data = ((*(uint64_t*)data <<  8) & 0xFF00FF00FF00FF00UL ) | ((*(uint64_t*)data >> 8)  & 0x00FF00FF00FF00FFUL );
      *(uint64_t*)data = ((*(uint64_t*)data << 16) & 0xFFFF0000FFFF0000UL ) | ((*(uint64_t*)data >> 16) & 0x0000FFFF0000FFFFUL );
      *(uint64_t*)data = (*(uint64_t*)data << 32) | (*(uint64_t*)data >> 32);
      break;
    default:  // Any non-standard data-size. Slow calculation
      // size_t i = 0;
      // size_t j = size - 1;
      // uint8_t temp;
      // while (i < j) {
      //   temp = ((uint8_t*)data)[i];
      //   ((uint8_t*)data)[i] = ((uint8_t*)data)[j];
      //   ((uint8_t*)data)[j] = temp;
      //   i++; j--;
      // }
      (void)PRINT_ERR("Only standard size supported: u8, u16, u32, u64\n");
      exit(ENODATA);
  }
}

/// @brief Wrapper for fread(). Converts result to little endian
/// @param buffer 
/// @param size 
/// @param count 
/// @param stream 
/// @return 
size_t fread_le(void *buffer, size_t size, size_t count, FILE *stream){
  size_t ndata = fread(buffer, size, count, stream);

  for(int i=0; i<count; i++){
    convert_to_le((buffer + size*i), size);
  }

  return ndata;
}