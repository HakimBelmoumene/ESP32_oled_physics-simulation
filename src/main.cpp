#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>
#include <iostream>
#include <cmath>

#define WIRE Wire

using namespace std;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);
MPU6050 mpu(Wire);

class Ball{
  public:
    //the variables
    int Vel[2] = {0,0};
    float M=0.35; // mass 
    int g=10; // gravity=10 sue me!!
    int pos[2]; //temporary position variable ig
    int theta =0;


    float get_angle(){
      mpu.update();
      float theta=mpu.getAngleZ();
      return theta;
    }
    void velocity(){
      theta= (get_angle()+90)*3.14159/180;
      Vel[1]= static_cast<int>(M*g*sin(theta));
      Vel[0]= static_cast<int>(M*g*cos(theta));
    }

    void pos_update(){
      if (pos[1]<4){
        pos[1]=4;
      }
      if (pos[1]>60){
        pos[1]=60;
      }
      if (pos[0]<4){
        pos[0]=4;
      }
      if (pos[0]>124){
        pos[0]=124;
      }
      pos[0]+=Vel[0];
      pos[1]+=Vel[1];
    }

    void create_ball(){
      display.clearDisplay();
    
      velocity();
      pos_update();
      
      display.fillCircle(pos[0],pos[1],4,1);
      
      display.display();
      
    }
};
//the variables
// int Vel[2] = {0,0};
// float M=0.35; // mass 
// int g=10; // gravity=10 sue me!!
// int pos[2] = {64,32}; //temporary position variable ig
// int theta =0;

Ball ball1;


Ball ball2;

Ball ball3;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");


  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");
  display.clearDisplay();

 
  // text display tests
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10,10);
  display.println("DUMB ANIMATION");
  display.display(); // actually display all of the above
  delay(500);
  ball1.pos[0]=20;
  ball1.pos[1]=15;

  ball2.pos[0]=10;
  ball2.pos[1]=25;
}

// float get_angle(){
//   mpu.update();
//   float theta=mpu.getAngleZ();
//   return theta;
// }
// void velocity(){
//   theta= (get_angle()+90)*3.14159/180;
//   Vel[1]= static_cast<int>(M*g*sin(theta));
//   Vel[0]= static_cast<int>(M*g*cos(theta));
// }

// void pos_update(){
//   if (pos[1]<4){
//     pos[1]=4;
//   }
//   if (pos[1]>60){
//     pos[1]=60;
//   }
//   if (pos[0]<4){
//     pos[0]=4;
//   }
//   if (pos[0]>124){
//     pos[0]=124;
//   }
//   pos[0]+=Vel[0];
//   pos[1]+=Vel[1];
// }
void loop() {
  


  // display.clearDisplay();
  
  // velocity();
  // pos_update();
  
  // display.fillCircle(pos[0],pos[1],4,1);
  
  // display.display();
  // delay(10);
  ball1.create_ball();
  ball2.create_ball();
  ball3.create_ball();
  

}