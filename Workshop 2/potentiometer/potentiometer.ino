#define RED_LED 11
#define BUTTON 12
#define POT_PIN A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting program...");
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
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

// helper function to fade LED up and down
void fade_led() {
  // Make LED brighter
  for (int i = 0; i < 255; i += 1) {
    analogWrite(RED_LED, i);
    delay(10);
  }

  // Make LED dimmer
  for (int i = 255; i >= 0; i -= 1) {
    analogWrite(RED_LED, i);
    delay(10);
  }
}

void loop() {
  // put your main code here, to run repeatedly:  
//  blink_led(1);
//  fade_led();

  int button = digitalRead(BUTTON);

  if (button == 0) {  // button pressed
    fade_led();
  }

  int pot_value = analogRead(POT_PIN); // read the analog value going into the potentiometer pin
  int brightness = map(pot_value, 0, 1023, 0, 255); // rescale the potentiometer value from 0 - 1023 down to 0 - 255
  analogWrite(RED_LED, brightness);
  
  // print the potentiometer values to the serial
  Serial.print("Pot: ");
  Serial.println(pot_value);
}
