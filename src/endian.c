#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "endian.h"
#include "commons.h"  // For error-printing functions


/// @brief Checks if system stores data as little endian or big endian
/// @return 1 = Little Endian  |  0 = big Endian
bool is_little_endian(){
  uint16_t num = 0x01;                // Checks how the system stores the value b00000000_00000001
  uint8_t *pnum = (uint8_t*)&num;     // <--lower address--       pnum[0]  pnum[1]       --higher address-->
  return (pnum[0] == 1);              // Big Endian    stores as: 00000000_00000001     
}                                     // Little Endian stores as: 00000001_00000000       

/// @brief Coverts data of any size from big endian to little endian
/// @param data Pointer to data
/// @param size Size of datatype
inline void swap_bytes(void *data, size_t size){
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


/// @brief Wrapper for fread(). Reads big endian -> converts to little endian
/// @param buffer Pointer to where to store the read data
/// @param size   Size of data type
/// @param count  Number of elements to read
/// @param stream Pointer to file stream
/// @return 
size_t fread_be2le(void *buffer, size_t size, size_t count, FILE *stream){
  size_t ndata = fread(buffer, size, count, stream);

  for(int i=0; i<count; i++){
    swap_bytes( (uint8_t*)buffer + size*i, size);
  }

  return ndata;
}


/// @brief Wrapper for fwrite(). Converts little endian to big endian before writing.
/// @param ptr Pointer to data to be written
/// @param size Size of data type
/// @param nmemb Number of elements to write
/// @param stream Pointer to file stream
/// @return Number of elements succesfully written
size_t fwrite_le2be(const void *ptr, size_t size, size_t nmemb, FILE *stream){
  size_t total_bytes = size*nmemb;
  void   *buffer = (void*)malloc(total_bytes);
  memcpy(buffer, ptr, total_bytes);

  for(int i=0; i<nmemb; i++){
    swap_bytes( (uint8_t*)buffer + size*i, size);
  }
  size_t ndata = fwrite(buffer, size, nmemb, stream);

  free(buffer);
  return ndata;
}
