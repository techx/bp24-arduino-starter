#include <NewPing.h> // include the ultrasonic sensor library
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define RED_LED 11
#define BUTTON 12
#define POT_PIN A0
#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define JOYSTICK_BTN 7
#define ULTRASONIC_TRIGGER 9
#define ULTRASONIC_ECHO 10
int max_ultrasonic_distance_cm = 400; // set the maximum measureable distance for the ultrasonic sensor to 400cm 
NewPing sonar(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO, max_ultrasonic_distance_cm); 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting program...");
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_BTN, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello World!");
  display.display();

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

void read_joystick() {
  int joystick_x_value = analogRead(JOYSTICK_X); // read the analog value going into the joystick pin for the x direction
  int joystick_y_value = analogRead(JOYSTICK_Y); // read the analog value going into the joystick pin for the y direction
  int joystick_sw_value = digitalRead(JOYSTICK_BTN); // read the digital value going into the joystick button pin
}

void read_ultrasonic_sensor() {
  int ultrasonic_distance_cm = sonar.ping_cm(); // read the distance in cm going to the ultrasonic sensor 

  Serial.print(" Ultrasonic: ");
  Serial.print(ultrasonic_distance_cm);

  Serial.println();
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
  
  read_joystick();
  read_ultrasonic_sensor();
}