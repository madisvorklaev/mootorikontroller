const int goRelayPin = 3;
const int contactorPin = 4;
const int goPressedPin = 5;
const int redLed = 9;
const int greenLed = 10;
const int blueLed = 11;
const int contactorLed = 12;

int goEngaged;
int goPressed;
int contactorEngaged;
int ledState;
int ledColor;

unsigned long previousMillis = 0;
const long interval = 500;

bool blinked;

void setup() {
  pinMode(goRelayPin, INPUT);
  pinMode(contactorPin, INPUT);
  pinMode(goPressedPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(contactorLed, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  blinked = false;
  readPins();
  while(contactorEngaged == LOW && goEngaged == LOW){
    if(goPressed == HIGH){
      ledColor = greenLed;
      Serial.println("GO active");
    }
    else if(goPressed == LOW){
      ledColor = blueLed;
      Serial.println("LINK active");
    }
    blink();
    readPins();
  }
    digitalWrite(ledState, LOW);
    
  if(contactorEngaged == LOW && goEngaged == HIGH){
    delay(100);
    Serial.println("Delay");
    contactorEngaged = digitalRead(contactorPin);
    if(contactorEngaged == LOW){
      digitalWrite(contactorLed, HIGH);
      Serial.println("HALT");
    }
    else{
      Serial.println("GO incative");
      ledState = LOW;
      digitalWrite(redLed, ledState);
      digitalWrite(greenLed, ledState);
      digitalWrite(blueLed, ledState);
      digitalWrite(contactorLed, ledState);
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
