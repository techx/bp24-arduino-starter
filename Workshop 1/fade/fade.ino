#define RED_LED 11

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
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

  if (led_is_off) {
    led_brightness = 255;
  }
}
