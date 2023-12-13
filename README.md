# IoT-Aeroponics
An basic IoT solution for aeroponics system control based on Arduino 
This project uses a ESP 8266 to set up WiFi and server to allow the control of multiple aeroponics systems to raise multiple plants. 
It includes 4 basic types of the station: The Main Control Terminal (MCT), The Bucket Control Station (BCS), Data Collection and Calibration Station (DCS), and In Bucket Stand (IBS). 
A set of system would include 1 MCT, maximum of ( 8 BCS + 40 IBS ) and 1 DCS. 
The Main Control Terminal sends out input command through a WiFi server. All the bucket control station connects and receives the signal from the server to determine the bucket number, mode and control perimeter.

The Bucket Control Station controls 5 bucket. It can operate the 5 buckets'mist makers separately in time control mode, percentage control mode and on/off mode. It also provide power for the fans that distribute the mist evenly in the buckets as well.                     
Time control mode turns on the mistmaker for X seconds and turn off the mistmaker for Y seconds. X and Y can be input through the MCT. 
Percentage mode set the mist level to a certain IR sensor reading by turning on and off the mist maker . 
This reading is determined by a steady state mist level IR sensor reading multiplied by the percentage input throught he MCT. 
For the on/off mode, the MCT can control the mist maker on/off directly 

The Data Collection and Calibration Station have no control authority over mist maker and the fan. It is a interface to record the mist level in the bucket during normal operation and determine the steady state IR sensor reading for calibration purposes, which is necessary for the Percentage mode to work properly. Sensor value A is obtained by reading the sensor value without turning on the mist maker.  Another sensor value B can be obtained by set the bucket control mode to on/off and turn on the mist maker for more than 20 mins. The calibration reading is the absolute value of the difference between A and B. After getting the calibration reading, change the fullmist value to the calibration value for the control mode to operate in its best condition. 

The In Bucket Stand is a stand to host fan and sensor for the controlling and mist distribution purposes. It needs to be connected to the BCS. 

Look for the bill of materials and assembly insturction to make the system and installing libraries in you computer. 
Upload the code in each folder to the corresponding arduino/ESP8266 board to set up the functions of the system




