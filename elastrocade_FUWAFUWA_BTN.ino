#include <MsTimer2.h>
#include "LedControl.h"
#include "StaticValues.h"

LedControl led_0 = LedControl(LEDNUM, PIN_0, false);
LedControl led_1 = LedControl(LEDNUM, PIN_1, false);

int I_all_0 = 0;
int I_all_1 = 0;
int pos_I_all_0;
int diff_0;
int diff_1;
int array_0[ARRAY_SIZE];
int array_1[ARRAY_SIZE];
int sensorValue0 = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;

bool stateShoot_0;
bool stateShoot_1;

void readData() { // takes 0.72 - 1.1 ms (ARRAY_SIZE:10 - 100) to finish all calculation
 sensorValue0 = analogRead(A0);
 sensorValue1 = analogRead(A1);
 sensorValue2 = analogRead(A2);
 sensorValue3 = analogRead(A3);
 sensorValue4 = analogRead(A4);
 sensorValue5 = analogRead(A5);
 I_all_0 = sensorValue0 + sensorValue1 + sensorValue2;
 I_all_1 = sensorValue3 + sensorValue4 + sensorValue5;
 push(array_0, I_all_0);
 push(array_1, I_all_1);
}

void setup() {
 // initialize serial communication at 9600 bits per second:
 Serial.begin(9600);
 led_0.setup();
 led_1.setup();

 stateShoot_0 = false;
 stateShoot_1 = false;
 
 for (int i = 0; i < ARRAY_SIZE; i++) {
   array_0[i] = 0;
   array_1[i] = 0;
 }
 MsTimer2::set(5, readData);  // can be slower.
 MsTimer2::start();
}

void loop() {
  diff_0 = array_0[ARRAY_SIZE - 1] - array_0[0];
  diff_1 = array_1[ARRAY_SIZE - 1] - array_1[0];
//  Serial.print(diff_0);
//  Serial.print(", ");
//  Serial.println(diff_1);

  if(diff_0 > TH){
    if(!stateShoot_0){ 
      led_0.startShootEffect();
      stateShoot_0 = true;      
    }
  }else{
    stateShoot_0 = false;
  }

  if(diff_1 > TH){
    if(!stateShoot_1){
      led_1.startShootEffect();
      stateShoot_1 = true;
    }
  }else{
    stateShoot_1 = false;
  }

  sendSignal();
  led_0.counter();
  led_1.counter();
  led_0.shootEffect();
  led_1.shootEffect();
//  Serial.println(led_0.cicle);
  
 delay(1);        // delay in between reads for stabili/ty
}
void push(int ArrayData[], int val) {
 for (int i = 0; i < ARRAY_SIZE; i++) {
   if (i == ARRAY_SIZE - 1) {
     ArrayData[i] = val;
   } else {
     ArrayData[i] = ArrayData[i + 1];
   }
 }
}

void sendSignal(){
  if(led_0.flag_shoot && led_0.cicle < 11){ 
    if(led_0.count == 0 && led_0.cicle == 0) Serial.write(1);
    if(led_0.count == 4 && led_0.cicle == 5){
      Serial.write(0);
    }
  }
  
  if(led_1.flag_shoot && led_1.cicle < 11){
    if(led_1.count == 0 && led_1.cicle == 0) Serial.write(3);
    if(led_1.count == 4 && led_1.cicle == 10){
      stateShoot_1 = false;
      Serial.write(2);
    }
  }
}

