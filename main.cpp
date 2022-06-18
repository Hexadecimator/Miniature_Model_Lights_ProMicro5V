#include <Arduino.h>

bool debug_startup = true; // set this false to stop the debug light sequence that
                           // turns all lights on one by one to make sure none are
                           // burnt out
bool simple_light_pattern = true; // TODO - control this with an external switch

uint8_t light_sequence[6] = { 2, 3, A0, A1, A2, A3 };

int bright = 170;
unsigned long rdm_delayer = 100;
int rdm_on_off = 0;
unsigned long update_seed_time = 180000; // 180000 = 30 minutes (i think)
unsigned long last_seed_update_time = 0;

void allLightsOff() {
  for(int i = 0; i < 6; i++) {
    digitalWrite(light_sequence[i], LOW);
  }
}

void initLights() {
  for(int i = 0; i < 6; i++) {
    pinMode(light_sequence[i], OUTPUT);
  }
  allLightsOff();
  delay(500);
}

void testLights() {
  for(int i = 0; i < 6; i++) {
    digitalWrite(light_sequence[i], HIGH);
    delay(250);
    digitalWrite(light_sequence[i], LOW);
    delay(250);
  }

  for(int i = 0; i < 6; i++) {
    digitalWrite(light_sequence[i], HIGH);
    delay(250);
  }
  delay(1000);
  allLightsOff();
}

void randomOnOff() {
  for(int i = 0; i < 6; i++) {
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
    for(int i = 0; i < 6; i++) {
      if(i%2==0) digitalWrite(light_sequence[i], HIGH);
      else digitalWrite(light_sequence[i], LOW);
    }
    delay(rdm_delay_time);
    rdm_delay_time  = random(250, 750);
    allLightsOff();
    for(int i = 0; i < 6; i++) {
      if(i%2==0) digitalWrite(light_sequence[i], LOW);
      else digitalWrite(light_sequence[i], HIGH);
    }
    delay(rdm_delay_time);
  }
}

void sequence2() {
  allLightsOff();
  for(int i = 0; i < 6; i++) {
    digitalWrite(light_sequence[i], HIGH);
    delay(random(250-450));
  }

  for(int i = 0; i < 6; i++) {
    digitalWrite(light_sequence[i], LOW);
    delay(random(250-450));
  }
}

void setup() {
  //Serial.begin(9600);
  initLights();
  randomSeed(analogRead(A4));
  last_seed_update_time = millis();
  delay(250);
  if(debug_startup) testLights();
}

void loop() {
  // TODO - control simple_light_pattern with an external hardware switch instead of hard-coding
  if(simple_light_pattern) {
    randomOnOff();
  }
  else {
    int pattern_chooser = random(0, 100);
    if(pattern_chooser >= 97) sequence1();
    else if (pattern_chooser >= 80 && pattern_chooser < 96) sequence2();
    else randomOnOff();
  }
  
  delay(random(250, 750));  
  
  // try to continually randomize the randomness
  if(millis() - last_seed_update_time >= update_seed_time) {
    randomSeed(analogRead(A4));
    last_seed_update_time = millis();
  } 
}