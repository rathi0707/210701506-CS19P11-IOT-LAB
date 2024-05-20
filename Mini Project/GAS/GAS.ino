#include <LiquidCrystal.h> 
#include <SoftwareSerial.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
SoftwareSerial gsmModule(9, 10); 

int gasPin = A0; 
int ledPin = 13; 
int buzzerPin = 7;
int exhaustFanPin = 6; 

void setup() {
  pinMode(gasPin, INPUT); 
  pinMode(ledPin, OUTPUT); 
  pinMode(buzzerPin, OUTPUT); 
  pinMode(exhaustFanPin, OUTPUT); 

  lcd.begin(16, 2); 
  lcd.print("Gas Detector"); 

  gsmModule.begin(9600); 
}

void loop() {
  int gasValue = analogRead(gasPin); 

  if (gasValue > 500) { 
    digitalWrite(ledPin, HIGH); 
    digitalWrite(buzzerPin, HIGH); 
    digitalWrite(exhaustFanPin, HIGH); 
    lcd.setCursor(0, 1); 
    lcd.print("Gas Detected!"); 
    sendSMS("Gas detected! Please evacuate."); 
    makeCall("+918838762655"); 
    delay(10000); 
  } else {
    digitalWrite(ledPin, LOW); 
    digitalWrite(buzzerPin, LOW); 
    digitalWrite(exhaustFanPin, LOW); 
    lcd.setCursor(0, 1); 
    lcd.print("No Gas Detected"); 
  }

  delay(1000); 
}

void sendSMS(String message) {
  gsmModule.print("AT+CMGF=1\r"); 
  delay(1000);
  gsmModule.println("AT+CMGS=\"+918838762655\""); 
  delay(1000);
  gsmModule.println(message); 
  delay(1000);
  gsmModule.println((char)26); 
  delay(1000);
}

void makeCall(String phoneNumber) {
  gsmModule.println("ATD" + phoneNumber + ";"); r
  delay(20000); 
  gsmModule.println("ATH"); 
}