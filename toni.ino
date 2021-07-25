#include <Servo.h>
#include <Wire.h>
#define dirPin 2  // pin yang terhubung ke DIR+ motor driver
#define stepPin 3 // pin yang terhubung ke PUL+ motor driver
#define relayPin 8
#define servoPin 9
#define echoPin 6
#define trigPin 7

Servo myservo;

int distance = 0;
long duration;

bool seeding = false;
int pos = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayPin, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(0);

  digitalWrite(dirPin, HIGH);
}
void loop()
{
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(100);

  if (distance < 5 && distance != 0)
  {
    for (int i = 0; i <= 18; i++)
    {
      if (i >= 18)
      {
        for (int x = 0; x < 8000; x++)
        {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(200);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(200);
        }
      }
      else
      {
        for (int x = 0; x < 1600; x++)
        {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(200);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(200);
        }

        for (pos = 0; pos <= 180; pos += 1)
        { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos); // tell servo to go to position in variable 'pos'
          delay(1);           // waits 15ms for the servo to reach the position
        }
        delay(1000);
        digitalWrite(relayPin, LOW);
        for (pos = 180; pos >= 0; pos -= 1)
        {                     // goes from 180 degrees to 0 degrees
          myservo.write(pos); // tell servo to go to position in variable 'pos'
          delay(15);          // waits 15ms for the servo to reach the position
        }
        delay(1000);
        digitalWrite(relayPin, HIGH);
      }
    }
  }
}

void receiveEvent(int bytes)
{
  distance = Wire.read(); // receive byte as an integer
  // Serial.println(distance); // print the integer
}
