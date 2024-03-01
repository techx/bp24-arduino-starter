#include <NewPing.h> // include the ultrasonic sensor library
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Servo.h>  // include the Servo library

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

#define SERVO 6
Servo servo;

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
  servo.attach(SERVO);
  servo.write(0);

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

  servo.attach(SERVO);
  servo.write(0);
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

void read_joystick() {
  int joystick_x_value = analogRead(JOYSTICK_X); // read the analog value going into the joystick pin for the x direction
  int joystick_y_value = analogRead(JOYSTICK_Y); // read the analog value going into the joystick pin for the y direction
  int joystick_sw_value = digitalRead(JOYSTICK_BTN); // read the digital value going into the joystick button pin

  Serial.print("Joystick X: ");
  Serial.println(joystick_x_value);

  int servo_pos = map(joystick_x_value, 0, 1023, 0, 180);
  servo.write(servo_pos);
}

void read_ultrasonic_sensor() {
  int ultrasonic_distance_cm = sonar.ping_cm(); // read the distance in cm going to the ultrasonic sensor 

  Serial.print(" Ultrasonic: ");
  Serial.println(ultrasonic_distance_cm);

  Serial.println();
}

void spin_servo(int start_pos, int end_pos) {
  if (start_pos < end_pos) {  // Servo position should increase from start to end
    for (int pos = start_pos; pos <= end_pos; pos++) {
      servo.write(pos);
      delay(10);
    }
  } else {  // Servo position should decrease from start to end
    for (int pos = start_pos; pos >= end_pos; pos--) {
      servo.write(pos);
      delay(10);
    }
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
  
  read_joystick();
  read_ultrasonic_sensor();

  spin_servo(0, 180);
}
