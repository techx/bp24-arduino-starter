#include <NewPing.h> // include the ultrasonic sensor library
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
#define SERVO 6
Servo servo;
#define BUZZER 3

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

  servo.attach(SERVO);
  servo.write(0);

  pinMode(BUZZER, OUTPUT);

  // PASSIVE BUZZER ONLY:
//  play_song();
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

  Serial.print("Joystick X: ");
  Serial.println(joystick_x_value);

  int servo_pos = map(joystick_x_value, 0, 1023, 0, 180);
  servo.write(servo_pos);
}

void read_ultrasonic_sensor() {
  int ultrasonic_distance_cm = sonar.ping_cm(); // read the distance in cm going to the ultrasonic sensor 

  Serial.print(" Ultrasonic: ");
  Serial.println(ultrasonic_distance_cm);
}

void spin_servo(int start_pos, int end_pos) {
  /*
   * Spins the servo from start_pos to end_pos
   */
  // EXPLAIN FOR LOOP BEFORE CODING THIS
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

void buzz() {
  /*
   * ACTIVE BUZZER; makes a "tick" sound
   */
  digitalWrite(BUZZER, HIGH);
  delay(1);  //wait for 1ms for a quick "tick" sound
  digitalWrite(BUZZER, LOW);
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

//  spin_servo(0, 180);

  buzz();
}
