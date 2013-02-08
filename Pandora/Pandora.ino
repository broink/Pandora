#include <SD.h>

#include <LiquidCrystal.h>
#include <stlib.h>
#include <PS2Keyboard.h>
#include <Time.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;

/*
* The actual GPS tracking programme
*
*
*/

/* Pin-list
1
2 
3 - Keyboard
4 - Keyboard
5 - LCD
6 - LCD
7 - LCD
8 - LCD
9 - Keyboard
10
11 - LCD
12 - LCD
13 - LED

*/

//Initiation
//LCD
LiquidCrystal lcd(12,11,8,7,6,5);

//Keyboard
PS2Keyboard keyboard;
String keyboardString = String(100);

String masterPhoneNumber = "0------085";      //Put in phonebook? Jespers number
String reciverPhoneNumber = masterPhoneNumber;

const int KBDataPin = 9;  //Ignore these to save RAM? No, samesame
const int KBIRQPin =  3;
const int WakeupPin = 4;
// const int RegPin = 2; //Replace with keyboard input, key '*'
const int LEDPin = 13;

//System
const int MAXMEMBERS = 10; 

boolean gsmStatus = false;
int timeSinceReport;
int currentTeam[MAXMEMBERS];
memset(currentTeam,0,MAXMEMBERS);

void setup(){
  Serial.begin(9600);
  delay(1000);
  //Setup LCD and print boot-text
  lcd.begin(16,2);
  lcd.setCursor(1,1);
  lcd.print("Booting...");
  delay(1000); 
  //Setup GSM
  if(gsm.begin(9600)){
    Serial.println("\nstatus=READY");
    gsmStatus = true;
  } else Serial.println("\nstatus=GSMFAIL");
  delay(1000);
  //Setup GPS
  
  delay(1000);
  //Set system time
  
  //Get timedata from GPS
  
  //setTime(hh,mm,ss,dd,mm,yy);
  delay(1000);
  //Set pins and constants
  pinMode(WakeupPin, INPUT);
  
  timeSinceReport = 301;
 // pinMode(RegPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  //Setup keyboard
  keyboard.begin(KBDataPin, KBIRQPin);
  
  //Send SMS to master with boot-verifications stuff
  if(gsmStatus){
    
    //Send it
  } else {
    //blink or warn or something. Do some kind of reset and attempt to reboot
  }
}

void loop(){
  writeLog();
  checkCamp();              //Check if 
  if(WakeupPin == HIGH){     //Check if a team wants to register with the box
    regTeam();
  } else if(timeSinceReport > 300){  //Send a report to master every 5 min
    reportToMaster();                //Send the report
    timeSinceReport = 0;             //Reset timer
  }

}

//Menufunctions
void regTeam(){
  lprint("Registrera lag");
  delay(1000);
  String pp = "Antal personer: \n Max ";
  pp.concat(MAXMEMBERS);
  lprint(pp);
  //Print into userfiles of current team the time of loosing the box
  
  int antalpers = keyboard.read();
  memset(currentTeam,0,MAXMEMBERS);
  String rp = "Reg. pers: ";
  for(int i = 0; i < antalpers; i++){
    rp.concat(i+1);
    rp += "/";
    rp.concat(antalpers);
    lprint(rp);
    currentTeam[i]=keyboard.read();
    lprint("ID: "+currentTeam[i]);
  //Check if personal file exists
  //No: Create it. filename = id
  //Yes: print \n+id+" "+time+" "+multiplier+" "+pos
  }
}

void writeLog(){
  //Where we are
  //What time is it
  //Who owns the box
}

void reportToMaster(){
  
}

//Helpfunctions
void checkCamp(){
  
}

void lprint(String text){
  //First, format the text
  lcd.autoscroll();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(text.substring(0,text.indexOf("\n")));
  lcd.setCursor(0,1);
  lcd.print(text.substring(text.indexOf("\n")+2));
}
