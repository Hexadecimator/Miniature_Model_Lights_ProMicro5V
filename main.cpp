#include <Arduino.h>

uint8_t light_sequence[6] = { 2, 3, A0, A1, A2, A3 };

int bright = 170;
unsigned long rdm_delayer = 100;
int rdm_on_off = 0;

void allLightsOff() {
  for(int i = 0; i <= 6; i++) {
    digitalWrite(light_sequence[i], LOW);
  }
}

void initLights() {
  for(int i = 0; i <= 6; i++) {
    pinMode(light_sequence[i], OUTPUT);
  }
  allLightsOff();
  delay(500);
}

void testLights() {
  for(int i = 0; i <= 6; i++) {
    digitalWrite(light_sequence[i], HIGH);
    delay(250);
    digitalWrite(light_sequence[i], LOW);
    delay(250);
  }

  for(int i = 0; i <= 6; i++) {
    digitalWrite(light_sequence[i], HIGH);
    delay(250);
  }
  delay(1000);
  allLightsOff();
}

void randomOnOff() {
  for(int i = 0; i <= 6; i++) {
    rdm_on_off = random(0,2);
    rdm_delayer = random(150, 600);
    digitalWrite(light_sequence[i], rdm_on_off);
    delay(rdm_delayer);
  }
}

void sequence1() {
  int rdm_num_repeats = random(2, 5);
  for(int i = 0; i <= rdm_num_repeats; i++) {
    int rdm_delay_time  = random(250, 750);
    allLightsOff();
    for(int i = 0; i <= 6; i++) {
      if(i%2==0) digitalWrite(light_sequence[i], HIGH);
      else digitalWrite(light_sequence[i], LOW);
    }
    delay(rdm_delay_time);
    rdm_delay_time  = random(250, 750);
    allLightsOff();
    for(int i = 0; i <= 6; i++) {
      if(i%2==0) digitalWrite(light_sequence[i], LOW);
      else digitalWrite(light_sequence[i], HIGH);
    }
    delay(rdm_delay_time);
  }
}

void sequence2() {
  allLightsOff();
  for(int i = 0; i <= 6; i++) {
    digitalWrite(light_sequence[i], HIGH);
    delay(random(150-350));
  }

  for(int i = 0; i <= 6; i++) {
    digitalWrite(light_sequence[i], LOW);
    delay(random(150-350));
  }
}

void setup() {
  //Serial.begin(9600);
  initLights();
  randomSeed(analogRead(A4));
  delay(250);
  testLights();
}


void loop() {
  int chooser = random(0, 100);
  
  if(chooser >= 97) sequence1();
  else if (chooser >= 80 && chooser < 96) sequence2();
  else randomOnOff();

  delay(random(250, 750));  
}