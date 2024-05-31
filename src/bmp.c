#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "bmp.h"
#include "endian.h"
#include "commons.h" // for error printing

void init_bmp(bmp_t *bmp){
  memset(bmp, 0, sizeof(bmp_t));
}


void free_bmp_pixel(bmp_pixel_t *pixel){
  free(pixel);
}
void free_bmp(bmp_t *bmp){
  free_bmp_pixel(bmp->pixel);
}

int fread_bmp_header(bmp_header_t *dst, FILE *fp){
  if(fseek(fp, 0, SEEK_SET)) return 0;
  if(!fread( &dst->id               , sizeof(uint16_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->size             , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->reserved         , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->offset           , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->headersize       , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->width            , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->height           , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->colorplane       , sizeof(uint16_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->bitperpixel      , sizeof(uint16_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->compression      , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->pixelsize        , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->pixelmeter_x     , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->pixelmeter_y     , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->colorused        , sizeof(uint32_t),  1, fp) ) return 0;  // 
  if(!fread( &dst->importantcolor   , sizeof(uint32_t),  1, fp) ) return 0;  // 
}


/// @brief Read and allocate memory for pixels
/// @param dst    Pointer to where to store data
/// @param header Poniter to bmp header info. Needed to get size of image
/// @param fp 
/// @return 
int fread_bmp_pixel(bmp_pixel_t **dst, bmp_header_t *header, FILE *fp){
  uint32_t pixel_nbyte = header->bitperpixel / 8;   // Convert size from bits to bytes
  int      padding = bmp_get_row_padding(pixel_nbyte, header->width);
  uint8_t *blackhole = (uint8_t*)malloc(padding); // For discarding fread() padding data

  *dst = (bmp_pixel_t*)malloc(header->width * header->height * pixel_nbyte);
  if(*dst == NULL) return 0;
  
  // Read pixel data only. Ignores padding
  if(fseek(fp, header->offset, SEEK_SET)) return 0;
  for(uint32_t y=0; y < header->height; y++){
    for(uint32_t x=0; x < header->width; x++){
      size_t pixel_offset = (x + y*header->width)*pixel_nbyte;
      if(!fread( ((uint8_t*)(*dst) + pixel_offset), pixel_nbyte, 1, fp) ) 
      return 0; 
    }
    (void)fread(blackhole, padding, 1, fp);
  }

  free(blackhole);
  return 1;
}


/// @brief Reads all content of a .bmp file
/// @param bmp Pointer to bmp object
/// @param fp 
/// @return 1 = Success  |  0 = Failed
int fread_bmp_file(bmp_t *bmp, FILE *fp){
  if(!fread_bmp_header(&(*bmp).header, fp) )               return 0;
  if(!fread_bmp_pixel(&(*bmp).pixel, &(*bmp).header, fp) ) return 0;
  return 1;
}


int  fwrite_bmp_header(bmp_header_t *src, FILE *fp){
  if(fseek(fp, 0, SEEK_SET)) return 0;
  if(!fwrite(&src->id            ,  sizeof(uint16_t),  1,  fp) )  return 0;
  if(!fwrite(&src->size          ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->reserved      ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->offset        ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->headersize    ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->width         ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->height        ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->colorplane    ,  sizeof(uint16_t),  1,  fp) )  return 0;
  if(!fwrite(&src->bitperpixel   ,  sizeof(uint16_t),  1,  fp) )  return 0;
  if(!fwrite(&src->compression   ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->pixelsize     ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->pixelmeter_x  ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->pixelmeter_y  ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->colorused     ,  sizeof(uint32_t),  1,  fp) )  return 0;
  if(!fwrite(&src->importantcolor,  sizeof(uint32_t),  1,  fp) )  return 0;
  return 1;
}


/// @brief Writes color table. Only support 8-bit grayscale for now
/// @param header Pointer to bmp header
/// @param fp Pointer to file stream
/// @return Write: 1 = Success | 0 = Fail
int fwrite_bmp_colortable(bmp_header_t *header, FILE *fp){
  uint32_t pixel_nbyte = header->bitperpixel / 8;   // Convert size from bits to bytes
  // int padding = bmp_get_row_padding(pixel_nbyte, header->width);

  if(header->bitperpixel > 8 ) return 1;  // Only pixel-size 8-bit of less requires lookup table

  // Only support 8-bit grayscale for now.
  // LUT value is gray gradient. Can be modified for other colors
  switch(header->bitperpixel){
    // Write 00,00,00,00...to... 000,255,255,255 (for little-eendian system)
    case 8:
      for(uint32_t i=0; i<256; i++){
        // uint32_t lut_value = (i<<24) | (i<<16) | (i<<8) & 0xFFFFFF00;
        uint32_t lut_value = (0x00) | (i<<16) | (i<<8) | (i);
        if(!fwrite(&lut_value, 4, 1, fp))  return 0;
      } return 1;
    default:
      (void)PRINT_WARNING("Only supports 8-bits grayscale colortable for now.\n");
      return 0;
  }
  return 1;
}

int fwrite_bmp_pixel(bmp_pixel_t **src, bmp_header_t *header, FILE *fp){
  uint32_t pixel_nbyte = header->bitperpixel / 8;   // Convert size from bits to bytes
  int      padding = bmp_get_row_padding(pixel_nbyte, header->width);

  for(uint32_t y=0; y < header->height && y < BMP_MAX_PIXELY; y++){
    for(uint32_t x=0; x < header->width && x < BMP_MAX_PIXELX; x++){
      size_t pixel_offset = (x + y*header->width)*pixel_nbyte;
      if(!fwrite( ((uint8_t*)(*src) + pixel_offset), pixel_nbyte, 1, fp) ) 
      return 0; 
    }
    (void)fwrite((uint8_t[]){0,0,0}, padding, 1, fp); 
  }
  return 1;
}


int fwrite_bmp_file(bmp_t *bmp, FILE *fp){
  static const size_t BMP_HEADER_OFFSET    = 54;
  static const size_t COLORTABLE_OFFSET_U8 = 256*4;

  // Calculate pixel offsets if grayscale
  if((*bmp).header.bitperpixel == 24){
    (*bmp).header.offset = BMP_HEADER_OFFSET;
  } else if((*bmp).header.bitperpixel == 8){
    (*bmp).header.offset = BMP_HEADER_OFFSET + COLORTABLE_OFFSET_U8;
  } else {
    (void)PRINT_WARNING("Only supports 24-bit and 8-bits bit-per-pixel for now.\n");
    return 0;
  }

  if(!fwrite_bmp_header(&(*bmp).header, fp)              )  return 0;     
  if(!fwrite_bmp_colortable(&(*bmp).header, fp)          )  return 0;     
  if(!fwrite_bmp_pixel(&(*bmp).pixel, &(*bmp).header, fp))  return 0;   
  return 1;
}



/// @brief Get the number of padding required for each row in bytes.
///        Rows must be divisible by 4 bytes rounded up.
/// @param bytesperpixel Size of each pixels in bytes
/// @param width         Width of image 
/// @return Returns padding size at the end of each rows in bytes
int  bmp_get_row_padding(int bytesperpixel, uint32_t width){
  int pad_nbytes = 4 - ((width * bytesperpixel) % 4);
  if(pad_nbytes == 4) pad_nbytes = 0; // For cases where rows are perfectly divided by 4.

  return pad_nbytes;
}


void print_bmp_header(bmp_header_t *header){
  printf("id             : ");   fwrite(&header->id, sizeof(char), 2, stdout);  putchar('\n'); // uint16_t
  printf("size           : ");   printf("%u" , header->size          );         putchar('\n'); // uint32_t
  printf("reserved       : ");   printf("%u" , header->reserved      );         putchar('\n'); // uint32_t
  printf("offset         : ");   printf("%u" , header->offset        );         putchar('\n'); // uint32_t
  printf("headersize     : ");   printf("%u" , header->headersize    );         putchar('\n'); // uint32_t
  printf("width          : ");   printf("%u" , header->width         );         putchar('\n'); // uint32_t
  printf("height         : ");   printf("%u" , header->height        );         putchar('\n'); // uint32_t
  printf("colorplane     : ");   printf("%hu", header->colorplane    );         putchar('\n'); // uint16_t
  printf("bitperpixel    : ");   printf("%hu", header->bitperpixel   );         putchar('\n'); // uint16_t
  printf("compression    : ");   printf("%u" , header->compression   );         putchar('\n'); // uint32_t
  printf("pixelsize      : ");   printf("%u" , header->pixelsize     );         putchar('\n'); // uint32_t
  printf("pixelmeter_x   : ");   printf("%u" , header->pixelmeter_x  );         putchar('\n'); // uint32_t
  printf("pixelmeter_y   : ");   printf("%u" , header->pixelmeter_y  );         putchar('\n'); // uint32_t
  printf("colorused      : ");   printf("%u" , header->colorused     );         putchar('\n'); // uint32_t
  printf("importantcolor : ");   printf("%u" , header->importantcolor);         putchar('\n'); // uint32_t
}


void print_bmp_pixel(bmp_header_t *header, bmp_pixel_t *pixel){
  uint32_t pixel_nbyte = header->bitperpixel / 8;   // Convert size from bits to bytes
  uint8_t gray;

  for(uint32_t y=0; y < header->height; y++){
    for(uint32_t x=0; x < header->width; x++){
      size_t pixel_offset = (x + y*header->width)*pixel_nbyte;

      if(pixel_nbyte == 1){
        gray = *(pixel + pixel_offset);
      } 
      else if(pixel_nbyte == 3){
        gray = ( (float)*(pixel + pixel_offset + BYTE_OFFSET_RED) * PIXEL_GRAY_RATIO_RED) + 
               ( (float)*(pixel + pixel_offset + BYTE_OFFSET_GRN) * PIXEL_GRAY_RATIO_GRN) + 
               ( (float)*(pixel + pixel_offset + BYTE_OFFSET_BLU) * PIXEL_GRAY_RATIO_BLU) ;
      }

      if     (gray >= (255/12)*11) printf("$$");
      else if(gray >= (255/12)*10) printf("MM");
      else if(gray >= (255/12)* 9) printf("@@");
      else if(gray >= (255/12)* 8) printf("%%%%");
      else if(gray >= (255/12)* 7) printf("##");
      else if(gray >= (255/12)* 6) printf("**");
      else if(gray >= (255/12)* 5) printf("++");
      else if(gray >= (255/12)* 4) printf("==");
      else if(gray >= (255/12)* 2) printf("--");
      else if(gray >= (255/12)* 2) printf("::");
      else if(gray >= (255/12)* 1) printf("..");
      else if(gray >= (255/12)* 0) printf("  ");
      else printf("E"); // unexpected value error
    } putchar('\n');
  }
}


void print_bmp(bmp_t *bmp){
  print_bmp_header(&(*bmp).header);
  print_bmp_pixel(&(*bmp).header, (*bmp).pixel);
}


