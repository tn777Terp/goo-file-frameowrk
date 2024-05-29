#pragma once

#include <stdio.h>
#include "goo_struct.h"

// Code only support little endian system
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define GOO_MAGIC_TAG     0x07000000444C5000ULL   // Indicates the the beginning of a .goo file

void  init_goo(goo_t *goo);                                               // Initialize all value to 0
void  init_goo_header_info(goo_header_info_t *goo_header_info);           // Initialize all value to 0

void  free_goo_layer_content(goo_layer_content_t *content, int nlayers);  // 
void  free_goo(goo_t *goo);                                               //

int   fread_goo_header_info(goo_header_info_t *dst, FILE *fp);            // Reads header info of .goo file
int   fread_goo_layer_definition(goo_layer_definition_t *dst, FILE *fp);  // Read layer definition of .goo file
int   fread_goo_layer_content(goo_layer_content_t **dst, goo_header_info_t *header, FILE *fp);
int   fread_goo_file(goo_t *dst, FILE *fp);                               // Read all content of .goo file

void  print_img_u16(uint16_t *data, uint16_t width, uint16_t height);     // Prints image given u16 pixel datas

void  print_goo_header_info(goo_header_info_t *header);                   // Prints out all .goo header info
void  print_goo_layer_definition(goo_layer_definition_t *definition);     // Print layer definition
void  print_goo_layer_content(goo_layer_content_t *content);              // Print layer content
void  print_goo(goo_t *goo, int max_layer);                               // Print all .goo info














#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  #error "Big Endian system currently not support. TBD"
#else
  #error "Unexpected"
#endif

