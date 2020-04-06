#include "HX711.h"
#include <Servo.h> 

#define PF0 A0 //button
#define PF1 A1
#define PF2 A2
#define PF3 A3 
#define PF4 A4 
#define PF5 A5
#define PF6 A6
#define PF7 A7

#define PC0 37 //7seg
#define PC1 36
#define PC2 35
#define PC3 34
#define PC4 33
#define PC5 32
#define PC6 31
#define PC7 30

#define PB4 10 //servo
#define PB5 11

#define DOUT  53 //loadcell
#define CLK  52
HX711 scale;

Servo myservo1;
Servo myservo2;

int e0,e1,e2,e3,e4,e5,e6,e7;
int pos = 0;  
int X ;
void setup() 
{
Serial.begin(9600);

pinMode(INPUT,PF0 );
pinMode(INPUT,PF1);
pinMode(INPUT,PF2);
pinMode(INPUT,PF3);
pinMode(INPUT,PF4);
pinMode(INPUT,PF5);
pinMode(INPUT,PF6);
pinMode(INPUT,PF7);

 scale.begin(DOUT, CLK);
 
  myservo1.attach(PB4);
  myservo2.attach(PB5); 
  
pinMode(OUTPUT,PC0);
pinMode(OUTPUT,PC1);
pinMode(OUTPUT,PC2);
pinMode(OUTPUT,PC3);
pinMode(OUTPUT,PC4);
pinMode(OUTPUT,PC5);
pinMode(OUTPUT,PC6);
pinMode(OUTPUT,PC7);
}

void loop() 
{
e0= digitalRead(PF0 ); //open 
e1= digitalRead(PF1 ); // close
e2= digitalRead(PF2 ); //floor1
e3= digitalRead(PF3 ); //floor 2
e4= digitalRead(PF4 ); //floor 3
e5= digitalRead(PF5 ); //requst up
e6= digitalRead(PF6 ); //requst down
e7= digitalRead(PF7 ); // emergency ( Not a point)

long reading = scale.read();
X = reading/10000;


//Serial.print(e0);
/*Serial.print(e1);
Serial.print(e2);
Serial.print(e3);
Serial.print(e4);
Serial.print(e5);
Serial.print(e6);
Serial.println(e7);
Serial.println(X);
 delay(300);
 */
//button_door(); 
button_7seg();
}

/*-----------------------------------servo------------------------------------*/
void servoOpen(){
Serial.println("Open Door");
      pos = 180;
      myservo1.write(pos);
   }
void servoClose(){
Serial.println("Close Door");
  pos = -180;
      myservo1.write(pos);
   }
void servofloor1(){
      pos = -180;
      myservo1.write(pos);
   }
  void servofloor2(){
      pos = 93;
      myservo1.write(pos);
   }
void servofloor3(){
      pos = 180;
      myservo1.write(pos);
   }
 /*-----------------------------------XXX------------------------------------*/
void weight(){
   if (X<100)
   {
      servoClose();
      Serial.println("Not overweight");
      delay(500);
   }
   else if (X>100)
   {
      servoOpen();
      Serial.println("Overweight X_X");
      delay(500);
      // function alarm signal
   }
   delay(500);
 }

 void button_door(){
 if (e0 == 0 && e1 == 1 ) //button open
    {
        Serial.println("OPEN -PRESS");
	servoOpen();
	delay(5000);
	weight();
    }
 else if (e0 == 1 && e1 == 1) //button open
    {
       Serial.println("OPEN -NOT PRESS");
       servoClose();
       weight();
    }
   else if (e0 == 1 && e1== 0 ) //button close  
   {
      weight();
      delay(1000);
      Serial.println("CLOSE - PRESS");
    }
  }
  /*-----------------------------------7seg------------------------------------*/
  
 void sevensegment(int num){
  if (num== 1){
 digitalWrite(PC0,LOW); 
 digitalWrite(PC1,HIGH);
 digitalWrite(PC2,HIGH);
 digitalWrite(PC3,LOW);
 digitalWrite(PC4,LOW);
 digitalWrite(PC5,LOW);
 digitalWrite(PC6,LOW);
 digitalWrite(PC7,HIGH);
 } 
  if (num== 2){
 digitalWrite(PC0,HIGH); 
 digitalWrite(PC1,HIGH);
 digitalWrite(PC2,LOW);
 digitalWrite(PC3,HIGH);
 digitalWrite(PC4,HIGH);
 digitalWrite(PC5,LOW);
 digitalWrite(PC6,HIGH);
 digitalWrite(PC7,HIGH);
 } 
  if (num== 3){
 digitalWrite(PC0,HIGH); 
 digitalWrite(PC1,HIGH);
 digitalWrite(PC2,HIGH);
 digitalWrite(PC3,HIGH);
 digitalWrite(PC4,LOW);
 digitalWrite(PC5,LOW);
 digitalWrite(PC6,HIGH);
 digitalWrite(PC7,HIGH);
 } 
   if (num== 9){
 digitalWrite(PC0,LOW); 
 digitalWrite(PC1,LOW);
 digitalWrite(PC2,LOW);
 digitalWrite(PC3,LOW);
 digitalWrite(PC4,LOW);
 digitalWrite(PC5,LOW);
 digitalWrite(PC6,LOW);
 digitalWrite(PC7,LOW);
 } 

}
  /*-----------------------------------7seg------------------------------------*/
  void button_7seg(){
   if (e2==0)
   {   sevensegment(9);
   delay(100);
      sevensegment(1);

   }
   if (e3==0)
   {   sevensegment(9);
   delay(100);
      sevensegment(2);
   }
   if (e4==0)
   {   sevensegment(9);
   delay(100);
      sevensegment(3);
   }
  }
  
