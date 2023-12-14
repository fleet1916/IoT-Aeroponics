
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x3F for a 16 chars and 2 line display

const byte rows = 4; //four rows
const byte cols = 4; //three columns
char keys[rows][cols] = {
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'}
};
byte rowPins[rows] = {46,48,50,52}; //connect to the row pinouts of the keypad
byte colPins[cols] = {38,40,42,44}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );


int inputmod=0;
String input;
String output;
String mask;
String ont ="00";
String offt= "00";
String strpct="000";
int mode = 3;
int mod = 2;
int state=LOW;
String command;
String sep ="x";

int station=0;
int wifi=0;
int sub=0;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.print("Welcome!");
  delay(1000);
  lcd.setCursor(11,2);
  lcd.print("stand by ");  


}

void loop() {
  char key = keypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("Station:");
  lcd.setCursor(10,0);
  lcd.print("Mode:");

  input=String(key);

  if (input == "a") {
    inputmod=1;
  } else if (input == "b") {
    inputmod=2;
  } else if (input == "c") {
    inputmod=3;
  } 
  if (inputmod == 1 || inputmod == 2 || inputmod ==3 ) {
    output=output+input;
  } 
  if (input == "#") {
    output.remove(0,1);
    int l = output.length();
    output.remove(l,1);
    if (inputmod ==1) {
      station=output.toInt();
    } else if (inputmod == 2) {
      mode=output.toInt();
    } else if (inputmod == 3) {
      if (mode==1) {
        ont=output.substring(0,2);
        offt=output.substring(3,5);
      } else if (mode==2) {
        strpct=output.substring(0,3);
        
      } else if (mode==3) {
        
        if (state == LOW) {
          state = HIGH;
          mod=3;
          } else {
          state = LOW;
          mod=2;
          }
      }
    } 
    output="";
    inputmod=0;
  }
  if (input == "d") {
    output="";
    inputmod=0;
  }
  lcd.setCursor(8,0);
  lcd.print(station);
  lcd.setCursor(15,0);
  if (mode ==1 ) {
    lcd.print("time ");
    lcd.setCursor(0,1);
    lcd.print("ON t:");
    lcd.setCursor(5,1);
    lcd.print(ont);
    lcd.setCursor(7,1);
    lcd.print("OFF t:");
    lcd.setCursor(13,1);
    lcd.print(offt);
    lcd.setCursor(16,1);
    lcd.print("min");

  } else if (mode ==2) {
    lcd.print("level");
    lcd.setCursor(0,1);
    lcd.print("level:");
    lcd.setCursor(6,1);
    lcd.print(strpct);
    lcd.setCursor(9,1);
    lcd.print("%          ");
  } else if (mode ==3) {
    lcd.print("onoff");
    lcd.setCursor(0,1);
    if (state == LOW) {
      lcd.print("OFF                 ");
    } else {
      lcd.print("ON                  ");
    }
  }
  lcd.setCursor(0,3);
  lcd.print(output+"        ");
  sub=(station-1)%5;
  wifi=(station-1)/5;
  if (mode == 1 || mode ==2) {
    mod=mode-1;
  } 
  command=sub+sep+mod+sep+strpct+sep+offt+sep+ont+sep+wifi;
  if (input == "*") {
    if (key != NO_KEY ){
    if (station <= 50 && station != 0) {
    Serial.println(command);
    lcd.setCursor(11,2);
    lcd.print("sent      ");
    delay(500);
    lcd.setCursor(11,2);
    lcd.print("stand by ");
    } else {
    lcd.setCursor(11,2);
    lcd.print("not avail");
    delay(1000);
    lcd.setCursor(11,2);
    lcd.print("stand by ");

    }

    }
  }
  

  


}


