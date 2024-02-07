#define RED_LED 11
#define BUTTON 12
#define POT_PIN A0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting program...");
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);

  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(500);
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(500);
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(500);
}

int led_brightness = 255;

bool fade_led() {
  if (led_brightness >= 0) {
    analogWrite(RED_LED, led_brightness);
    led_brightness -= 1;
    return false;
  }
  else {
    return true;
  }
}


void loop() {
  // put your main code here, to run repeatedly:  
  bool led_is_off = fade_led();
  delay(10);

  int button = digitalRead(BUTTON);

  if (button == 0) {
    led_brightness = 255;
  }

  int pot_value = analogRead(POT_PIN); // read the analog value going into the potentiometer pin
  int brightness = map(pot_value, 0, 1023, 0, 255); // rescale the potentiometer value from 0 - 1023 down to 0 - 255
  analogWrite(RED_LED, brightness);
  
  // print the potentiometer values to the serial
  Serial.print("Pot: ");
  Serial.println(pot_value);
}