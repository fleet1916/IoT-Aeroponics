#include <PID_v1.h>

int wifi=1;

double fullmist=130;
int satlimit=300000;
unsigned long starttime = 0;
unsigned long smplintvl = 1000;
unsigned long snsrintvl = 5000; 
unsigned long pM1 = 0; 
unsigned long pM2 = 0;
char j;

int mistPina=2;
int ledPina=3;
int mistPinb=4;
int ledPinb=5;
int mistPinc=6;
int ledPinc=7;
int mistPind=8;
int ledPind=9;
int mistPine=10;
int ledPine=11;

int calibpin=12;
int pwrpin=13;

const int ira = A1;
const int irb = A2;
const int irc = A3;
const int ird = A4;
const int ire = A5;

int mistStatea;
int mistStateb;
int mistStatec;
int mistStated;
int mistStatee;

double sVa[10];
double cVa[10];
double rslta;
double avgsnsra;
unsigned long pMa3 = 0;
unsigned long pMa4 = 0; 
unsigned long intvla[2];
double mistlevelprcnta=0;
double ontimea;
double setvaluea=mistlevelprcnta*fullmist/100;
int modea = 2;

//Bucket b numbers
double sVb[10];
double cVb[10];
double rsltb;
double avgsnsrb;
unsigned long pMb3 = 0;
unsigned long pMb4 = 0; 
unsigned long intvlb[2];
double mistlevelprcntb=0;
double ontimeb;
double setvalueb=mistlevelprcntb*fullmist/100;
int modeb = 2;

double sVc[10];
double cVc[10];
double rsltc;
double avgsnsrc;
unsigned long pMc3 = 0;
unsigned long pMc4 = 0; 
unsigned long intvlc[2];
double mistlevelprcntc=0;
double ontimec;
double setvaluec=mistlevelprcntc*fullmist/100;
int modec = 2;

double sVd[10];
double cVd[10];
double rsltd;
double avgsnsrd;
unsigned long pMd3 = 0;
unsigned long pMd4 = 0; 
unsigned long intvld[2];
double mistlevelprcntd=0;
double ontimed;
double setvalued=mistlevelprcntd*fullmist/100;
int moded = 2;

double sVe[10];
double cVe[10];
double rslte;
double avgsnsre;
unsigned long pMe3 = 0;
unsigned long pMe4 = 0; 
unsigned long intvle[2];
double mistlevelprcnte=0;
double ontimee;
double setvaluee=mistlevelprcnte*fullmist/100;
int modee = 2;



 
unsigned long time=0;
PID PIDa(&avgsnsra, &ontimea, &setvaluea, 100, 8, 100, DIRECT);
PID PIDb(&avgsnsrb, &ontimeb, &setvalueb, 100, 8, 100, DIRECT);
PID PIDc(&avgsnsrb, &ontimeb, &setvalueb, 100, 8, 100, DIRECT);
PID PIDd(&avgsnsrb, &ontimeb, &setvalueb, 100, 8, 100, DIRECT);
PID PIDe(&avgsnsrb, &ontimeb, &setvalueb, 100, 8, 100, DIRECT);



String strtotal;
String buck;
String mode;
String pct; 
String ont;
String offt;
String id; 
int buc =6;
int mod = 2;
int pc;
int idk;
unsigned long on;
unsigned long off;


char dataStr[100] = "";
char buffer[7];


void setup() {
  Serial.begin(115200);
  //pinMode set up 
    pinMode(mistPina, OUTPUT);
    pinMode(ledPina, OUTPUT);
    pinMode(mistPinb, OUTPUT);
    pinMode(ledPinb, OUTPUT);
    pinMode(mistPinc, OUTPUT);
    pinMode(ledPinc, OUTPUT);
    pinMode(mistPind, OUTPUT);
    pinMode(ledPind, OUTPUT);
    pinMode(mistPine, OUTPUT);
    pinMode(ledPine, OUTPUT);
    pinMode(pwrpin,OUTPUT);
    pinMode(calibpin,OUTPUT);
    digitalWrite(pwrpin,HIGH);
    digitalWrite(calibpin,HIGH);



  //calibration
  for (j = 0; j < 10; j++) {
    cVa[j] =analogRead(ira) ;
    cVb[j] =analogRead(irb) ;
    cVa[j] =analogRead(irc) ;
    cVb[j] =analogRead(ird) ;
    cVa[j] =analogRead(ire) ;
    delay(50);
  }
  rslta = 0;
  rsltb = 0;
  rsltc = 0;
  rsltd = 0;
  rslte = 0;
  for (j = 0; j < 10; j++) {
    rslta = rslta + cVa[j]; 
    rsltb = rsltb+ cVb[j];
    rsltc = rsltc + cVc[j]; 
    rsltd = rsltd+ cVd[j];
    rslte = rslte + cVe[j]; 
  }
  rslta = rslta / 10+55; 
  rsltb = rsltb / 10+40; 
  rsltc = rsltc / 10; 
  rsltd = rsltd / 10; 
  rslte = rslte / 10; 
  delay(1000);
  starttime = millis();

  pM1 = starttime; 
  pM2 = starttime;
  Serial.print("calib value:");
  Serial.println(rslta);


  PIDa.SetOutputLimits(500, satlimit);
  PIDa.SetMode(AUTOMATIC);
  PIDb.SetOutputLimits(500, satlimit);
  PIDb.SetMode(AUTOMATIC);
  PIDc.SetOutputLimits(500, satlimit);
  PIDc.SetMode(AUTOMATIC);
  PIDd.SetOutputLimits(500, satlimit);
  PIDd.SetMode(AUTOMATIC);
  PIDe.SetOutputLimits(500, satlimit);
  PIDe.SetMode(AUTOMATIC);
  digitalWrite(calibpin,LOW);
}

void loop() {
  dataStr[0] = 0;
  command();
  sense();
  time=millis();
  if (buc==0) {
    if (mod==0) {
      modea=0;
    } else if (mod == 1){
      modea=1;
    } else if (mod == 2) {
      modea=2;
    } else if (mod == 3) {
      modea=3;
    }

    mistlevelprcnta=pc;
    intvla [0]=on*1000;
    intvla [1]=off*1000;
  } else if (buc==1) {
    if (mod==0) {
      modeb=0;
    } else if (mod == 1) {
      modeb=1;
    } else if (mod == 2) {
      modeb=2;

    } else if (mod == 3) {
      modeb=3;
    } else if (mod == 4) {
      modeb=4;
    }
    mistlevelprcntb=pc;
    intvlb [0]=on*1000;
    intvlb [1]=off*1000;
  } else if (buc==2) {
    if (mod==0) {
      modec=0;
    } else if (mod == 1) {
      modec=1;
    } else if (mod == 2) {
      modec=2;
    } else if (mod == 3) {
      modec=3;
    } else if (mod == 4) {
      modec=4;
    }
    mistlevelprcntc=pc;
    intvlc [0]=on*1000;
    intvlc [1]=off*1000;
  } else if (buc==3) {
    if (mod==0) {
      moded=0;
    } else if (mod == 1) {
      moded=1;
    } else if (mod == 2) {
      moded=2;

    } else if (mod == 3) {
      moded=3;
    } else if (mod == 4) {
      moded=4;
    }
    mistlevelprcntd=pc;
    intvld [0]=on*1000;
    intvld [1]=off*1000;
  } else if (buc==4) {
    if (mod==0) {
      modee=0;
    } else if (mod == 1) {
      modee=1;
    } else if (mod == 2) {
      modee=2;

    } else if (mod == 3) {
      modee=3;
    } else if (mod == 4) {
      modee=4;
    }
    mistlevelprcnte=pc;
    intvle [0]=on*1000;
    intvle [1]=off*1000;
  }

  if (modea==1) {
    controlmodea();
  } else if (modea==0) {
    timemodea();
  } else if (modea==2) {
    digitalWrite(mistPina,LOW);
    digitalWrite(ledPina,LOW);
  } else if (modea==3) {
    digitalWrite(mistPina,HIGH);
    digitalWrite(ledPina,HIGH);
  }
  if (modeb== 1) {
    controlmodeb();
  } else if (modeb ==0 ) {
    timemodeb();
  } else if (modeb ==2) {
    digitalWrite(mistPinb,LOW);
    digitalWrite(ledPinb,LOW);
  } else if (modeb==3) {
    digitalWrite(mistPinb,HIGH);
    digitalWrite(ledPinb,HIGH);
  }
  if (modec==1) {
    controlmodec();
  } else if (modec==0) {
    timemodec();
  } else if (modec==2) {
    digitalWrite(mistPinc,LOW);
    digitalWrite(ledPinc,LOW);
  } else if (modec==3) {
    digitalWrite(mistPinc,HIGH);
    digitalWrite(ledPinc,HIGH);
  }

  if (moded== 1) {
    controlmoded();
  } else if (moded ==0 ) {
    timemoded();
  } else if (moded==2) {
    digitalWrite(mistPind,LOW);
    digitalWrite(ledPind,LOW);
  } else if (moded==3) {
    digitalWrite(mistPind,HIGH);
    digitalWrite(ledPind,HIGH);
  }
   if (modee==1) {
    controlmodee();
  } else if (modee==0) {
    timemodee();
  } else if (modee==2) {
    digitalWrite(mistPine,LOW);
    digitalWrite(ledPine,LOW);
  } else if (modee==3) {
    digitalWrite(mistPine,HIGH);
    digitalWrite(ledPine,HIGH);
  }




}

void command () {
    while (Serial.available() > 0 ) {
    strtotal  = Serial.readString();    
    id=strtotal.substring(14);
    idk=id.toInt();
    if (idk == wifi) {
    buck=strtotal.substring(0);
    mode=strtotal.substring(2);
    pct=strtotal.substring(4,7);
    ont=strtotal.substring(8,10);
    offt=strtotal.substring(11,13);
    buc=buck.toInt();
    mod=mode.toInt();
    pc=pct.toInt();
    Serial.println(idk);
    Serial.println(buc);
    Serial.println(mod);
    Serial.println(pc);
    on =(unsigned long) ont.toInt();
    off = (unsigned long) offt.toInt();
    Serial.println(on);
    Serial.println(off);
    if ((on == 0 || off == 0 )&& mod==0) {
      mod=2;
    }
    if (pct == 0 && mod == 1) {
      mod=2;
    }
    }
   }

}

void controlmodea () {
    setvaluea=mistlevelprcnta*fullmist/100;
    PIDa.Compute();
    pMa3 = time;
    if (time - pMa3 < ontimea) {
        mistStatea=HIGH;
    } else {
        mistStatea=LOW;
    }
    digitalWrite(mistPina, mistStatea);
    digitalWrite(ledPina,mistStatea);
   
    
}

void controlmodeb () {
    setvalueb=mistlevelprcntb*fullmist/100;
    PIDb.Compute();
    pMb3 = time;
    if (time - pMb3 < ontimeb) {
        mistStateb=HIGH;
    } else {
        mistStateb=LOW;
    }
    digitalWrite(mistPinb, mistStateb);
    digitalWrite(ledPinb,mistStateb);
    if (time - pM2 >= snsrintvl) {
    pM2 = time;
    }

}

void controlmodec () {
    setvaluec=mistlevelprcntc*fullmist/100;
    PIDc.Compute();
    pMc3 = time;
    if (time - pMc3 < ontimec) {
        mistStatec=HIGH;
    } else {
        mistStatec=LOW;
    }
    digitalWrite(mistPinc, mistStatec);
    digitalWrite(ledPinc,mistStatec);
   
    
}

void controlmoded () {
    setvalued=mistlevelprcntd*fullmist/100;
    PIDd.Compute();
    pMd3 = time;
    if (time - pMd3 < ontimed) {
        mistStated=HIGH;
    } else {
        mistStated=LOW;
    }
    digitalWrite(mistPind, mistStated);
    digitalWrite(ledPind,mistStated);
   
    
}

void controlmodee () {
    setvaluee=mistlevelprcnte*fullmist/100;
    PIDe.Compute();
    pMe3 = time;
    if (time - pMe3 < ontimee) {
        mistStatee=HIGH;
    } else {
        mistStatee=LOW;
    }
    digitalWrite(mistPine, mistStatee);
    digitalWrite(ledPine,mistStatee);
   
    
}

void timemodea () {
    digitalWrite(mistPina, mistStatea);
    digitalWrite(ledPina,mistStatea);
    if (time- pMa4 >= intvla[mistStatea]) {
    pMa4 = time;
      if (mistStatea == LOW) {
      mistStatea = HIGH;
      } else {
      mistStatea = LOW;
      }
    }
  }

void timemodeb () {
    digitalWrite(mistPinb, mistStateb);
    digitalWrite(ledPinb,mistStateb);
    if (time- pMb4 >= intvlb[mistStateb]) {
    pMb4 = time;
      if (mistStateb == LOW) {
      mistStateb = HIGH;
      } else {
      mistStateb = LOW;
      }
    }
  }

void timemodec () {
    digitalWrite(mistPinc, mistStatec);
    digitalWrite(ledPinc,mistStatec);
    if (time- pMc4 >= intvlc[mistStatec]) {
    pMc4 = time;
      if (mistStatec == LOW) {
      mistStatec = HIGH;
      } else {
      mistStatec = LOW;
      }
    }
  }

void timemoded () {
    digitalWrite(mistPind, mistStated);
    digitalWrite(ledPind,mistStated);
    if (time- pMd4 >= intvld[mistStated]) {
    pMd4 = time;
      if (mistStated == LOW) {
      mistStated = HIGH;
      } else {
      mistStated = LOW;
      }
    }
  }

void timemodee () {
    digitalWrite(mistPine, mistStatee);
    digitalWrite(ledPine,mistStatee);
    if (time- pMe4 >= intvle[mistStatee]) {
    pMe4 = time;
      if (mistStatee == LOW) {
      mistStatee = HIGH;
      } else {
      mistStatee = LOW;
      }
    }
  }

void sense () {
  if (time - pM1 >= smplintvl) {
        pM1 = time;
        for (j = 0; j < 10; j++) {
            sVa[j] =analogRead(ira)-rslta;
            sVb[j] =analogRead(irb)-rsltb;
            sVc[j] =analogRead(irc)-rsltc;
            sVd[j] =analogRead(ird)-rsltd;
            sVe[j] =analogRead(ire)-rslte;
        }
    }
    avgsnsra=0;
    avgsnsrb=0;
    avgsnsrc=0;
    avgsnsrd=0;
    avgsnsre=0;
    for (j = 0; j < 10; j++) {
    avgsnsra = avgsnsra + sVa[j]; 
    avgsnsrb = avgsnsrb + sVb[j]; 
    avgsnsrc = avgsnsrc + sVc[j]; 
    avgsnsrd = avgsnsrd + sVd[j];
    avgsnsre = avgsnsre + sVe[j]; 
    }
    avgsnsra = avgsnsra / 10; 
    avgsnsrb = avgsnsrb / 10; 
    avgsnsrc = avgsnsrc / 10; 
    avgsnsrd = avgsnsrd / 10; 
    avgsnsre = avgsnsre / 10; 

  if (time - pM2 >= snsrintvl) {
    pM2 = time;


    dtostrf(avgsnsra, 5, 1, buffer);  //5 is minimum width, 1 is precision; float value is copied onto buff
    strcat( dataStr, buffer); //append the converted float
    strcat( dataStr, ", "); //append the delimiter

    dtostrf(avgsnsrb, 5, 1, buffer);  //5 is minimum width, 1 is precision; float value is copied onto buff
    strcat( dataStr, buffer); //append the converted float
    strcat( dataStr, 0); //terminate correctly 
    //Serial.println(dataStr);
   
  }
}