#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "commons.h"
#include "goo.h"



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

  goo_t goo; init_goo(&goo);
  

/*** EXAMPLE of how to read entire file and print out its details***/
  if(!fread_goo_file(&goo, p_fin) ){
    (void)PRINT_ERR("Failed to read header info for %s\n\n", argv[1]);
    return EIO;
  }
  print_goo(&goo, 2); // Prints at most info for 2 layers. This prevents too much text on screen.
  free_goo(&goo);


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
  // print_goo_layer_content(&goo_layer_contents[1]); putchar('\n');
  //
  // free_goo_layer_content(goo_layer_contents, goo_header_info.total_layers);


  fclose(p_fin);
  return 0;
}
