#include <Servo.h>
#include <Wire.h>
#define dirPin 2  // pin yang terhubung ke DIR+ motor driver
#define stepPin 3 // pin yang terhubung ke PUL+ motor driver
#define relayPin 8
#define servoPin 9

Servo myservo;

int distance = 0;
long duration;

int pos = 0;

void setup()
{
  Wire.begin(4);                // menggunakan bus i2c dengan alamat 4
  Wire.onReceive(receiveEvent); // meregistrasi event

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  myservo.attach(servoPin);
  myservo.write(0); // mengatur servo ke posisi 0 (posisi awal)

  digitalWrite(dirPin, HIGH);   // mengatur arah putaran stepper (HIGH = CCW, LOW = CW)
  digitalWrite(relayPin, HIGH); // mengatur kondisi awal relay
}
void loop()
{
  // menjalankan stepper terus menerus
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(100);

  if (distance < 5 && distance != 0)
  {
    // jika object terdeteksi akan melakukan perulangan 18x menyemai
    for (int i = 0; i <= 18; i++)
    {
      if (i >= 18)
      {
        // setelah lubang terakhir, melakukan gerakan 8000 step agar objek tidak terdeteksi lagi
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
        // bergerak pelan per lubang, dimana jaraknya yaitu sekitar 1650 step
        for (int x = 0; x < 1650; x++)
        {
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(200);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(200);
        }

        for (pos = 0; pos <= 180; pos += 1)
        { // dari 0 derajat ke 180 derajat
          // per stepnya 1 derajat
          myservo.write(pos);
          delay(1); // untuk kecepatan dari 0 ke 180, semakin besar semakin lama
        }
        delay(1000);
        digitalWrite(relayPin, LOW);
        for (pos = 180; pos >= 0; pos -= 1)
        { // dari 180 derajat ke 0 derajat
          // per stepnya 1 derajat
          myservo.write(pos);
          delay(15); // untuk kecepatan dari 180 ke 0, semakin besar semakin lama
        }
        // menghidupkan vacum selama 1 detik
        digitalWrite(relayPin, HIGH);
        delay(1000);
      }
    }
  }
}

void receiveEvent(int bytes)
{
  // membaca nilai sensor ultrasonic dari Arduino 2 melalui i2c
  distance = Wire.read();
}
