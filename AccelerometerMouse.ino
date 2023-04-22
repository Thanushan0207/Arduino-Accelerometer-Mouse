/* Code Name: Arduino Accelerometer Mouse
Author: Thanushan Ambalavanan
Date: 04/05/2022 */

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;

int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
int button1 = 6;
int buttonState1 = 0; 

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(button1, INPUT);
  mpu.initialize();
  if (!mpu.testConnection()) { while (1); }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vx = (gx+15)/150;  
  vy = -(gz-100)/150;
  Mouse.move(vx, vy);
  buttonState1 = digitalRead(button1);
 if (buttonState1 == HIGH) {
    Mouse.press(MOUSE_LEFT);
    delay(100);
    Mouse.release(MOUSE_LEFT);
    delay(200);
  } 
  delay(80);
}