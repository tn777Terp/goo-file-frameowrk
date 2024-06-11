#pragma once

#include <stdint.h>
#include <stdbool.h>

// #######################################################################################
// Data Structure Summary
// #######################################################################################
// goo_t
// ├─ goo_header_info_t
// ├─ ...
// ├─ goo_layer_content_t[*]
// │  ├─ goo_layer_definition_t
// │  ├─ ...



// Data are stored as little endian. You must convert them back to big endian when
// writing out file.
#pragma packed
typedef struct goo_header_info_t {
  char     version                      [ 4];  // Format version
  uint64_t magic_tag                        ;  // Fix constant: 0x07_00_00_00_44_4C_50_00
  char     software_info                [32];  // Software info
  char     software_version             [24];  // Software version
  char     file_time                    [24];  // File create time
  char     printer_name                 [32];  // Printer name
  char     printer_type                 [32];  // Printer type
  char     profile_name                 [32];  // Resin profile name
  int16_t  anti_aliasing_level              ;  // Anti-aliasing level setting by slicer
  int16_t  grey_level                       ;  // Grey level
  int16_t  blur_level                       ;  // Blur level
  uint16_t small_preview_image_data[116*116];  // u16[RED 5-bits, GREEN 6-bits, BLUE 5-bits]
  uint16_t delimiter1                       ;  // Fixed value: 0x0D_0A
  uint16_t big_preview_image_data  [290*290];  // u16[RED 5-bits, GREEN 6-bits, BLUE 5-bits]
  uint16_t delimiter2                       ;  // Fixed value: 0x0D_0A
  int32_t  total_layers                     ;  // Total number of layers
  int16_t  x_resolution                     ;  // Resolution of printing LCD in x-direction
  int16_t  y_resolution                     ;  // Resolution of printing LCD in y-direction
  bool     x_mirror                         ;  // 1 = mirror : Indicates if the image is x-mirrored by slicer
  bool     y_mirror                         ;  // 1 = mirror : Indicates if the image is y-mirrored by slicer
  float    x_size_of_platform               ;  // (mm)     Active area of printing in x-direction
  float    y_size_of_platform               ;  // (mm)     Active area of printing in y-direction
  float    z_size_of_platform               ;  // (mm)     Active area of printing in z-direction
  float    layer_thickness                  ;  // (mm)     Layer thickness
  float    common_exposure_time             ;  // (sec)    Common layer exposure time
  bool     exposure_delay_mode              ;  // 1 = Static Time  |  0 = Turn Off Time
  float    turn_off_time                    ;  // (sec) Delay time of layer exposure in Turn-off-time-mode
  float    bottom_before_lift_time          ;  // (sec)    Waiting time before lift for bottom layers
  float    bottom_after_lift_time           ;  // (sec)    Waiting time after lift for bottom layers
  float    bottom_after_retract_time        ;  // (sec)    Waiting time after retract for bottom layers
  float    before_lift_time                 ;  // (sec)    Waiting time before lift for common layers
  float    after_lift_time                  ;  // (sec)    Waiting time after lift for common layers
  float    after_retract_time               ;  // (sec)    Waiting time after retract for common layers
  float    bottom_exposure_time             ;  // (sec)    Exposure time of bottom layer
  float    bottom_layers                    ;  // (sec)    Number of bottom layers
  float    bottom_lift_distance             ;  // (mm)     Lift distance for bottom layers
  float    bottom_lift_speed                ;  // (mm/min) Lift speed for bottom layers
  float    lift_distance                    ;  // (mm)     Lift distance for common layers
  float    lift_speed                       ;  // (mm/min) Lift speed for common layers
  float    bottom_retract_distance          ;  // (mm)     Retract distance for bottom layers
  float    bottom_retract_speed             ;  // (mm/min) Retract speed for bottom layers
  float    retract_distance                 ;  // (mm)     Retract distance for common layers
  float    retract_speed                    ;  // (mm/min) Retract speed for common layers
  float    bottom_second_lift_distance      ;  // (mm)     Retract distance of second stage for common layers
  float    bottom_second_lift_speed         ;  // (mm/min) Retract speed of second stage for common layers
  float    second_lift_distance             ;  // (mm)     Lift distance of second stage for common layers
  float    second_lift_speed                ;  // (mm/min) Lift speed of second stage for common layers
  float    bottom_second_retract_distance   ;  // (mm)     Lift distance of second stage for bottom layers
  float    bottom_second_retract_speed      ;  // (mm/min) Lift speed of second stage for bottom layers
  float    second_retract_distance          ;  // (mm)     Retract distance of second stage for common layers
  float    second_retract_speed             ;  // (mm/min) Retract speed of second stage for common layers
  int16_t  bottom_light_pwm                 ;  // Power of light for bottom layers (0-255)
  int16_t  light_pwm                        ;  // Power of light for common layers (0-255)
  bool     advance_mode                     ;  // 0 = Normal Mode  |  1 = Advance Mode - Printing use the value of "Layer Definition Content"
  int32_t  printing_time                    ;  // (sec)    Printing time
  float    total_volume                     ;  // (mm^3)   Volume of all parts
  float    total_weight                     ;  // (g)      Weight of all parts
  float    total_price                      ;  // Total cost of resin
  char     price_unit                   [ 8];  // Unit of price. eg: $
  int32_t  offset_of_layer_content          ;  // Positiono of layer_content start
  bool     gray_scale_level                 ;  // 0 = Range of pixels's grey value is 0x0-0xF  |  1 = Range of pixel's grey value is 0x0-0xFF
  int16_t  transition_layer                 ;  // Numbers of transition layers
} goo_header_info_t;


#pragma packed
typedef struct goo_layer_definition_t {
  int16_t  pause_flag               ;  // 0 = Reserved  |  1 = Current layer pause printing
  float    pause_position_z         ;  // (mm)     Lift distance of z-axis when pause_flag=1
  float    layer_position_z         ;  // (mm)     Height of current layer
  float    layer_exposure_time      ;  // (sec)    Exposure time of current layer
  float    layer_off_time           ;  // (sec)    Off time of current layer when exposure_delay_mode=0
  float    before_lift_time         ;  // (sec)    Waiting time before lift for current layer.   Enabled when exposure_delay_mode=1
  float    after_lift_time          ;  // (sec)    Waiting time after lift for current layer.    Enabled when exposure_delay_mode=1
  float    after_retract_time       ;  // (sec)    Waiting time after retract for current layer. Enabled when exposure_delay_mode=1
  float    lift_distance            ;  // (mm)     Lift distance for current layer
  float    lift_speed               ;  // (mm/min) Lift speed for current layer
  float    second_lift_distance     ;  // (mm)     Lift distance of second stage for current layer
  float    second_lift_speed        ;  // (mm/min) Lift speed of second stage for current layer
  float    retract_distance         ;  // (mm)     Retract distance for current layer
  float    retract_speed            ;  // (mm/min) Retract speed for current layer
  float    second_retract_distance  ;  // (mm)     Retract distance of second stage for current layer
  float    second_retract_speed     ;  // (mm/min) Retract speed of second stage for current layer
  int16_t  light_pwm                ;  // Power of light for current layers (0-255)
  uint16_t delimiter                ;  // Fixed value: 0x0D_0A
} goo_layer_definition_t;

#pragma packed
typedef struct goo_layer_content_t {
  goo_layer_definition_t definition ;  // Layer definitions
  int32_t                data_size  ;  // Indicate size of image_data
  uint8_t                data_start ;  // Fix value: 0x55 - indicates start of image_data
  uint8_t               *image_data ;  // See spec sheet pdf for details on the formatting
  uint8_t                checksum   ;  // 8-bit checksum of image_data
  uint16_t               delimiter  ;  // Fix value: 0x0D_0A
} goo_layer_content_t;              


#pragma packed
typedef struct goo_t {
  goo_header_info_t    header_info  ;  // File header
  goo_layer_content_t *layer_content;  // Contains layer datas
  char             ending_string[11];  // Fix value: 0x00_00_00_07_00_00_00_44_4C_50_00 - indicates end of file
} goo_t;