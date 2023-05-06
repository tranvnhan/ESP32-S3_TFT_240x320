#include <SPI.h>
#include <AGIS_Display.h>

/*Function prototypes*/
void IRAM_ATTR TFT_DisplayISR();

// create pointer for timer
hw_timer_t *Timer3_cfg = NULL; // create a pointer for timer3

void setup(void) {
  Serial.begin(115200);

  /*Setup for timer3*/
  Timer3_cfg = timerBegin(3, 4000, true); // Prescaler = 40000
  timerAttachInterrupt(Timer3_cfg, &TFT_DisplayISR,
                       true);              // call the function TFT_DisplayISR()
  timerAlarmWrite(Timer3_cfg, 1000, true); // Time = 4000*1000/80,000,000 = 50ms
  timerAlarmEnable(Timer3_cfg);            // start the interrupt

  /*Initialize TFT display, LVGL*/
  display_init();

  /*Display the input screen*/
  lv_scr_load(input_scr);
  GUI();
}

// bool flag = false;

void loop() {
  // static lv_obj_t * another_scr = lv_obj_create(NULL);
  // static lv_obj_t * input_scr = lv_obj_create(NULL);

  // if (flag) {
  //   lv_scr_load(another_scr);
  //   another_GUI();
  // }
  // else {
  //   lv_scr_load(input_scr);
  //   GUI();
  // }
  // Serial.println(keypad_check);
}

// timer3 interrupt, for refreshing TFT display
void IRAM_ATTR TFT_DisplayISR(){
  lv_timer_handler(); /* let the GUI do its work */
}