#include <SPI.h>
#include <TFT_eSPI.h>
#include <Free_Fonts.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library

void setup(void) {
  tft.init();

  // BUG: some font sizes not working!!!
  tft.fillScreen(TFT_BLACK);
  // tft.setCursor(0, 0, 4);
  // tft.setTextColor(TFT_WHITE);
  // tft.println(" White text");

  tft.setCursor(0, 0);
  tft.setFreeFont(FS12);
  tft.println();
  tft.print("Printed using free fonts");
}

void loop() {

}