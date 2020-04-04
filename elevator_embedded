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

}

/*
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
 */
 
void servofloor1(){
      pos = -180;
      myservo1.write(pos);
   }
void servofloor3(){
      pos = 180;
      myservo2.write(pos);
   }
