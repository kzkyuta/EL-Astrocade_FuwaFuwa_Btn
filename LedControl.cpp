#include "LedControl.h"

LedControl::LedControl(uint8_t LedNum, uint8_t PIN, bool Side)
      :Adafruit_NeoPixel(LedNum, PIN, NEO_GRB + NEO_KHZ800),
      side(Side),
      LedNum(LedNum)
{
  Adafruit_NeoPixel::begin();
  Adafruit_NeoPixel::setBrightness(255); //Max 255
}

LedControl::~LedControl(){ }

void LedControl::setup(){
  flag_shoot = false;
  LED_all(0,0,0);
  count = 0;
  cicle = 0;
}

void LedControl::counter(){
  if(flag_shoot){
    count ++;
    if(cicle == maxCicle){
      cicle = 0;
      count = 0;
      flag_shoot = false;
      InitShootEffect();
    }
  }
}

void LedControl::LED_all(uint8_t a, uint8_t b, uint8_t c){ // 
  for(int i=3; i < LedNum; i++){
    this->setPixelColor(i, this->Color(a, b, c));
  }
  this->show();
}

void LedControl::startShootEffect(){
  flag_shoot = true;
  LED_all(0,0,0);
}

void LedControl::InitShootEffect(){
  L_Led_Inc = 11; //最初にフェードインするLED番号
  L_Led_Cnt = 12; 
  L_Led_Dec = 13; 
  R_Led_Inc = 16; 
  R_Led_Cnt = 15; 
  R_Led_Dec = 14; 
}

void LedControl::shootEffect(){
  if(flag_shoot){
    int v = 255/oneCicleCount*count;
    if(side){
      this->setPixelColor(L_Led_Dec, this->Color(255 - v, 255 - v, 255 - v));
      this->setPixelColor(L_Led_Cnt, this->Color(255, 255, 255));
      this->setPixelColor(L_Led_Inc, this->Color(0 + v, 0 + v, 0 + v));
      this->setPixelColor(R_Led_Dec, this->Color(255 - v, 255 - v, 255 - v));
      this->setPixelColor(R_Led_Cnt, this->Color(255, 255, 255));
      this->setPixelColor(R_Led_Inc, this->Color(0 + v, 0 + v, 0 + v));
      if(count == oneCicleCount){
        L_Led_Dec--;
        L_Led_Cnt--;
        L_Led_Inc--;
        R_Led_Dec++;
        R_Led_Cnt++;
        R_Led_Inc++;
        cicle ++;
        count = 0;
      }
    }else{
      this->setPixelColor(L_Led_Dec, this->Color(255 - v, 255 - v, 255 - v));
      this->setPixelColor(L_Led_Cnt, this->Color(255, 255, 255));
      this->setPixelColor(L_Led_Inc, this->Color(0 + v, 0 + v, 0 + v));
      this->setPixelColor(R_Led_Dec, this->Color(255 - v, 255 - v, 255 - v));
      this->setPixelColor(R_Led_Cnt, this->Color(255, 255, 255));
      this->setPixelColor(R_Led_Inc, this->Color(0 + v, 0 + v, 0 + v));
      if(count == oneCicleCount){
        L_Led_Dec--;
        L_Led_Cnt--;
        L_Led_Inc--;
        R_Led_Dec++;
        R_Led_Cnt++;
        R_Led_Inc++;
        cicle ++;
        count = 0;
      }
    }
    this->show();
  }
}

