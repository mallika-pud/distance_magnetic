#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/*
  การต่อขาจอ LCD กับ UNO
  VCC - 5V
  GND - GND
  SDA - A4
  SCL - A5

  การต่อขา Ultrasonic กับ UNO
  VCC - 5V
  GND - GND
  Trig - 12
  Echo - 11

*/
LiquidCrystal_I2C lcd(0x27, 20, 4);  // ตั้งค่า I2C address ของ LCD
const int trigPin = 12;
const int echoPin = 11;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("distance");
  lcd.setCursor(0,1);
  lcd.print("voltage");
  lcd.setCursor(0,2);
   lcd.print("B_field");
}

void loop() {
   int distance = Ultrasonic();
  Serial.println("ระยะ " + String(distance) + " cm");
}

int Ultrasonic() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
   int sensorValue = analogRead(A3);
  
  float voltage = sensorValue * (5.0 / 1023.0);
  float B_field= 33.1*(voltage-2.54);
 
  Serial.print("Voltage = ");
  Serial.print(voltage,2);// 4 decimal points
  Serial.println("V");
  Serial.print("B=");
  Serial.print(B_field,2);
  Serial.println("mT");

  lcd.setCursor(0, 0);
  lcd.backlight();
  lcd.print("distance=");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.backlight();
  lcd.print("V=");
  lcd.print(voltage,2);
  lcd.print("V");
  lcd.setCursor(0,2);
  lcd.backlight();
  lcd.print("B=");
  lcd.print(B_field);
  lcd.print("mT");
 
   delay(3000);


}
