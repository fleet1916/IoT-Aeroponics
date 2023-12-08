# IoT-Aeroponics
An basic IoT solution for aeroponics system control based on Arduino 
This project uses a ESP 8266 to set up WiFi and server to allow the control of multiple aeroponics systems to raise multiple plants. 
The Main Control Terminal (MCT) sends out input command through a WiFi server. All the bucket control station connects and receives the signal from the server to determine the bucket number, mode and control perimeter.  
The bucket control station controls 5 bucket. It can operate the 5 buckets'mist makers separately in time control mode, percentage control mode and on/off mode. It also provide power for the fans that distribute the mist evenly in the buckets as well.                     
Time control mode turns on the mistmaker for X seconds and turn off the mistmaker for Y seconds. X and Y can be input through the MCT. 
Percentage mode set the mist level to a certain IR sensor reading by turning on and off the mist maker . 
This reading is determined by a steady state mist level IR sensor reading multiplied by the percentage input throught he MCT. 
For the on/off mode, the MCT can control the mist maker on/off directly 




