#define RECORD_GAP_MICROS 12000
#define DECODE_NEC 1
#include <IRremote.h>

int IR_RECEIVE_PIN = 4;

#define FORWARD 1
#define REVERSE 0
#define RIGHT 1
#define LEFT 0

int motor1pin1 = 8;
int motor1pin2 = 9;

int motor2pin1 = 10;
int motor2pin2 = 11;

long remoteData = 0;

void setup() {
  Serial.begin(9600);

  //Setup motor 1
  pinMode(motor1pin1, OUTPUT);  
  pinMode(motor1pin2, OUTPUT);   

  //Setup motor 2
  pinMode(motor2pin1, OUTPUT);  
  pinMode(motor2pin2, OUTPUT);   

  pinMode(5, OUTPUT);  //hand
  pinMode(6, OUTPUT);   //hand

  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

}

void loop() {

  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.decodedRawData != 0) {
      remoteData = IrReceiver.decodedIRData.decodedRawData; 
    }    
    IrReceiver.resume();  // Receive the next value
  } 
  processData();
  delay(20);
}

void processData() {
  Serial.println(remoteData);
  
  if (remoteData == -467959936){
        Serial.println("UP pressed");
        motor_drive(FORWARD);
        delay(200);
  }
  if (remoteData == -150438016){
        Serial.println("BREAK pressed");
        delay(50);
        motor_brake();
        delay(200);
  }
  if (remoteData == -100302976){
        Serial.println("DOWN pressed");
        motor_drive(REVERSE);
        delay(200);
  }
  if (remoteData == -133726336){
      Serial.println("LEFT pressed");
      motor_rotate(LEFT);
      delay(200);
      motor_brake();
      remoteData = -150438016;
  }
  if (remoteData == -167149696){
      Serial.println("RIGHT pressed");
      motor_rotate(RIGHT);
      delay(200);
      motor_brake();
      remoteData = -150438016;
  }
  if (remoteData == -217284736){
      Serial.println("UPP pressed");
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      delay(1000);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
  }
  if (remoteData == -16744576){
      Serial.println("DOWNN pressed");
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      delay(1000);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
  }
  
}

//Stops the motors from spinning and locks the wheels
void motor_brake() {

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

//Controls the direction the motors turn, speed from 0(off) to 255(full speed)
void motor_drive(char direction) {
  if (direction == FORWARD) {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  } else {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  }
}

void motor_rotate(char direction) {
  if (direction == RIGHT) {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
  } else {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
  }
}
