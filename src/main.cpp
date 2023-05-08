#include <SPI.h>
#include <AGIS_Display.h>

/*Function prototypes*/
void IRAM_ATTR TFT_DisplayISR();

// create pointer for timer
hw_timer_t *Timer3_cfg = NULL; // create a pointer for timer3

void setup(void) {
  Serial.begin(115200);

  /*Setup for timer3*/
  // NOTE: too frequent timer interrupt may cause display frozen issue
  Timer3_cfg = timerBegin(3, 8000, true); // Prescaler = 40000
  timerAttachInterrupt(Timer3_cfg, &TFT_DisplayISR,
                       true);              // call the function TFT_DisplayISR()
  timerAlarmWrite(Timer3_cfg, 1000, true); // Time = 8000*1000/80,000,000 = 100ms
  timerAlarmEnable(Timer3_cfg);            // start the interrupt

  /*Initialize TFT display, LVGL*/
  display_init();

  /*Display the input screen*/
  lv_scr_load(input_scr);
  input_screen();
}

void loop() {
}

// timer3 interrupt, for refreshing TFT display
void IRAM_ATTR TFT_DisplayISR(){
  lv_timer_handler(); /* let the GUI do its work */
}