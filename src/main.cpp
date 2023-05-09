#include <SPI.h>
#include <AGIS_Display.h>

extern unsigned int numDrops;
extern unsigned int dripRate;
extern float infusedVolume;
extern long infusedTime;

/*Function prototypes*/
void IRAM_ATTR TFT_DisplayISR();

// create pointer for timer
hw_timer_t *Timer3_cfg = NULL; // create a pointer for timer3

void setup(void) {
  Serial.begin(115200);

  /*Setup for timer3*/
  // TODO: find out why calling `lv_timer_handler()` in timer interrupt causes
  // undeterministic behaviour
  // NOTE: too frequent timer interrupt may cause display frozen issue
  // Timer3_cfg = timerBegin(3, 4000, true); // Prescaler = 40000
  // timerAttachInterrupt(Timer3_cfg, &TFT_DisplayISR,
  //                      true);              // call the function TFT_DisplayISR()
  // timerAlarmWrite(Timer3_cfg, 1000, true); // Time = 4000*1000/80,000,000 = 50ms
  // timerAlarmEnable(Timer3_cfg);            // start the interrupt

  /*Initialize TFT display, LVGL*/
  display_init();

  /*Display the input screen*/
  lv_scr_load(input_scr);
  input_screen();
}

void loop() {
  lv_timer_handler(); /* let the GUI do its work */
}

// timer3 interrupt, for refreshing TFT display
void IRAM_ATTR TFT_DisplayISR(){
  lv_timer_handler(); /* let the GUI do its work */
}