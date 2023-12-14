#include <LiquidCrystal.h>
const int analogInPin = A0;
double calibValue[10];
double sensorValue[10];
double result;
double avgsensor;
char j;
unsigned long previousMillis2 = 0;
unsigned long starttime = 0;
unsigned long previousMillis1 = 0;      
unsigned long sampleinterval = 1000;
unsigned long sensorinterval = 5000; 
unsigned long time=0;
double mistlevelprcnt=0; //mist level 0-20% will generate inefficient control 
double fullmist=130;
double ontime;
double setvalue=mistlevelprcnt*fullmist/100;
int satlimit=300000;
const int rs = 4, en = 5, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  delay(5000);
  lcd.setCursor(0,0);
  lcd.print("Initializing...");
  delay(5000);
  Serial.println("Calibrating....");
  for (j = 0; j < 20; j++) {
    calibValue[j] =analogRead(analogInPin) ;
    lcd.setCursor(0,1);
    lcd.print(analogRead(analogInPin));
    delay(500);
  }

  result = 0;
  for (j = 10; j <20; j++) {
    result = result + calibValue[j]; // add them up
  }
  result = result / 10; 
  Serial.println("Calibration Value=");
  Serial.println(result);
  lcd.setCursor(0,1);
  lcd.print("calib value");
  lcd.print(result);
  delay(5000);
  Serial.println("Calibration complete!");
  
  lcd.clear();
}

void loop() {
  time = millis();
  sense();
}


void sense () {
  if (time - previousMillis1 >= sampleinterval) {
        previousMillis1 = time;
        for (j = 0; j <= 10; j++) {
            sensorValue[j] =analogRead(analogInPin) ;
        }
    }
    avgsensor=0;
    for (j = 0; j < 10; j++) {
    avgsensor = avgsensor + sensorValue[j]; // add them up
    }
    avgsensor = avgsensor / 10; 

  if (time - previousMillis2 >= sensorinterval) {
    previousMillis2 = time;
    Serial.println(avgsensor);
    lcd.setCursor(1,0);
    lcd.print(avgsensor);
    
  }
}