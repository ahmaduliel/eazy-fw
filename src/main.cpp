#include <Arduino.h>
#include <DFPlayer_Mini_Mp3.h>
#include <dht_nonblocking.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <UVLight.h>

#define DHTTYPE DHT_TYPE_21
#define DHTPIN 20

SoftwareSerial serialSW(34, 35);
DHT_nonblocking dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(26, 27, 28, 29, 30, 31);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}