#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "commons.h"
#include "goo.h"
#include "bmp.h"



int main(int argc, char ** argv){

  if(argc != 2){
    (void)PRINT_ERR("\nUsage: %s <target.lst>\n\n", argv[0]);
    return EINVAL;
  }

  FILE *p_fin = fopen(argv[1], "rb");
  if(p_fin == NULL){
    (void)PRINT_ERR("Failed to open %s\n\n", argv[1]);
    return ENOENT;
  }


  printf("System Endianess: ");
  if(is_little_endian()){
    printf("Little Endian\n\n");
  } else{
    printf("Big Endian\n\n");
    (void)PRINT_ERR("Code currently only support Little Endian systems %s\n\n", argv[1]);
    return ENOEXEC;
  }




/*** EXAMPLE of how to read entire bmp file and rewrite the content***/
  bmp_t bmp; init_bmp(&bmp);
  if(!fread_bmp_file(&bmp, p_fin) ){
    (void)PRINT_ERR("Failed to read bmp file: %s\n\n", argv[1]);
    return EIO;
  }
  print_bmp(&bmp);
  //free_bmp(&bmp);

  FILE *p_fout = fopen("test_out.bmp", "wb");
  if(!fwrite_bmp_file(&bmp, p_fout)){
    (void)PRINT_ERR("Failed to write bmp file: %s\n\n", "test_out.bmp");
    return EIO;
  }
  fclose(p_fout);

  free_bmp(&bmp);

/*** EXAMPLE of how to read the header and pixel data separately ***/
  // bmp_header_t bmp_header;
  // bmp_pixel_t *bmp_pixels;
  // 
  // if(!fread_bmp_header(&bmp_header, p_fin) ){
  //   (void)PRINT_ERR("Failed to read header info for %s\n\n", argv[1]);
  //   return EIO;
  // }
  // print_bmp_header(&bmp_header);
  //
  // if(!fread_bmp_pixel(&bmp_pixels, &bmp_header, p_fin)){
  //   (void)PRINT_ERR("Failed to read pixel info for %s\n\n", argv[1]);
  //   return EIO;
  // }
  // print_bmp_pixel(&bmp_header, bmp_pixels);
  // 
  // free_bmp_pixel(bmp_pixels);




/*** EXAMPLE of how to read entire file and print out its details***/
  // goo_t goo; init_goo(&goo);
  // if(!fread_goo_file(&goo, p_fin) ){
  //   (void)PRINT_ERR("Failed to read header info for %s\n\n", argv[1]);
  //   return EIO;
  // }
  // print_goo(&goo, 2); // Prints at most info for 2 layers. This prevents too much text on screen.
  // free_goo(&goo);


/*** EXAMPLE of how to read Header Info and Layer Content Separately ***/
  // goo_header_info_t   goo_header_info;
  // goo_layer_content_t *goo_layer_contents;
  // // Reading Header Info example
  // if(!fread_goo_header_info(&goo_header_info, p_fin)){
  //   (void)PRINT_ERR("Failed to read header info for %s\n\n", argv[1]);
  //   return EIO;
  // }
  // print_goo_header_info(&goo_header_info);  putchar('\n');
  //
  // // Reading Layer Content example
  // if(!fread_goo_layer_content(&goo_layer_contents, &goo_header_info, p_fin)){
  //   (void)PRINT_ERR("Failed to read content info for %s\n\n", argv[1]);
  //   return EIO;
  // }
  // print_goo_layer_content(&goo_layer_contents[0]); putchar('\n');
  // // print_goo_layer_content(&goo_layer_contents[1]); putchar('\n');
  //
  // free_goo_layer_content(goo_layer_contents, goo_header_info.total_layers);


  fclose(p_fin);
  return 0;
}
