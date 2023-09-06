#include <Servo.h>;
Servo myservo;

long prevmillis = 0;
long interval = 3000;
int toClose = 0;
int toOpen = 0;
int switchClosed = 0;
int clawClosed = 0;
void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
  myservo.attach(9);
  myservo.write(0);
  //prevmillis = millis();
}

void loop() {
  //Serial.println(digitalRead(10));
  delay(250);
  if (digitalRead(10) && switchClosed) {
    switchClosed = 0;
    toOpen = 1;
    delay(10);
    Serial.println("|| switch went from closed to open (lifted up) ||");
  }
  if (!digitalRead(10) && !switchClosed) {
    if (clawClosed) {
      toOpen = 1;
      toClose = 0;
    } else {
      toOpen = 0;
      toClose = 1;
    }
    switchClosed = 1;
    setTimer();
    Serial.println("-- switch went from open to closed --");
  }
  if (interval < (millis() - prevmillis)) {
    Serial.println(interval);
    //Serial.println();
    if (toClose) {
      Serial.println("! closing !");
      closeClaw();
      toClose = 0;
      toOpen = 0;
      clawClosed = 1;
    }
    if (toOpen && !digitalRead(10)) {
      Serial.println("! opening !");
      openClaw();
      toOpen = 0;
      toClose = 0;
      clawClosed = 0;
    }
  }
}
void setTimer(){
  prevmillis = millis();
}
void closeClaw(){
  for(int pos = 0; pos <= 180; pos += 1){
    myservo.write(pos);
    delay(15);
  }
}

void openClaw(){
  for(int pos = 180; pos >= 0; pos -= 1){
    myservo.write(pos);
    delay(15);
  }
}
