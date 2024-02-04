void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.println("Setup Complete.");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  Serial.println("LED On.");
  delay(1000);
  digitalWrite(13, LOW);
  Serial.println("LED Off.");
  delay(1000);
}
