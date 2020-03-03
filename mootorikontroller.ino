const int goPin = 3;
const int contactorPin = 4;
const int goLed = 11;
const int contactorLed = 12;

int goPressed;
int contactorEngaged;
int goLedState = LOW;

unsigned long previousMillis = 0;
const long interval = 500;

bool blinked = false;

void setup() {
  pinMode(goPin, INPUT);
  pinMode(contactorPin, INPUT);
  pinMode(goLed, OUTPUT);
  pinMode(contactorLed, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  blinked = false;
  readPins();
  while(contactorEngaged == LOW && goPressed == LOW){
    Serial.println("GO active");
    blink();
    readPins();
  }
    digitalWrite(goLed, LOW);
    
  if(contactorEngaged == LOW && goPressed == HIGH){
    delay(100);
    Serial.println("Delay");
    contactorEngaged = digitalRead(contactorPin);
    if(contactorEngaged == LOW){
      digitalWrite(contactorLed, HIGH);
      Serial.println("HALT");
    }
    else{
      Serial.println("GO incative");
      digitalWrite(contactorLed, LOW);
    }
  }
  
}

void readPins() {
  goPressed = digitalRead(goPin);
  contactorEngaged = digitalRead(contactorPin);
}

void blink() {
  if(blinked == false){
  goLedState = HIGH;
  digitalWrite(goLed, goLedState);
  blinked = !blinked;
  }
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (goLedState == LOW) {
      goLedState = HIGH;
    } else {
      goLedState = LOW;
    }

    digitalWrite(goLed, goLedState);
  }
}
