/*
 *Simple program to test an RGB LED or an LED Strip 
 *Connect the pins 9, 10, 11 to the RGB inputs
 */
 
void setup() {
  //initialise pins as output
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  //set different colours with a delay
  analogWrite(9, 100);
  analogWrite(10, 100);
  analogWrite(11, 100);
  delay(500);
  analogWrite(9, 200);
  analogWrite(10, 0);
  analogWrite(11, 0);
  delay(500);
  analogWrite(9, 0);
  analogWrite(10, 200);
  analogWrite(11, 0);
  delay(500);
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 200);
  delay(500);
  analogWrite(9, 200);
  analogWrite(10, 200);
  analogWrite(11, 200);
  delay(500);
  analogWrite(9, 120);
  analogWrite(10, 10);
  analogWrite(11, 500);
  delay(500);
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  delay(500);
}
