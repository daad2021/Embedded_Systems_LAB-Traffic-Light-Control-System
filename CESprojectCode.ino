const int pedSignalButton = 3; // pedestrian signal/push button
const int pedSignalRed = 6; // pedestrian red light pin
const int pedSignalGreen = 5; // pedestrian green light pin

// variables for vertical signal
const int verticalSignalRed = 13;
const int verticalSignalYellow = 12;
const int verticalSignalGreen = 11;

// variables for horizontal signal
const int horizontalSignalRed = 10;
const int horizontalSignalYellow = 9;
const int horizontalSignalGreen = 8;

const int beeper = 7; // variable beeper/buzzer

// Delay times setting
int carGreenLightDelay = 10000; // green light stays on for 1 minute
int beepNblinkDelay_slow = 500; //blink pedestrian green light and beep every 0.5 seconds
int beepNblinkDelay_fast = 300; //blink pedestrian green light and beep every 0.3 seconds
int pedSafetyDelay = 3000; //
int pedCrossTime = 5000; // time allocated for pedestrians to cross
int yellowDelay = 2000; // time allocated for the yellow ight/signal to stay ON

int pedWaiting = 0;  // variable for the pedestrian waiting state
int carCycle = 0; // variable for counting car signal cycles
int vertSignalTracker = 0; //variable for storing the state of the vertical signal before and after the pedestrian interruption
int horizSignalTracker = 0; //variable for storing the state of the vertical signal before and after the pedestrian interruption

bool buttonState = true;  // variable for storing the pushbutton state.

unsigned long pedButtonPressedTime = 0; // variable to store the time the pedestrian button is pressed
unsigned long lastPedCrossTime = 0;
const unsigned long pedWaitTime = 15000; // how long a pedestrian should wait for the green light after pressing the button

void setup(){
  // Setting the LED pins as OUTPUT
  pinMode(pedSignalRed, OUTPUT);
  pinMode(pedSignalGreen, OUTPUT);
  pinMode(verticalSignalRed, OUTPUT);
  pinMode(verticalSignalYellow, OUTPUT);
  pinMode(verticalSignalGreen, OUTPUT);
  pinMode(horizontalSignalRed, OUTPUT);
  pinMode(horizontalSignalYellow, OUTPUT);
  pinMode(horizontalSignalGreen, OUTPUT);
  
  pinMode(beeper, OUTPUT); //setting the beeper/buzzer as OUTPUT
  pinMode(pedSignalButton, INPUT_PULLUP);  //Setting the Push Button as INPUT and using the internal pullup resistor
  
  attachInterrupt(1, pedRequest, CHANGE);  //Monitoring for interrup to check if button is pressed

 // Setting the initial state of the LED's
 //digitalWrite (verticalSignalGreen, HIGH);
 digitalWrite (horizontalSignalRed, HIGH);
 digitalWrite (pedSignalRed, HIGH);
 } //end of setup function


void loop() {
  /*if vertSignalTask function executed last before the interrupt, then continue from the horizontal signal task*/
//  if (vertSignalTracker == 1){
//    horizSignalTask();
//    vertSignalTracker = 0;
//  }
  
  vertSignalTask(); //calling the vertical lane signal control function call
  
 /*if horizSignalTask function executed last before the interrupt, then continue from the vertical signal task*/
//  if (horizSignalTracker == 1){
//    vertSignalTask();
//    horizSignalTracker = 0;
//  }
  
  horizSignalTask(); //calling the horizontal lane signal control function
  
    //running 2 cycles for cars before pedestrial cross
    //when pedestrian signal button is not pressed
  carCycle += 1;
  if (carCycle == 2){
    pedestrianCross();
    carCycle = 0;
  }
} //End of loop function


//Vertical lane signal change function
void vertSignalTask(){
  if (pedWaiting == 1&& (millis() - pedButtonPressedTime) >= pedWaitTime) {  //If the button is pressed and the waiting time has elapsed
      pedestrianCross();//  Exit main loop and run pedestrianCross() function
      vertSignalTracker = 1;
      lastPedCrossTime = millis();
      pedButtonPressedTime = millis();
  }
  
  digitalWrite(verticalSignalRed, LOW);  //
  if (vertSignalTracker == 1){
    digitalWrite(verticalSignalYellow, HIGH);
    delay(yellowDelay);  // 2 Seconds of Yellow signal
    digitalWrite(verticalSignalYellow, LOW);
  }
  digitalWrite(verticalSignalGreen, HIGH);
  delay(carGreenLightDelay);  // 10 Seconds of Green
  digitalWrite(verticalSignalGreen, LOW);  //
  digitalWrite(verticalSignalYellow, HIGH);
  delay(yellowDelay);  // 2 Seconds of Yellow signal
  digitalWrite(verticalSignalYellow, LOW);  //
  digitalWrite(verticalSignalRed, HIGH);
}

// Horizontal signal control function
void horizSignalTask(){ 
    if (pedWaiting == 1 && (millis() - pedButtonPressedTime) >= pedWaitTime){  //If the button is pressed and the waiting time has elapsed
       pedestrianCross();//  exit the main loop and run pedestrianCross() function
       horizSignalTracker = 1;
       pedButtonPressedTime = millis(); //pedButtonPressedTime gets the current time
    }
  
  digitalWrite(horizontalSignalYellow, HIGH);
  digitalWrite(horizontalSignalRed, LOW);
  delay(yellowDelay);
  digitalWrite(horizontalSignalYellow, LOW);
   
  digitalWrite(horizontalSignalGreen, HIGH);  //
  delay(carGreenLightDelay);  // delay car Green signal ON for 8 Seconds
  digitalWrite(horizontalSignalGreen, LOW);
  digitalWrite(horizontalSignalYellow, HIGH);  //
  delay(yellowDelay); // delay Yellow signal ON for 2 seconds
  digitalWrite(horizontalSignalYellow, LOW); 
  digitalWrite(horizontalSignalRed, HIGH);  //
  digitalWrite(verticalSignalRed, LOW);
  digitalWrite(verticalSignalYellow, HIGH);
  delay(yellowDelay);
  digitalWrite(verticalSignalYellow, LOW);
}

//pedestrian crossing function
void pedestrianCross() {
    digitalWrite(verticalSignalRed, LOW);
    digitalWrite(horizontalSignalRed, LOW);
    
    digitalWrite(verticalSignalYellow, HIGH);
    digitalWrite(horizontalSignalYellow, HIGH);
    delay(pedSafetyDelay);
    digitalWrite(verticalSignalYellow, LOW);
    digitalWrite(horizontalSignalYellow, LOW);
        
    digitalWrite(verticalSignalRed, HIGH);
    digitalWrite(horizontalSignalRed, HIGH);
    delay(pedSafetyDelay);
    digitalWrite (pedSignalGreen, HIGH); 
    digitalWrite (pedSignalRed, LOW);  // Turn on Green Pedestrian Light
    delay (pedCrossTime);  // delay pedestrian green light ON for 5 second before start to blink
    digitalWrite (pedSignalGreen, LOW); 
    digitalWrite(pedSignalButton, LOW);
    
   // Blink the pedestrian green light and beep each 0.5 seconds for 5 times
   // slow blink and beep
  for (int x = 0; x < 5; x++) {
    digitalWrite(pedSignalGreen, HIGH);
    digitalWrite(beeper, HIGH);
    delay(beepNblinkDelay_slow);
    digitalWrite(pedSignalGreen, LOW);
    digitalWrite(beeper, LOW);
    delay(beepNblinkDelay_slow);
  }

  // Blink the pedestrian green light and beep each 0.3 seconds for 5 times
  // fast blink and beep
  for (int i = 0; i < 5; i++) { 
  digitalWrite(pedSignalGreen, HIGH);
  digitalWrite(beeper, HIGH);
  delay(beepNblinkDelay_fast);
  digitalWrite(pedSignalGreen, LOW);
  digitalWrite(beeper, LOW);
  delay(beepNblinkDelay_fast);
  }
  
  digitalWrite(pedSignalRed, HIGH);
  delay(pedSafetyDelay); // Delay for 3 seconds before switching ON green for cars to ensure pedestrian safty
  lastPedCrossTime = millis(); //
  pedWaiting = 0; //reset the pedestrian wait state
  asm volatile ("  jmp 0");  //always begin the cycle from vertical lane signal after pedestrian cross
} // End of pedestrianCross function


//Pedestrian signal button pressed state check function
void pedRequest() {
     buttonState = digitalRead(pedSignalButton);
     if (buttonState == false){
         pedWaiting = 1;  //Pedestrian waiting
         pedButtonPressedTime = millis(); //pedButtonPressedTime gets the current time
  }
} // end of pedRequest function
