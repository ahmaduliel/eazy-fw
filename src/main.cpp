#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <UVLight.h>
#include <SoundMan.h>
#include <FlowState.h>

SoftwareSerial serialSW(34, 35);
LiquidCrystal lcd(26, 27, 28, 29, 30, 31);

SoundMan Sound;
UVLight UVControl;
FlowState State;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup Start...");
  lcd.begin(16,2);
  Sound.init(&serialSW, 9600, 20, 66);
  UVControl.init(32, false);
  State.init(&lcd, 200, &Sound, &UVControl, 5000, 25);
  Serial.println("Setup Complete..");
}

void loop() {
  State.handler();
  UVControl.handler();
}