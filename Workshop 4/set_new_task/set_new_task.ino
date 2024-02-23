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

// game settings
const int num_tasks = 4; // set the number of tasks to 3
long game_score = 0; // set the player's game score to 0
bool game_ended = false; // whether the current game has ended or not

// define an enum of certain game actions the player needs to do:
// press a button, twist a potentiometer, push a joystick, or none
enum game_action {
  PUSH_BUTTON,
  POTENTIOMETER,
  JOYSTICK,
  ULTRASONIC_SENSOR
};
game_action task;

long task_timer = 0; // variable to keep track of how much time has elapsed
long task_time_limit = 3000; // set the amount of time a player has to complete the task (3000 milliseconds = 3 seconds)
long task_pause = 1000; // set the amount of pause time between tasks

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); // start the serial at a baud rate of 115200
  Serial.println("Starting program...");

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
  display.println("Welcome to Bop It!");
  display.display();

  randomSeed(analogRead(5)); // initialize the random number generator with arbitrary data noise from a digital pin

  set_new_task();
}

void loop() {
  // put your main code here, to run repeatedly:

  // main game state check
   if (millis() - task_timer > task_time_limit) {
    end_game();
  } else {
    check_user_action();
  }
}

// variable to keep track of last potentiometer value, 
// so game can keep track of when the current value changes enough to indicate player had twisted potentiometer
int last_pot_value = 0;

void set_new_task() {
  delay(task_pause);
  task = random(num_tasks); // set the task to a random number between 0 and num_tasks - 1 (3 - 1 = 2)
  
  display.clearDisplay();
  display.setCursor(0, 10);
  display.println("Welcome to Bop It!");
  display.display();

	// blink the LED the number of times corresponding to a task
	for (int i = 0; i <= task; i++) {
		digitalWrite(RED_LED, HIGH);
		delay(300);
		digitalWrite(RED_LED, LOW);
		delay(300);
	}
  
	// print the user's score and the new task to Serial
	Serial.println();
	Serial.print("Your score: ");
	Serial.println(game_score);
	Serial.print("Selecting new task ");
	Serial.println(task);

	task_timer = millis(); // reset the game timer to now, so that any time measurement is in reference to the time a task was assigned

	// if the assigned task is to twist a potentiometer, measure the current value of the potentiometer so when the player twists it 
	// to a new value, it can be measured against the last value
	if (task == POTENTIOMETER) {
		last_pot_value = analogRead(POT_PIN);
	}
}

void end_game() {
  set_new_task();
}

void check_user_action() {

}