#pragma once

#include <stdint.h>
#include <stdio.h>

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
  uint16_t id             ;
  uint32_t size           ;
  uint32_t reserved       ;
  uint32_t offset         ;
  uint32_t headersize     ;
  uint32_t width          ;
  uint32_t height         ;
  uint16_t colorplane     ;
  uint16_t bitperpixel    ;
  uint32_t compression    ;
  uint32_t pixelsize      ;
  uint32_t pixelmeter_x   ;
  uint32_t pixelmeter_y   ;
  uint32_t colorused      ;
  uint32_t importantcolor ;
} bmp_header_t;


typedef uint8_t bmp_pixel_t;

typedef struct bmp_t{
  bmp_header_t header;
  bmp_pixel_t  *pixel;
} bmp_t;


// Functions only support 24-bit RGB and 8-bit grayscale

void init_bmp(bmp_t *bmp);

void free_bmp_pixel(bmp_pixel_t *pixel);
void free_bmp(bmp_t *bmp);

int  fread_bmp_header(bmp_header_t *dst, FILE *fp);
int  fread_bmp_pixel(bmp_pixel_t **dst, bmp_header_t *header, FILE *fp);
int  fread_bmp_file(bmp_t *bmp, FILE *fp);

int  bmp_get_row_padding(int pixelsize, uint32_t width);

void print_bmp_header(bmp_header_t *header);
void print_bmp_pixel(bmp_header_t *header, bmp_pixel_t *pixel);
void print_bmp(bmp_t *bmp);














#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  #error "Big Endian system currently not support. TBD"
#else
  #error "Unexpected"
#endif