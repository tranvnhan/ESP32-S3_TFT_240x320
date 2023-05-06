#ifndef ECFC85B5_FBAD_44F5_B4D7_5DC33680411F
#define ECFC85B5_FBAD_44F5_B4D7_5DC33680411F

#include <TFT_eSPI.h>
// #include <Free_Fonts.h>
#include <lvgl.h>
#include <lv_conf.h>
#include <AGIS_Keypad.h>

extern lv_disp_draw_buf_t draw_buf;
extern lv_color_t color_buf[ TFT_WIDTH * TFT_HEIGHT / 10 ];

extern lv_obj_t * input_scr;
extern lv_obj_t * another_scr;
extern lv_indev_t * keypad_indev;
extern lv_group_t * input_grp;

// Use these variables in main.cpp
extern int32_t keypad_VTBI;
extern int32_t keypad_totalTimeHour;
extern int32_t keypad_totalTimeMinute;
extern int32_t keypad_dropFactor;

/*Keypad variables*/
extern Keypad keypad;

// For testing:
extern bool keypad_check;

void display_init();
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void GUI(void);
static void textarea_event_handler(lv_event_t * event);
static void radiobutton_create(lv_obj_t * parent, const char * txt, uint32_t i);
static void radio_event_handler(lv_event_t * event);
void another_GUI();
static void keypad_read(lv_indev_drv_t * drv, lv_indev_data_t * data);
bool validate_keypad_inputs();

#endif /* ECFC85B5_FBAD_44F5_B4D7_5DC33680411F */
