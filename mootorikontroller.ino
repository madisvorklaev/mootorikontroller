#define DEBUG 1

#include <LiquidCrystal.h>

const int goRelayPin = 6;
const int contactorPin = 7;
const int goPressedPin = 8;
const int redLed = 9;
const int greenLed = 10;
const int blueLed = 13;
//const int contactorLed = 12;

int goEngaged;
int goPressed;
int contactorEngaged;
int ledState;
int ledColor;

unsigned long previousMillis = 0;
const long interval = 500;

bool blinked;

String message;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(goRelayPin, INPUT);
  pinMode(contactorPin, INPUT);
  pinMode(goPressedPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
//  pinMode(contactorLed, OUTPUT);

  #ifdef DEBUG
  Serial.begin(9600);
  #endif

  lcd.begin(16, 2);
  lcd.print("HOIST CONTROLLER");
}

void loop() {
  blinked = false;
  readPins();
  while(contactorEngaged == LOW && goEngaged == LOW){
    if(goPressed == HIGH){
      ledColor = greenLed;
      lcd.clear();
      message = "GO active";
      print();
    }
    else if(goPressed == LOW){
      ledColor = blueLed;
      message = "LINK active";
      print();
    }
    blink();
    readPins();
  }
    digitalWrite(ledState, LOW);
    
  if(contactorEngaged == LOW && goEngaged == HIGH){
    delay(100);
    message = "Delay";
      print();
    contactorEngaged = digitalRead(contactorPin);
    if(contactorEngaged == LOW){
      digitalWrite(redLed, HIGH);
      message = "HALT";
      print();
    }
    else{
      lcd.clear();
      message = "GO inactive";
      print();
      ledState = LOW;
      digitalWrite(redLed, ledState);
      digitalWrite(greenLed, ledState);
      digitalWrite(blueLed, ledState);
//      digitalWrite(contactorLed, ledState);
    }
  }
  
}

void readPins() {
  goEngaged = digitalRead(goRelayPin);
  contactorEngaged = digitalRead(contactorPin);
  goPressed = digitalRead(goPressedPin);
}

void blink() {
  if(blinked == false){
    ledState = HIGH;
    digitalWrite(ledColor, ledState);
    blinked = !blinked;
  }
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(ledColor, ledState);
  }
}

void print() {
  lcd.setCursor(0, 1);
  lcd.print(message);
  #ifdef DEBUG
  Serial.println(message);
  #endif
}
