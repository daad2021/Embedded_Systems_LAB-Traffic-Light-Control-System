# Traffic-Light-Control-System Using Arduino

## About This Project And How It Works
This project is to develop a traffic light control system to help control the traffic situation at a crossroad automatically. One traffic light for each direction of the crossroad. Each traffic light consists of three LED’s (Red, Yellow and Green). 
One traffic light is green from the start and switch interchangeably among the others after a predefined time to allow or stop traffic flow. There is also a pedestrian signal which is controlled by two pushbuttons; one at each side of the road. When one of the pushbuttons is pressed, the system checks if the pedestrian has waited for 5 seconds, then the vehicle traffic lights turn red to stop all vehicle movements and the pedestrian traffic turns green after ‘pedestrianSafeWaitTime’ of 3 seconds has elapsed when all vehicles have stopped. A beeper beeps to signal how much time is left for the pedestrians to cross. The pedestrian traffic turns red when the crossing time elapses, and the vehicle traffic turns green to allow the traffic flow.

## Components Required
The components required for this project are as follows;


•	Arduino Mega 2560

•	Tiny breadboards (5 pieces)

•	220 ohm resistors (17 pieces)

•	Red LEDs 5mm (6 pieces)

•	Yellow LEDs 5mm (4 pieces)

•	Green LEDs 5mm (6 pieces)

•	Jumper wires (6 red, 4 yellow, 5 green, 2 brown, 8 black)

•	Piezo buzzer (1 piece)

•	PushButton Switch 12mm (2 pieces)

•	3V DC Power source


1.	Arduino Mega 2560

 ![ArduinoMega2560](https://user-images.githubusercontent.com/84599965/119196093-f17f4a80-ba85-11eb-84f1-8b7fd20e03e7.png)


2.	Tiny breadboards (5 pieces)

 ![breadBoard](https://user-images.githubusercontent.com/84599965/119196185-0fe54600-ba86-11eb-82cb-a867923e5650.png)


3.	220 ohm resistors (17 pieces)

 ![resistor220](https://user-images.githubusercontent.com/84599965/119196215-1bd10800-ba86-11eb-880a-e007bb51c061.png)


4.	Red LEDs (6 pieces)

 ![RedLED](https://user-images.githubusercontent.com/84599965/119196252-29868d80-ba86-11eb-86ea-fc7b9b0e5dbd.png)


5.	Yellow LEDs (4 pieces)

 ![YellowLED](https://user-images.githubusercontent.com/84599965/119196279-2f7c6e80-ba86-11eb-8075-7a1e7317b30a.png)


6.	Green LEDs (6 pieces)

 ![GreenLED](https://user-images.githubusercontent.com/84599965/119196295-37d4a980-ba86-11eb-847a-478f388bb49c.png)
 


7.	Jumper wires (6 red, 4 yellow, 5 green, 2 brown, 8 black)

 ![jumperWire](https://user-images.githubusercontent.com/84599965/119196306-3c995d80-ba86-11eb-8be9-9907255dee50.png)
 


8.	Piezo buzzer/beeper (1 piece)

 ![Beeper](https://user-images.githubusercontent.com/84599965/119196326-44590200-ba86-11eb-8e4c-eed7d68a961a.png)
 


9.	PushButton Switch 12mm (2 pieces)

 ![pushButton](https://user-images.githubusercontent.com/84599965/119196347-4d49d380-ba86-11eb-827d-63ea2196317b.png)
 



10.	 3V DC Power source

 ![DC source](https://user-images.githubusercontent.com/84599965/119196361-53d84b00-ba86-11eb-9ef7-552667dbdcfb.png)



## Circuit Diagram
The controller circuit consists of 16 LEDs. Each vehicle signal has 3 LEDs (Red, Yellow and Green). The pedestrian signal also consists of 4 LEDs and 2 pushbuttons. Each LED is connected in series with 220 ohm resistor to limit the current flowing through the LEDs. The current expected to flow through the components are13.6mA (3V, 220ohms).

 ![CircuitDiagram](https://user-images.githubusercontent.com/84599965/119196394-60f53a00-ba86-11eb-9b87-b3f52f1547d5.png)

