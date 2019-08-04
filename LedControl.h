#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class LedControl : public Adafruit_NeoPixel {
  public:
    LedControl(uint8_t, uint8_t, bool);
    ~LedControl();
    uint8_t L_Led_Inc = 11; //最初にフェードインするLED番号
    uint8_t L_Led_Cnt = 12; //最初にフェードインするLED番号
    uint8_t L_Led_Dec = 13; //最初にフェードインするLED番号
    uint8_t R_Led_Inc = 16; //最初にフェードインするLED番号
    uint8_t R_Led_Cnt = 15; //最初にフェードインするLED番号
    uint8_t R_Led_Dec = 14; //最初にフェードインするLED番号
    void setup();
    void LED_all(uint8_t, uint8_t, uint8_t);
    void shootEffect();
    void startShootEffect();
    void InitShootEffect();
    void counter();
    bool flag_shoot;
    int count;
    int cicle;
    uint8_t oneCicleCount = 5;
    uint8_t maxCicle = 21;
    
  private:
    bool side;
    uint8_t LedNum;
};
