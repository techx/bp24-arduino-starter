#define RED_LED 11

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
}

// helper function to blink LED a specific number of times
void blink_led(int num_blinks) {
  for (int i = 0; i < num_blinks; i++) {
    digitalWrite(RED_LED, HIGH);
    delay(300);
    digitalWrite(RED_LED, LOW);
    delay(300);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  blink_led(1);

  // WHY DOES IT BLINK MORE THAN ONCE???
}
