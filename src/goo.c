#include <stdlib.h>
#include <string.h>
#include "goo.h"
#include "endian.h"

// ###############################################################################################################################
// INIT FUNCTIONS
// ###############################################################################################################################

void init_goo(goo_t *goo){
  memset(goo, 0, sizeof(goo_header_info_t));
}

void init_goo_header_info(goo_header_info_t *goo_header_info){
  memset(goo_header_info, 0, sizeof(goo_header_info_t));
}

// ###############################################################################################################################
// FREE FUNCTIONS
// ###############################################################################################################################

/// @brief  Free the layer content and it's field
void free_goo_layer_content(goo_layer_content_t *content, int nlayers){
  for(int i=0; i<nlayers; i++){
    free(content[i].image_data);
  } free(content);
}

void free_goo(goo_t *goo){
  free_goo_layer_content((*goo).layer_content, (*goo).header_info.total_layers);
}


// ###############################################################################################################################
// FREAD FUNCTIONS
// ###############################################################################################################################

/// @brief     Reads in a *.goo file and parse the header info
/// @param dst Pointer to where the data will be stored
/// @param fp  Pointer to file stream
/// @return    1=sucess | 0=error
int fread_goo_header_info(goo_header_info_t *dst, FILE *fp) {
  if(fseek(fp, 0, SEEK_SET)) return 0;
  if(!fread_be2le( dst->version                        , sizeof(char    ),       4, fp) ) return 0;  // char [ 4]
  if(!fread_be2le(&dst->magic_tag                      , sizeof(uint64_t),       1, fp) ) return 0;  // uint64_t
  if(!fread_be2le( dst->software_info                  , sizeof(char    ),      32, fp) ) return 0;  // char [32]
  if(!fread_be2le( dst->software_version               , sizeof(char    ),      24, fp) ) return 0;  // char [24]
  if(!fread_be2le( dst->file_time                      , sizeof(char    ),      24, fp) ) return 0;  // char [24]
  if(!fread_be2le( dst->printer_name                   , sizeof(char    ),      32, fp) ) return 0;  // char [32]
  if(!fread_be2le( dst->printer_type                   , sizeof(char    ),      32, fp) ) return 0;  // char [32]
  if(!fread_be2le( dst->profile_name                   , sizeof(char    ),      32, fp) ) return 0;  // char [32]
  if(!fread_be2le(&dst->anti_aliasing_level            , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t        
  if(!fread_be2le(&dst->grey_level                     , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t        
  if(!fread_be2le(&dst->blur_level                     , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t        
  if(!fread_be2le( dst->small_preview_image_data       , sizeof(uint16_t), 116*116, fp) ) return 0;  // uint16_t [116*116]
  if(!fread_be2le(&dst->delimiter1                     , sizeof(uint16_t),       1, fp) ) return 0;  // int16_t
  if(!fread_be2le( dst->big_preview_image_data         , sizeof(uint16_t), 290*290, fp) ) return 0;  // uint16_t [290*290]
  if(!fread_be2le(&dst->delimiter2                     , sizeof(uint16_t),       1, fp) ) return 0;  // int16_t
  if(!fread_be2le(&dst->total_layers                   , sizeof(int32_t ),       1, fp) ) return 0;  // int32_t         
  if(!fread_be2le(&dst->x_resolution                   , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_be2le(&dst->y_resolution                   , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_be2le(&dst->x_mirror                       , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_be2le(&dst->y_mirror                       , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_be2le(&dst->x_size_of_platform             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->y_size_of_platform             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->z_size_of_platform             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->layer_thickness                , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->common_exposure_time           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->exposure_delay_mode            , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_be2le(&dst->turn_off_time                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_before_lift_time        , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_after_lift_time         , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_after_retract_time      , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->before_lift_time               , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->after_lift_time                , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->after_retract_time             , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_exposure_time           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_layers                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_lift_distance           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_lift_speed              , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->lift_distance                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->lift_speed                     , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_retract_distance        , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_retract_speed           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->retract_distance               , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->retract_speed                  , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_second_lift_distance    , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_second_lift_speed       , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->second_lift_distance           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->second_lift_speed              , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_second_retract_distance , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_second_retract_speed    , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->second_retract_distance        , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->second_retract_speed           , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->bottom_light_pwm               , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_be2le(&dst->light_pwm                      , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t         
  if(!fread_be2le(&dst->advance_mode                   , sizeof(bool    ),       1, fp) ) return 0;  // bool            
  if(!fread_be2le(&dst->printing_time                  , sizeof(int32_t ),       1, fp) ) return 0;  // int32_t         
  if(!fread_be2le(&dst->total_volume                   , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->total_weight                   , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le(&dst->total_price                    , sizeof(float   ),       1, fp) ) return 0;  // float           
  if(!fread_be2le( dst->price_unit                     , sizeof(char    ),       8, fp) ) return 0;  // char [ 8]           
  if(!fread_be2le(&dst->offset_of_layer_content        , sizeof(int32_t ),       1, fp) ) return 0;  // int32_t           
  if(!fread_be2le(&dst->gray_scale_level               , sizeof(bool    ),       1, fp) ) return 0;  // bool              
  if(!fread_be2le(&dst->transition_layer               , sizeof(int16_t ),       1, fp) ) return 0;  // int16_t    
  return 1;
}           


int fread_goo_layer_definition(goo_layer_definition_t *dst, FILE *fp){
  // fpos_t pos; getpos(fp, &pos);
  if(!fread_be2le(&dst->pause_flag               , sizeof(int16_t ), 1, fp) ) return 0;  // int16_t 
  if(!fread_be2le(&dst->pause_position_z         , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->layer_position_z         , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->layer_exposure_time      , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->layer_off_time           , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->before_lift_time         , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->after_lift_time          , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->after_retract_time       , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->lift_distance            , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->lift_speed               , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->second_lift_distance     , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->second_lift_speed        , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->retract_distance         , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->retract_speed            , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->second_retract_distance  , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->second_retract_speed     , sizeof(float   ), 1, fp) ) return 0;  // float   
  if(!fread_be2le(&dst->light_pwm                , sizeof(int16_t ), 1, fp) ) return 0;  // int16_t 
  if(!fread_be2le(&dst->delimiter                , sizeof(uint16_t), 1, fp) ) return 0;  // uint16_t
}


/// @brief Reads the layer definition and image data. Automatically allocate memory for layers.
/// @param dst    Pointer to a goo_layer_content_t*, where the data will be stored
/// @param header Pointer to header info. Will be used to get content offset and nlayers value.
/// @param fp     Pointer to file stream
/// @return       0 = Read Fail  |  1 = Read Success
int  fread_goo_layer_content(goo_layer_content_t **dst, goo_header_info_t *header, FILE *fp){
  if(header->offset_of_layer_content == 0)                 return 0;  // Header was created but not read into
  if(fseek(fp, header->offset_of_layer_content, SEEK_SET)) return 0;  

  *dst = (goo_layer_content_t*)calloc(header->total_layers, sizeof(goo_layer_content_t));
  if(*dst == NULL) return 0;
  

  // Loop through all layers and read their layer info
  for(int i=0; i < header->total_layers; i++){
    // Reading layer definition
    if(!fread_goo_layer_definition(&(*dst)[i].definition, fp) )                            return 0;
    if(!fread_be2le(&(*dst)[i].data_size  , sizeof(int32_t ), 1, fp) )                     return 0;

    // Verifying start-byte. First byte before image data should always be 0x55
    if(!fread_be2le(&(*dst)[i].data_start , sizeof(uint8_t), 1, fp) )                      return 0;
    if((*dst)[i].data_start != 0x55) return 0; 

    // Reading image data
    // Subtract 2*uint8 from size to account for the magic number 0x55 we just read and 8-bit checksum at the end
    size_t layer_size = (*dst)[i].data_size - (2*sizeof(uint8_t));
    (*dst)[i].image_data = (uint8_t*)malloc(layer_size*sizeof(uint8_t));
    if( (*dst)[i].image_data == NULL)                                                      return 0;
    if(!fread_be2le( (*dst)[i].image_data , sizeof(uint8_t ), layer_size, fp))             return 0;
    if(!fread_be2le(&(*dst)[i].checksum   , sizeof(uint8_t),  1, fp) )                     return 0;
    if(!fread_be2le(&(*dst)[i].delimiter  , sizeof(uint16_t), 1, fp) )                     return 0;

    // Calculating and verifying checksum
    uint8_t *tmp_image_data = (*dst)[i].image_data;
    uint8_t tmp_checksum = 0; 
    for(int i=0; i<layer_size; i++){
      tmp_checksum += ((uint8_t*)tmp_image_data)[i];
    } tmp_checksum = ~tmp_checksum;
    if(tmp_checksum != (*dst)[i].checksum)                                                 return 0;
  }

  return 1;
}

int fread_goo_file(goo_t *dst, FILE *fp){
  if(!fread_goo_header_info(&(*dst).header_info, fp) )                                     return 0;
  if(!fread_goo_layer_content(&(*dst).layer_content, &(*dst).header_info, fp) )            return 0;
  if(!fread_be2le( (*dst).ending_string, sizeof(char), 11, fp) )                           return 0;
}



// ###############################################################################################################################
// IMAGE CODEC
// ###############################################################################################################################

#define OPCODE_ALLWHITE  0b00
#define OPCODE_GRAYSCALE 0b01
#define OPCODE_DIFFMODE  0b10
#define OPCODE_ALLBLACK  0b11


/// @brief Decode image data and convert it to bitmap pixels
/// @param src Goo data with valid header and data info
/// @return Pointer to 1D bitmap array
uint8_t* decode_goo_image_data(const goo_t *src){
  int32_t image_size    = (*src).header_info.x_resolution * (*src).header_info.y_resolution;
  // subtract two bytes to account for data_start and checksum
  int32_t data_size     = (*src).layer_content[0].data_size - 2;
  uint8_t *encoded_data = (*src).layer_content[0].image_data;
  

  int pixel_pos = 0;  // points to current pixel being drawn
  uint8_t *pixel_data;
  if((pixel_data = (uint8_t*)malloc(image_size * sizeof(uint8_t))) == NULL) return NULL;
  

  // DECODING IMAGE_DATA
  for(int i=0; i<data_size; i++){
    // byte0[7:6] == opcode
    //   b00 This chunk contain all 0x0 pixels
    //   b01 This chunk contain the value of gray between 0x1 to 0xfe. The gray value is in the next byte
    //   b10 This chunk contain the diff value from the previous pixel
    //   b11 This chunk contain all 0xff pixels 
    // byte0[5:4] == operand (operand functionality depends on the opcode)
    //   operand = runlength for opcode = b00 | 01 | 11
    //   operand = difftype  for opcode = b10
 
    uint8_t  opcode    =  encoded_data[i] >> 6;
    uint8_t  operand   = (encoded_data[i] >> 4) & 0b11;

    uint8_t  color     = 0;
    uint32_t runlength = 0;

    int offset0 = i;
    int offset1 = i + 1;
    int offset2 = i + 2;
    int offset3 = i + 3;
    
    if(opcode == OPCODE_DIFFMODE){
      // byte0[5:4] == diffmode  for opcode = 10
      //   b00 : Positive diff value byte0[3:0] to previous pixel. runlength = 1                    
      //   b01 : Positive diff value byte0[3:0] to previous pixel. runlength = next byte          
      //   b10 : Negative diff value byte0[3:0] to previous pixel. runlength = 1        
      //   b11 : Negative diff value byte0[3:0] to previous pixel. runlength = next byte
      uint8_t diff = encoded_data[i] & 0x0F;
      switch(operand){
        case 0b00: 
          color = color + diff;
          runlength = 1;
          break;
        case 0b01: 
          color = color + diff;
          runlength = encoded_data[++i];
          break;
        case 0b10: 
          color = color - diff;
          runlength = 1;
          break;
        case 0b11: 
          color = color - diff;
          runlength = encoded_data[++i];
          break;
        default: free(pixel_data); return NULL;
      }
    } 
    
    else{
      // byte0[5:4] == runlength for opcode = 00 | 01 | 11
      //   b00 : runlength = byte0[3:0]                     
      //   b01 : runlength = [byte1 byte0[3:0]]             
      //   b10 : runlength = [byte1 byte2 byte0[3:0]]       
      //   b11 : runlength = [byte1 byte2 byte3 byte0[3:0]] 
      switch(opcode){
        case OPCODE_ALLWHITE:  color = 0;                     break; 
        case OPCODE_GRAYSCALE: color = encoded_data[++i];     offset1++; offset2++; offset3++; break;        
        case OPCODE_ALLBLACK:  color = 0xFF;                  break;
        default: free(pixel_data); return NULL;
      }
      switch(operand){
        case 0b00: 
          runlength = encoded_data[offset0] & 0x0F;   
          break;
        case 0b01: 
          runlength = (encoded_data[offset1]<< 4) | (encoded_data[offset0] & 0x0F);
          i = i + 1;  
          break;
        case 0b10: 
          runlength = (encoded_data[offset1]<<12) | (encoded_data[offset2]<< 4) | (encoded_data[offset0] & 0x0F);       
          i = i + 2;
          break;
        case 0b11: 
          runlength = (encoded_data[offset1]<<20) | (encoded_data[offset2]<<12) | (encoded_data[offset3]<<4) | (encoded_data[offset0] & 0x0F);     
          i = i + 3;
          break;
        default: free(pixel_data); return NULL;
      }

      // Drawing out decoded pixel data
      if(runlength <= 0) return NULL;
      for(int j=0; j < runlength; j++){
        pixel_data[pixel_pos+j] = color;
      } pixel_pos = pixel_pos + runlength;
    }
  }

  return pixel_data;
}



// ###############################################################################################################################
// PRINTING FUNCTIONS
// ###############################################################################################################################

/// @brief Prints image given u16 pixel datas WORD[R_u5: G_u6: B_u5]
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

      if     (grey > 65) printf("$$");
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
      else printf("E"); // unexpected value error
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
  // printf("magic_tag                 : ");   fwrite(header->magic_tag       , sizeof(char),       8, stdout);    putchar('\n');
  printf("magic_tag                 : ");   printf("0x%016lX", header->magic_tag);                              putchar('\n');
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
  printf("delimiter1                : ");   printf("0x%04hX", header->delimiter1                  );            putchar('\n');
  // printf("big_preview_image_data    : ");   print_img_u16(header->big_preview_image_data  , 290, 290);  putchar('\n');
  printf("big_preview_image_data    : ");   printf("Too large to display!"                        );            putchar('\n');
  printf("delimiter2                : ");   printf("0x%04hX", header->delimiter2                  );            putchar('\n');
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


/// @brief Print layer definition
/// @param definition Pointer to layer definition
void print_goo_layer_definition(goo_layer_definition_t *definition){
  printf("pause_flag              : ");   printf("%hi"  , definition->pause_flag              );            putchar('\n');  // int16_t 
  printf("pause_position_z        : ");   printf("%f"   , definition->pause_position_z        );            putchar('\n');  // float   
  printf("layer_position_z        : ");   printf("%f"   , definition->layer_position_z        );            putchar('\n');  // float   
  printf("layer_exposure_time     : ");   printf("%f"   , definition->layer_exposure_time     );            putchar('\n');  // float   
  printf("layer_off_time          : ");   printf("%f"   , definition->layer_off_time          );            putchar('\n');  // float   
  printf("before_lift_time        : ");   printf("%f"   , definition->before_lift_time        );            putchar('\n');  // float   
  printf("after_lift_time         : ");   printf("%f"   , definition->after_lift_time         );            putchar('\n');  // float   
  printf("after_retract_time      : ");   printf("%f"   , definition->after_retract_time      );            putchar('\n');  // float   
  printf("lift_distance           : ");   printf("%f"   , definition->lift_distance           );            putchar('\n');  // float   
  printf("lift_speed              : ");   printf("%f"   , definition->lift_speed              );            putchar('\n');  // float   
  printf("second_lift_distance    : ");   printf("%f"   , definition->second_lift_distance    );            putchar('\n');  // float   
  printf("second_lift_speed       : ");   printf("%f"   , definition->second_lift_speed       );            putchar('\n');  // float   
  printf("retract_distance        : ");   printf("%f"   , definition->retract_distance        );            putchar('\n');  // float   
  printf("retract_speed           : ");   printf("%f"   , definition->retract_speed           );            putchar('\n');  // float   
  printf("second_retract_distance : ");   printf("%f"   , definition->second_retract_distance );            putchar('\n');  // float   
  printf("second_retract_speed    : ");   printf("%f"   , definition->second_retract_speed    );            putchar('\n');  // float   
  printf("light_pwm               : ");   printf("%hi"  , definition->light_pwm               );            putchar('\n');  // int16_t 
  printf("delimiter               : ");   printf("0x%04hX", definition->delimiter             );           // putchar('\n');  // uint16_t
}

/// @brief Print info of layer_content[x]
/// @param content Pointer to layer_x
void print_goo_layer_content(goo_layer_content_t *content){
  print_goo_layer_definition(&content->definition);                                                         putchar('\n');
  printf("data_size               : ");   printf("%i"      , content->data_size               );            putchar('\n');
  printf("data_start              : ");   printf("0x%02hhX", content->data_start              );            putchar('\n');
  // printf("image_data              : ");   printf("%hi"  , content->image_data              );            putchar('\n');
  printf("image_data              : ");   printf("Too large to display!"                      );            putchar('\n');
  printf("checksum                : ");   printf("0x%02hhX", content->checksum                );            putchar('\n');
  printf("delimiter               : ");   printf("0x%04hX" , content->delimiter               );            putchar('\n');
}

/// @brief Print all info about the .goo file.
/// @param goo Pointer to the goo_t
/// @param max_layer Max numbers of layer contents to print
void print_goo(goo_t *goo, int max_layer){
  printf("____________________Header____________________\n");
  print_goo_header_info(&(*goo).header_info); putchar('\n');

  for(int i=0; i<max_layer && i<(*goo).header_info.total_layers; i++){
    printf("_______________Layer[%i]_______________\n", i);
    print_goo_layer_content(&(*goo).layer_content[i]); putchar('\n');
  }
  
  printf("ending_string           : "); printf("0x");
  for(int i=0; i<sizeof((*goo).ending_string); i++){
    printf("%02hhX ", ((uint8_t*)(*goo).ending_string)[i]); 
  } putchar('\n');

  // printf("magic_tag               : "); printf("0x%06X%016lX\n", *((uint32_t*)((*goo).ending_string + 8)), *((uint64_t*)(*goo).ending_string)); 
}