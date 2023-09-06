#define VCC_PIN 13
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define GROUND_PIN 10
#define MAX_DISTANCE 200

long duration;
int distance;
#include <Servo.h>

Servo myservo;

int pos = 0;
int record = 1;

void setup() 
{
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(GROUND_PIN, OUTPUT);
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(GROUND_PIN, LOW);
  digitalWrite(VCC_PIN, HIGH);
  myservo.attach(9);
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(20);

  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  if(distance > MAX_DISTANCE)
  {
    distance = MAX_DISTANCE;
  }

  if(distance <= 15)
  {
    delay(3000);

    close();
  
    delay(10000);

    open();

    delay(1000);  
   }
  
  Serial.print("Distance: ");
  Serial.println(distance);
}

void close()
{
  for(pos = 30; pos <= 110; pos += 1)
  {
    myservo.write(pos);
    delay(20);
  }
}

void open()
{
  for(pos = 110; pos >= 30; pos -= 1)
  {
    myservo.write(pos);
    delay(20);
  }
}

void read()
{
  while(distance <= 13)
  {
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(20);

    digitalWrite(TRIGGER_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    if(distance > MAX_DISTANCE)
    {
      distance = MAX_DISTANCE;
    }

    Serial.print("Distance: ");
    Serial.println(distance);
  }
}








