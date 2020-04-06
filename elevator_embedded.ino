#include "HX711.h"
#include <Servo.h> 

#define PF0 A0 //button
#define PF1 A1
#define PF2 A2
#define PF3 A3 
#define PF4 A4 
#define PA0 22
#define PA1 23
#define PA2 24
#define PA3 25

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

int e0,e1,e2,e3,e4,f0,f1,f2,f3;
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

pinMode(INPUT,PA0);
pinMode(INPUT,PA1);
pinMode(INPUT,PA2);
pinMode(INPUT,PA3);


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

f0= digitalRead(PA0 ); //requst up floor 1
f1= digitalRead(PA1); //requst down floor 3
f2= digitalRead(PA2);//requst up floor 2
f3= digitalRead(PA3); //requst down floor 2
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
//button_7seg();
lilac();
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
      myservo2.write(pos);
   }
  void servofloor2(){
      pos = 93;
      myservo2.write(pos);
   }
void servofloor3(){
      pos = 180;
      myservo2.write(pos);
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
    {	//int kk=1;
        Serial.println("OPEN -PRESS");
	servoOpen();
	delay(5000);
	weight();
    }
 else if (e0 == 1 && e1 == 1) //button open
    {// int kk=2;
       Serial.println("OPEN -NOT PRESS");
       servoClose();
       weight();
    }
   else if (e0 == 1 && e1== 0 ) //button close  
   {// int kk=3;
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
    /*-----------------------------------Press------------------------------------*/
void chosefloor(){
/*while(e2==1 || e3==1 || e4==1 || f0==1 || f1==1 || f2==1 || f3==1){
   Serial.println("PREEEEEEEEESSSSSSSS");
}
*/
   if(e2==0 && e3 == 1 && e4==1 ){
   Serial.println("Floor 1");
   servofloor1();
   }
      if(e2==1 && e3 == 0 && e4==1){
   Serial.println("Floor 2");
   servofloor2();
   }
      if(e2==1 && e3 == 1 && e4==0){
   Serial.println("Floor 3");
   servofloor3();
   }
   }
   
void requestfloor(){
      if(f0==0){
   Serial.println("floor 1 req up");
   }
      if(f1==0){
   Serial.println("floor 3 req down ");
   }
      if(f2==0){
   Serial.println("floor 2 req up");
   }
      if(f3==0){
   Serial.println("floor 2 req down");
   }

   }
   
