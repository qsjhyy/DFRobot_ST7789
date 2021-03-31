#include <DFRobot_ST7789.h>

DFRobot_ST7789 myst7789;

void setup(void) {
  Serial.begin(115200);
  myst7789.st7789_init();
  myst7789.fillScreen(0xf80000);
}

void loop() {

}