/*
 Program for controlling a robot with two motors.
 The robot turns when motors changes their speed and direction.
 Front bumpers on left and right sides detect obstacles.
 Motor-driver is used to run motors.
 Motors are run on full speed.
 */
//right side
const int pinRightMotorDirectionIn3 = 10;
const int pinRightMotorDirectionIn4 = 11;
const int pinRightMotorSpeed = 12;
const int pinRightBumper = 5;
//left side
const int pinLeftMotorDirectionIn1 = 2;
const int pinLeftMotorDirectionIn2 = 3;
const int pinLeftMotorSpeed = 4;//"Channel B" on motor-driver
const int pinLeftBumper = 8;
//timeouts - they are different to avoid robot stuck in a corner
const int turnRightTimeout = 150;
const int turnLeftTimeout = 200;
//set in counter how long a motor is running back: N/10 (in milliseconds)
int countDownWhileMovingToRight;
int countDownWhileMovingToLeft;
//Initialization
void setup() {
  initPins();
  runRightMotorForward();
  runLeftMotorForward();
  startMotors();
}
//Main loop
void loop() {
  verifyAndSetRightSide();
  verifyAndSetLeftSide();
  processRightSide();
  processLeftSide();
  delay(10);//repeat every 10 milliseconds
}
//---------------------------------------------------
void initPins(){
  pinMode(pinRightMotorDirectionIn3, OUTPUT);
  pinMode(pinRightMotorDirectionIn4, OUTPUT);
  pinMode(pinRightMotorSpeed, OUTPUT);
  pinMode(pinRightBumper, INPUT_PULLUP);
  pinMode(pinLeftMotorDirectionIn1, OUTPUT);
  pinMode(pinRightMotorDirectionIn2, OUTPUT);
  pinMode(pinLeftMotorSpeed, OUTPUT);
  pinMode(pinLeftBumper, INPUT_PULLUP);
}
void startMotors(){
  runRightMotorForward();
  runLeftMotorForward();
}
void processRightSide(){
  if(countDownWhileMovingToRight <= 0)//checks if counter was NOT ran when bumper had been pressed
    return;
  //otherwise - counter is counting down (as a delay) while the right motor is moving backward
  countDownWhileMovingToRight--;//decrease the counter if it WAS ran when bumper had been pressed
  if(countDownWhileMovingToRight <= 0)//if the running counter got down to zero
    runRightMotorForward();//run the right motor forward
}
void processLeftSide(){
  if(countDownWhileMovingToLeft <= 0)
    return;
  countDownWhileMovingToLeft--;
  if(countDownWhileMovingToLeft <= 0)
    runLeftMotorForward();
}
void verifyAndSetRightSide(){
  if(checkBumperIsNotPressed(pinRightBumper) //checks if right bumper has NOT been pressed
  )
    return;
  if(checkCounterIsNotSet(countDownWhileMovingToRight))//if the counter is not yet counting down
    runRightMotorBackward();//run the right motor backward
  countDownWhileMovingToRight = turnRightTimeout;//set the counter to maximum value to start it counting down
}
void verifyAndSetLeftSide(){
  if(checkBumperIsNotPressed(pinLeftBumper) //checks if left bumper has NOT been pressed
  )
    return;
  if(checkCounterIsNotSet(countDownWhileMovingToLeft))//if the counter is not yet counting down
    runLeftMotorBackward();//run the right motor backward
  countDownWhileMovingToLeft = turnLeftTimeout;//set the counter to maximum value to start it counting down
}
bool checkCounterIsNotSet(int counter){
  return counter <= 0;
}
bool checkBumperIsNotPressed(int pinBumper){
  return digitalRead(pinBumper) == HIGH;
}
void runRightMotorForward(){
  runMotorForward(pinRightMotorDirectionIn3,pinRightMotorDirectionIn4,pinRightMotorSpeed);
}
void runLeftMotorForward(){
  runMotorForward(pinLeftMotorDirectionIn1,pinRightMotorDirectionIn2,pinLeftMotorSpeed);
}
void runRightMotorBackward(){
  runMotorBackward(pinRightMotorDirectionIn3,pinRightMotorDirectionIn4,pinRightMotorSpeed);
}
void runLeftMotorBackward(){
  runMotorBackward(pinLeftMotorDirectionIn1,pinRightMotorDirectionIn2,pinLeftMotorSpeed);
}
void runMotorForward(int pinMotorDirection1,int pinMotorDirection2,int pinMotorSpeed){
  digitalWrite(pinMotorDirection1, true); //set direction forward
  digitalWrite(pinMotorDirection2, true);
  digitalWrite(pinMotorSpeed, false); //set max speed forward
}
void runMotorBackward(int pinMotorDirection1,int pinMotorDirection2,int pinMotorSpeed){
  digitalWrite(pinMotorDirection1, false); //set direction backward
  digitalWrite(pinMotorDirection2, false);
  digitalWrite(pinMotorSpeed, true); //set max speed backward
}

