#include <SPI.h>
#include <TFT_eSPI.h>
#include <Free_Fonts.h>
#include <lvgl.h>
#include <lv_conf.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

// LVGL variables
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ TFT_WIDTH * TFT_HEIGHT / 10 ];

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print( lv_log_level_t level, const char * buf )
{
    LV_UNUSED(level);
    Serial.flush();
}
#endif

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


void setup(void) {
  Serial.begin( 115200 );

  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println( LVGL_Arduino );
  Serial.println( "I am LVGL_Arduino" );

  // LVGL setup
  lv_init();
#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif
  lv_disp_draw_buf_init( &draw_buf, buf, NULL, TFT_WIDTH * TFT_HEIGHT / 10 );

  // TFT display setup
  tft.init();
  tft.setRotation(1);  // view display horizontally

  tft.fillScreen(TFT_BLACK);
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

  /* Create simple label */
  lv_obj_t *label = lv_label_create( lv_scr_act() );
  lv_label_set_text( label, LVGL_Arduino.c_str() );
  lv_obj_align( label, LV_ALIGN_TOP_LEFT, 0, 0 );
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
}