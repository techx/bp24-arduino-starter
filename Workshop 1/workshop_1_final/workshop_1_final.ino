#define RED_LED 11
#define BUTTON 12

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

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
}
