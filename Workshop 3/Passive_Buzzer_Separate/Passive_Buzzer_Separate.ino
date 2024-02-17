/*
 * The passive buzzer "tone" library must be used separately from the bop it game code
 * bc Arduino Uno does not have enough timers to support another PWM output.
 */


#define BUZZER 3

// Global Variable
int notes[5] = {440, 494, 523, 587, 659};

void setup() {
  pinMode(BUZZER, OUTPUT);

  tone(BUZZER, 1000); // 1000 hz
  delay(100);
}

void loop() {
  tone(BUZZER, 440); // A4
  delay(10);

  tone(BUZZER, 494); // B4
  delay(10);

  tone(BUZZER, 523); // C4
  delay(10);

  tone(BUZZER, 587); // D4
  delay(10);

  tone(BUZZER, 659); // E4
  delay(10);

  noTone(BUZZER);
  delay(1000);

  for (int i=0; i<5; i++) {
    tone(BUZZER, notes[i]);
    delay(10);
    notes[i] = notes[i] + 100;
  }
  
  noTone(BUZZER);
  delay(1000);
}
