# Traffic-Light-Control-System Using Arduino

## About This Project And How It Works
This project is to develop a traffic light control system to help control the traffic situation at a crossroad automatically. One traffic light for each direction of the crossroad. Each traffic light consists of three LED’s (Red, Yellow and Green). 
One traffic light is green from the start and switch interchangeably among the others after a predefined time to allow or stop traffic flow. There is also a pedestrian signal which is controlled by two pushbuttons; one at each side of the road. When one of the pushbuttons is pressed, the system checks if the pedestrian has waited for 5 seconds, then the vehicle traffic lights turn red to stop all vehicle movements and the pedestrian traffic turns green after ‘pedestrianSafeWaitTime’ of 3 seconds has elapsed when all vehicles have stopped. A beeper beeps to signal how much time is left for the pedestrians to cross. The pedestrian traffic turns red when the crossing time elapses, and the vehicle traffic turns green to allow the traffic flow.
For simplicity sake, two signals will be implemented(one vertical lane signal and one horizontal).

## Components Required
The components required for this project are as follows;


•	Arduino UNO

•	Breadboard full+ (1 piece)

•	220 ohm resistors (12 pieces)

•	Red LEDs 5mm (4 pieces)

•	Yellow LEDs 5mm (2 pieces)

•	Green LEDs 5mm (4 pieces)

•	Jumper wires (4 red, 2 yellow, 4 green, 1 brown, 3 blue, 14 black)

•	Piezo buzzer (1 piece)

•	PushButton Switch 12mm (2 pieces)



1.	Arduino UNO

![ArduinoUNO](https://user-images.githubusercontent.com/84599965/119560815-b3936680-bda4-11eb-8997-3788f133affe.png)


2.	Breadboard (1 piece)

![breadBoard](https://user-images.githubusercontent.com/84599965/119561904-09b4d980-bda6-11eb-9a28-4a2b0657d226.png)



3.	220 ohm resistors (12 pieces)

 ![resistor220](https://user-images.githubusercontent.com/84599965/119196215-1bd10800-ba86-11eb-880a-e007bb51c061.png)


4.	Red LEDs (4 pieces)

 ![RedLED](https://user-images.githubusercontent.com/84599965/119196252-29868d80-ba86-11eb-86ea-fc7b9b0e5dbd.png)


5.	Yellow LEDs (2 pieces)

 ![YellowLED](https://user-images.githubusercontent.com/84599965/119196279-2f7c6e80-ba86-11eb-8075-7a1e7317b30a.png)


6.	Green LEDs (4 pieces)

 ![GreenLED](https://user-images.githubusercontent.com/84599965/119196295-37d4a980-ba86-11eb-847a-478f388bb49c.png)
 


7.	Jumper wires (4 red, 2 yellow, 4 green, 1 brown, 3 blue, 14 black)

 ![jumperWire](https://user-images.githubusercontent.com/84599965/119196306-3c995d80-ba86-11eb-8be9-9907255dee50.png)
 


8.	Piezo buzzer/beeper (1 piece)

 ![Beeper](https://user-images.githubusercontent.com/84599965/119196326-44590200-ba86-11eb-8e4c-eed7d68a961a.png)
 


9.	PushButton Switch 12mm (2 pieces)

 ![pushButton](https://user-images.githubusercontent.com/84599965/119196347-4d49d380-ba86-11eb-827d-63ea2196317b.png)



## Circuit Diagram
The controller circuit consists of 16 LEDs. Each vehicle signal has 3 LEDs (Red, Yellow and Green). The pedestrian signal also consists of 4 LEDs and 2 pushbuttons. Each LED is connected in series with 220 ohm resistor to limit the current flowing through the LEDs. The current expected to flow through the components are13.6mA (3V, 220ohms).

![CircuitDigram2](https://user-images.githubusercontent.com/84599965/119557418-762cda00-bda0-11eb-99bf-2419e9463774.png)


##Souce code
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
  if (pedWaiting == 1&& (millis() - pedButtonPressedTime) > pedWaitTime) {  //  If the button is pressed
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
