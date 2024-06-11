#pragma once

#include <stdint.h>
#include <stdio.h>

#include "bmp_config.h"

#define BMP_HEADER_OFFSET     54
#define COLORTABLE_OFFSET_U8  (256*4)

#define BYTE_OFFSET_RED 0
#define BYTE_OFFSET_GRN 1
#define BYTE_OFFSET_BLU 2

#define PIXEL_GRAY_RATIO_RED 0.299f
#define PIXEL_GRAY_RATIO_GRN 0.587f
#define PIXEL_GRAY_RATIO_BLU 0.114f

// Code only support little endian system
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#pragma packed
typedef struct bmp_header_t{
  uint16_t id             ;   // "BM"
  uint32_t size           ;   // Total file size in bytes
  uint32_t reserved       ;   // unused
  uint32_t offset         ;   // Offset to where pixel data starts
  uint32_t headersize     ;   // Size of header (40 bytes most of the times)
  uint32_t width          ;   // Number of pixels (width)
  uint32_t height         ;   // Number of pixels (height)
  uint16_t colorplane     ;   // Number of color plane (usually =1)
  uint16_t bitperpixel    ;   // Number of bits each pixel takes up
  uint32_t compression    ;   // 0 = NONE | 1 = 8-bit RLE encoding | 2 = 4-bit RLE Encoding
  uint32_t pixelsize      ;   // Total image size in bytes including padding (can set to 0 if compression=0)
  uint32_t pixelmeter_x   ;   // 
  uint32_t pixelmeter_y   ;   // 
  uint32_t colorused      ;   // 
  uint32_t importantcolor ;   // 
} bmp_header_t;


typedef uint8_t bmp_pixel_t;

typedef struct bmp_t{
  bmp_header_t header;
  bmp_pixel_t  *pixel;
} bmp_t;


// Functions only support 24-bit RGB and 8-bit grayscale

void init_bmp(bmp_t *bmp, uint32_t width, uint32_t height);
void init_bmp_grayscale(bmp_t *bmp, uint32_t width, uint32_t height);

void free_bmp_pixel(bmp_pixel_t *pixel);
void free_bmp(bmp_t *bmp);

int  fread_bmp_header(bmp_header_t *dst, FILE *fp);
int  fread_bmp_pixel(bmp_pixel_t **dst, bmp_header_t *header, FILE *fp);
int  fread_bmp_file(bmp_t *bmp, FILE *fp);

int  fwrite_bmp_header(bmp_header_t *src, FILE *fp);
int  fwrite_bmp_pixel(bmp_pixel_t **src, bmp_header_t *header, FILE *fp);
int  fwrite_bmp_file(bmp_t *bmp, FILE *fp);

int  bmp_get_row_padding(int pixelsize, uint32_t width);

void print_bmp_header(bmp_header_t *header);
void print_bmp_pixel(bmp_header_t *header, bmp_pixel_t *pixel);
void print_bmp(bmp_t *bmp);














#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  #error "Big Endian system currently not support. TBD"
#else
  #error "Unexpected"
#endif