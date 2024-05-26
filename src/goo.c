#include "goo.h"
#include "endian.h"

/// @brief Initialize all fields to 0
/// @param header 
void init_goo_header_info(goo_header_info_t *header){
  memset(header, 0, sizeof(goo_header_info_t));
}


/// @brief  Creates and return a zero-initialized goo_header_info_t
/// @return Returns an zero-initialized goo_header_info_t
goo_header_info_t create_goo_header_info(){
  goo_header_info_t header;
  init_goo_header_info(&header);
  return header;
}


/// @brief     Reads in a *.goo file and parse the header info
/// @param dst Pointer to where the data will be stored
/// @param fp  Pointer to file stream
/// @return    1=sucess | 0=error
int fread_goo_header_info(goo_header_info_t *dst, FILE *fp) {
  fseek(fp, 0, SEEK_SET);

  if(!fread_le( dst->version                        , sizeof(char    ),       4, fp) ) return 0;  // char          [ 4]
  if(!fread_le( dst->magic_tag                      , sizeof(char    ),       8, fp) ) return 0;  // char          [ 8]
  if(!fread_le( dst->software_info                  , sizeof(char    ),      32, fp) ) return 0;  // char          [32]
  if(!fread_le( dst->software_version               , sizeof(char    ),      24, fp) ) return 0;  // char          [24]
  if(!fread_le( dst->file_time                      , sizeof(char    ),      24, fp) ) return 0;  // char          [24]
  if(!fread_le( dst->printer_name                   , sizeof(char    ),      32, fp) ) return 0;  // char          [32]
  if(!fread_le( dst->printer_type                   , sizeof(char    ),      32, fp) ) return 0;  // char          [32]
  if(!fread_le( dst->profile_name                   , sizeof(char    ),      32, fp) ) return 0;  // char          [32]
  if(!fread_le(&dst->anti_aliasing_level            , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t        
  if(!fread_le(&dst->grey_level                     , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t        
  if(!fread_le(&dst->blur_level                     , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t        
  if(!fread_le( dst->small_preview_image_data       , sizeof(uint16_t), 116*116, fp) ) return 0;  // uint16_t [116*116]
  if(!fread_le( dst->delimiter1                     , sizeof(char    ),       2, fp) ) return 0;  // char          [ 2]
  if(!fread_le( dst->big_preview_image_data         , sizeof(uint16_t), 290*290, fp) ) return 0;  // uint16_t [290*290]
  if(!fread_le( dst->delimiter2                     , sizeof(char    ),       2, fp) ) return 0;  // char          [ 2]
  if(!fread_le(&dst->total_layers                   , sizeof(int32_t ),       1, fp) ) return 0;  // int32_t         
  if(!fread_le(&dst->x_resolution                   , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_le(&dst->y_resolution                   , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_le(&dst->x_mirror                       , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_le(&dst->y_mirror                       , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_le(&dst->x_size_of_platform             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->y_size_of_platform             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->z_size_of_platform             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->layer_thickness                , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->common_exposure_time           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->exposure_delay_mode            , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_le(&dst->turn_off_time                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_before_lift_time        , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_after_lift_time         , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_after_retract_time      , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->before_lift_time               , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->after_lift_time                , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->after_retract_time             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_exposure_time           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_layers                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_lift_distance           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_lift_speed              , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->lift_distance                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->lift_speed                     , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_retract_distance        , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_retract_speed           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->retract_distance               , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->retract_speed                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_second_lift_distance    , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_second_lift_speed       , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->second_lift_distance           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->second_lift_speed              , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_second_retract_distance , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_second_retract_speed    , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->second_retract_distance        , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->second_retract_speed           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->bottom_light_pwm               , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_le(&dst->light_pwm                      , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_le(&dst->advance_mode                   , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_le(&dst->printing_time                  , sizeof(int32_t ),       1, fp) ) return 0;  // int32_t         
  if(!fread_le(&dst->total_volume                   , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->total_weight                   , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le(&dst->total_price                    , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_le( dst->price_unit                     , sizeof(char    ),       8, fp) ) return 0;  // char         [ 8]           
  if(!fread_le(&dst->offset_of_layer_content        , sizeof(int32_t ),       1, fp) ) return 0;  // int32_t           
  if(!fread_le(&dst->gray_scale_level               , sizeof(bool    ),       1, fp) ) return 0;  // bool              
  if(!fread_le(&dst->transition_layer               , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t    
  return 1;
}           


/// @brief Prints image given u16 pixel datas
/// @param data   Preview image data from *.goo file
/// @param width  Width of preview image
/// @param height Height of preview image
void print_img_u16(uint16_t *data, uint16_t width, uint16_t height){
  uint16_t pixel_value = 0;
  uint8_t  r, g, b, grey;
  putchar('\n');

  for(unsigned h=0; h<height; h++){
    for(unsigned w=0; w<width; w++){
      r = (data[w+(h*height)] & 0xF800) >> 11;
      g = (data[w+(h*height)] & 0x07E0) >>  5;
      b = (data[w+(h*height)] & 0x001F);
      grey = (uint8_t)(0.299*r + 0.587*g + 0.114*b);  // max value = 71.8140

      if     (grey > 65) printf("$$");   // out of range error 
      else if(grey > 59) printf("MM");
      else if(grey > 57) printf("@@");
      else if(grey > 47) printf("%%%%");
      else if(grey > 41) printf("##");
      else if(grey > 35) printf("**");
      else if(grey > 29) printf("++");
      else if(grey > 23) printf("==");
      else if(grey > 17) printf("--");
      else if(grey > 11) printf("::");
      else if(grey >  5) printf("..");
      else if(grey >  0) printf("  ");
      else printf("E");                 // unexpected value error
    }
    putchar('\n');
  }
}


/// @brief Prints out all paramaters from a *.goo header
/// @param header Header info read from the *.goo file 
void print_goo_header_info(goo_header_info_t *header){
  // printf("small_preview_image_data  : ");   print_img_u16(header->small_preview_image_data, 116, 116);  putchar('\n');
  // printf("big_preview_image_data    : ");   print_img_u16(header->big_preview_image_data  , 290, 290);  putchar('\n');

  printf("version                   : ");   fwrite(header->version         , sizeof(char),       4, stdout);    putchar('\n');
  printf("magic_tag                 : ");   fwrite(header->magic_tag       , sizeof(char),       8, stdout);    putchar('\n');
  printf("software_info             : ");   fwrite(header->software_info   , sizeof(char),      32, stdout);    putchar('\n');
  printf("software_version          : ");   fwrite(header->software_version, sizeof(char),      24, stdout);    putchar('\n');
  printf("file_time                 : ");   fwrite(header->file_time       , sizeof(char),      24, stdout);    putchar('\n');
  printf("printer_name              : ");   fwrite(header->printer_name    , sizeof(char),      32, stdout);    putchar('\n');
  printf("printer_type              : ");   fwrite(header->printer_type    , sizeof(char),      32, stdout);    putchar('\n');
  printf("profile_name              : ");   fwrite(header->profile_name    , sizeof(char),      32, stdout);    putchar('\n');
  printf("anti_aliasing_level       : ");   printf("%hi" , header->anti_aliasing_level            );            putchar('\n');
  printf("grey_level                : ");   printf("%hi" , header->grey_level                     );            putchar('\n');
  printf("blur_level                : ");   printf("%hi" , header->blur_level                     );            putchar('\n');
  // printf("small_preview_image_data  : ");   print_img_u16(header->small_preview_image_data, 116, 116);  putchar('\n');
  printf("small_preview_image_data  : ");   printf("Uncomment code to view image!!");                           putchar('\n');
  printf("delimiter1                : ");   printf("0x%04X", *(uint16_t*)(header->delimiter1));                 putchar('\n');
  // printf("big_preview_image_data    : ");   print_img_u16(header->big_preview_image_data  , 290, 290);  putchar('\n');
  printf("big_preview_image_data    : ");   printf("Too large to display!");                                    putchar('\n');
  printf("delimiter2                : ");   printf("0x%04X", *(uint16_t*)(header->delimiter2));                 putchar('\n');
  printf("total_layers              : ");   printf("%i"  , header->total_layers                   );            putchar('\n');
  printf("x_resolution              : ");   printf("%hi" , header->x_resolution                   );            putchar('\n');
  printf("y_resolution              : ");   printf("%hi" , header->y_resolution                   );            putchar('\n');
  printf("x_mirror                  : ");   printf("%hhi", header->x_mirror                       );            putchar('\n');
  printf("y_mirror                  : ");   printf("%hhu", header->y_mirror                       );            putchar('\n');
  printf("x_size_of_platform        : ");   printf("%f"  , header->x_size_of_platform             );            putchar('\n');
  printf("y_size_of_platform        : ");   printf("%f"  , header->y_size_of_platform             );            putchar('\n');
  printf("z_size_of_platform        : ");   printf("%f"  , header->z_size_of_platform             );            putchar('\n');
  printf("layer_thickness           : ");   printf("%f"  , header->layer_thickness                );            putchar('\n');
  printf("common_exposure_time      : ");   printf("%f"  , header->common_exposure_time           );            putchar('\n');
  printf("exposure_delay_mode       : ");   printf("%hhu", header->exposure_delay_mode            );            putchar('\n');
  printf("turn_off_time             : ");   printf("%f"  , header->turn_off_time                  );            putchar('\n');
  printf("bottom_before_lift_time   : ");   printf("%f"  , header->bottom_before_lift_time        );            putchar('\n');
  printf("bottom_after_lift_time    : ");   printf("%f"  , header->bottom_after_lift_time         );            putchar('\n');
  printf("bottom_after_retract_time : ");   printf("%f"  , header->bottom_after_retract_time      );            putchar('\n');
  printf("before_lift_time          : ");   printf("%f"  , header->before_lift_time               );            putchar('\n');
  printf("after_lift_time           : ");   printf("%f"  , header->after_lift_time                );            putchar('\n');
  printf("after_retract_time        : ");   printf("%f"  , header->after_retract_time             );            putchar('\n');
  printf("bottom_exposure_time      : ");   printf("%f"  , header->bottom_exposure_time           );            putchar('\n');
  printf("bottom_layers             : ");   printf("%f"  , header->bottom_layers                  );            putchar('\n');
  printf("bottom_lift_distance      : ");   printf("%f"  , header->bottom_lift_distance           );            putchar('\n');
  printf("bottom_lift_speed         : ");   printf("%f"  , header->bottom_lift_speed              );            putchar('\n');
  printf("lift_distance             : ");   printf("%f"  , header->lift_distance                  );            putchar('\n');
  printf("lift_speed                : ");   printf("%f"  , header->lift_speed                     );            putchar('\n');
  printf("bottom_retract_distance   : ");   printf("%f"  , header->bottom_retract_distance        );            putchar('\n');
  printf("bottom_retract_speed      : ");   printf("%f"  , header->bottom_retract_speed           );            putchar('\n');
  printf("retract_distance          : ");   printf("%f"  , header->retract_distance               );            putchar('\n');
  printf("retract_speed             : ");   printf("%f"  , header->retract_speed                  );            putchar('\n');
  printf("bottom_second_lift_distanc: ");   printf("%f"  , header->bottom_second_lift_distance    );            putchar('\n');
  printf("bottom_second_lift_speed  : ");   printf("%f"  , header->bottom_second_lift_speed       );            putchar('\n');
  printf("second_lift_distance      : ");   printf("%f"  , header->second_lift_distance           );            putchar('\n');
  printf("second_lift_speed         : ");   printf("%f"  , header->second_lift_speed              );            putchar('\n');
  printf("bottom_second_retract_dist: ");   printf("%f"  , header->bottom_second_retract_distance );            putchar('\n');
  printf("bottom_second_retract_spee: ");   printf("%f"  , header->bottom_second_retract_speed    );            putchar('\n');
  printf("second_retract_distance   : ");   printf("%f"  , header->second_retract_distance        );            putchar('\n');
  printf("second_retract_speed      : ");   printf("%f"  , header->second_retract_speed           );            putchar('\n');
  printf("bottom_light_pwm          : ");   printf("%hi" , header->bottom_light_pwm               );            putchar('\n');
  printf("light_pwm                 : ");   printf("%hi" , header->light_pwm                      );            putchar('\n');
  printf("advance_mode              : ");   printf("%hhu", header->advance_mode                   );            putchar('\n');
  printf("printing_time             : ");   printf("%i"  , header->printing_time                  );            putchar('\n');
  printf("total_volume              : ");   printf("%f"  , header->total_volume                   );            putchar('\n');
  printf("total_weight              : ");   printf("%f"  , header->total_weight                   );            putchar('\n');
  printf("total_price               : ");   printf("%f"  , header->total_price                    );            putchar('\n');
  printf("price_unit                : ");   fwrite(header->price_unit, sizeof(char), 8, stdout);                putchar('\n');
  printf("offset_of_layer_content   : ");   printf("%i"  , header->offset_of_layer_content        );            putchar('\n');
  printf("gray_scale_level          : ");   printf("%hhu", header->gray_scale_level               );            putchar('\n');
  printf("transition_layer          : ");   printf("%hi" , header->transition_layer               );            putchar('\n');
}
