#include <SPI.h>
#include <TFT_eSPI.h>
#include <Free_Fonts.h>
#include <lvgl.h>
#include <lv_conf.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// LVGL variables
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ TFT_WIDTH * TFT_HEIGHT / 10 ];

// Function prototypes
void display_random_stuffs();
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void lv_example_get_started_2(void);
void lv_example_get_started_4(void);

void setup(void) {

  // LVGL setup
  lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, TFT_WIDTH * TFT_HEIGHT / 10 );

  // TFT display setup
  tft.init();
  tft.setRotation(1);  // view display horizontally
  // tft.fillScreen(TFT_BLACK);
  // tft.setCursor(0, 0, 4);
  // tft.setTextColor(TFT_WHITE);
  // tft.println(" White text");

  // Using free fonts will have more sizes to choose
  // tft.setCursor(0, 0);
  // tft.setFreeFont(FS12);
  // tft.println();
  // tft.print("Printed using free fonts");

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = TFT_HEIGHT;  // flipped since we use horizontal view
  disp_drv.ver_res = TFT_WIDTH;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*Display random stuffs*/
  // display_random_stuffs();
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
}

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print( lv_log_level_t level, const char * buf )
{
    LV_UNUSED(level);
    Serial.flush();
}
#endif

void display_random_stuffs() {
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  /* Create simple label */
  lv_obj_t *label = lv_label_create( lv_scr_act() );
  lv_label_set_text( label, LVGL_Arduino.c_str() );
  lv_obj_align( label, LV_ALIGN_TOP_LEFT, 0, 0 );

  /* Button with label */
  lv_example_get_started_2();

  /* Slider with label */
  lv_example_get_started_4();
}

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/**
 * Create a button with a label and react on click event.
 */
void lv_example_get_started_2(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 30);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    // lv_obj_add_event(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}

/**
 * Create a slider and write its value on a label.
 */
void lv_example_get_started_4(void)
{
    /*Create a slider in the center of the display*/
    lv_obj_t * slider = lv_slider_create(lv_scr_act());
    lv_obj_set_width(slider, 200);                          /*Set the width*/
    lv_obj_center(slider);                                  /*Align to the center of the parent (screen)*/
    // lv_obj_add_event(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);     /*Assign an event function*/

    /*Create a label above the slider*/
    static lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "0");
    lv_obj_align_to(label, slider, LV_ALIGN_OUT_TOP_MID, 0, -15);    /*Align top of the slider*/
}