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

  goo_header_info_t goo_header_info = create_goo_header_info();
  if(!fread_goo_header_info(&goo_header_info, p_fin)){
    (void)PRINT_ERR("Failed to read file %s\n\n", argv[1]);
    return EIO;
  }

  print_goo_header_info(&goo_header_info);

  fclose(p_fin);
  return 0;
}
