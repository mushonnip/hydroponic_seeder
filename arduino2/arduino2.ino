#include <Wire.h>

// definisi pin sensor ultrasonic
#define echoPin 7 
#define trigPin 6

// definisi variabel
long duration;
int distance; 

void setup()
{
    Wire.begin();
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT);  // Sets the echoPin as an INPUT
    Serial.begin(9600);       // // Serial Communication is starting with 9600 of baudrate speed
}
void loop()
{
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(distance);      // sends one byte
    Wire.endTransmission();
}
