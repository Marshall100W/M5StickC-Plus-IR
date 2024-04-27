
#include <M5StickCPlus.h>
#define NO_LED_FEEDBACK_CODE
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

uint8_t brightness = 7;
unsigned long tmp_punto = millis();
#define puls_superior 37
#define puls_lateral 39

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Axp.ScreenBreath(brightness);
  M5.Lcd.setRotation(3);
  pinMode(puls_superior, INPUT_PULLUP);
  pinMode(puls_lateral, INPUT_PULLUP);
  IrSender.begin(9);
}

uint8_t sRepeats = 0;

void loop() {
  punto();
  if (!digitalRead(puls_superior)) {
    uint16_t sAddress = 0x7F00;
    uint8_t sCommand = 0x5;
    IrSender.sendNEC(0x7F00, 0x5, 0);
    Serial.println("Baja volumen");
    delay(300);
  }
  if (!digitalRead(puls_lateral)) {
    uint16_t sAddress = 0x7F00;
    uint8_t sCommand = 0x1;
    IrSender.sendNEC(sAddress, sCommand, sRepeats);
    Serial.println("Sube volumen");
    delay(300);
  }
}


void punto() {
  if (millis() > tmp_punto + 3000) {
    tmp_punto = millis();
    M5.lcd.fillRect(234, 10, 6, 6, GREEN);
  }
  if (millis() > tmp_punto + 2000) {
    M5.lcd.fillRect(234, 10, 6, 6, BLACK);
  }
}
