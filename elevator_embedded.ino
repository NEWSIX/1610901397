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
int veil=0,polar=0,ris,fa=2,fb;

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

f0= digitalRead(PA0 ); //request up floor 1
f1= digitalRead(PA1); //request down floor 3
f2= digitalRead(PA2);//request up floor 2
f3= digitalRead(PA3); //request down floor 2
long reading = scale.read();
X = reading/10000;


//button_door(); 
//button_7seg();
//button_door();
//servoClose();
button_floor();
requsetfloor();
compare_floor();

button_door();
compare_door();


}

 /*-----------------------------------Press------------------------------------*/

 void button_door(){
 if (e0 == 0 && e1 == 1 ) //button open
    {	veil=1;
    }
 else if (e0 == 1 && e1 == 1) //button open
    {	veil=2;

    }
   else if (e0 == 1 && e1== 0 ) //button close  
   {	veil=3;

    }
  }
  
void button_floor(){
   if(e2==0 && e3 == 1 && e4==1 ){
   polar=1;
   //Serial.println("Floor 1");
   }
   if(e2==1 && e3 == 0 && e4==1){
    polar=2;
   //Serial.println("Floor 2");
   }
    if(e2==1 && e3 == 1 && e4==0){
    polar=3;
   //Serial.println("Floor 3");
   }
   if(e2==1 && e3 == 1 && e4==1){
   polar=0;
   int ris=0;
   }
}

void requestfloor(){
      if(f0==0){
      fb=1;
   Serial.println("floor 1 req up");
   }
      if(f1==0){
      fb=2;
   Serial.println("floor 3 req down ");
   }
      if(f2==0){
      fb=3;
   Serial.println("floor 2 req up");
   }
      if(f3==0){
      fb=4;
   Serial.println("floor 2 req down");
   }
  }
/*-----------------------------------servo------------------------------------*/
void servoOpen(){
Serial.println("Open Door");
Serial.println(" ");
      pos = 180;
      myservo1.write(pos);
   }
void servoClose(){
Serial.println("Close Door");
Serial.println(" ");
  pos = -180;
      myservo1.write(pos);
   }
   
   //****//
   
void servofloor1(){
      fa=1;
      pos = -180;
      myservo2.write(pos);
      Serial.println("Floor : 1");
      Serial.println(" ");
   }
  void servofloor2(){
      fa=2;
      pos = 93;
      myservo2.write(pos);
      Serial.println("Floor : 2");
      Serial.println(" ");
   }
void servofloor3(){
      fa=3;
      pos = 180;
      myservo2.write(pos);
      Serial.println("Floor : 3");
      Serial.println(" ");
   }
 /*-----------------------------------Weight------------------------------------*/
void weight(){
while(X>100){
      long reading = scale.read();
      X = reading/10000;
       servoOpen();
      Serial.println("Overweight X_X");
      delay(500);
      // function alarm signal
   }

  // if (X<100)
   //{
      servoClose();
      Serial.println("Not overweight");
      delay(500);
      }
   //}
  /* else if (X>100)
   {
      servoOpen();
      Serial.println("Overweight X_X");
      delay(500);
      // function alarm signal
   }*/
 

  /*-----------------------------------7seg Display------------------------------------*/
  
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
 /*void button_7seg(){
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
 /*
  /*-----------------------------------Compared------------------------------------*/
void compare_door(){
      if(veil ==1){
	Serial.println("OPEN -PRESS");
	servoOpen();
	delay(5000);
	weight();
      }
      else if(veil ==2){
       Serial.println("OPEN -NOT PRESS");
       servoClose();
       weight();
      }
      else if(veil ==3){
      servoClose();
      delay(500);
      weight();
      delay(1000);
      Serial.println("CLOSE - PRESS");
      }
 }
 
 //**//
 
void  compare_floor(){
       if (polar == 1 ){
	 if(fa==2){
	 floor2to1();
	 }
	 if(fa==3){
	 floor3to1();
	 /*floor3to2(); 
	 if(f3==0){
	    Serial.println("Floor 2 request up");
	    servoOpen();
	    delay(1000);
	    servoClose();
	     }
	 floor2to1();*/
	 }
	} 
	 
	if (polar == 2 ){
	 if(fa==1){
	 floor1to2();
	 }
	 if(fa==3){
	 floor3to2();
	 } 
	} 
	if (polar == 3 ){
	 if(fa==1){
	    floor1to3();
	    /*floor1to2();
	    if(f2==0){
	    Serial.println("Floor 2 request down");
	    servoOpen();
	    delay(1000);
	    servoClose();
	     }
	    floor2to3();*/
	 }
	 if(fa==2){
	    floor2to3();
	 }
	} 

      
}
void requsetfloor(){
   if(f0==0){
      if(fa==1){
	 servoOpen();
	 delay(500);
	 servoClose();
      }
       if(fa==2){
	 floor2to1();
       }
       if(fa==3){
       floor3to1();
       }
   }
   
   if(f1==0){
      if(fa==1){
	     floor1to3();
	 }
	  if(fa==2){
	     floor2to3();
	  }
	  if(fa==3){
	  servoOpen();
	  delay(500);
	  servoClose();
	  }
   }
   
   if(f2==0 || f3==0){
      if(fa==1){
	 floor1to2();
	 }
	  if(fa==2){
	     servoOpen();
	     delay(500);
	     servoClose();
	  }
	  if(fa==3){
	    floor3to2();
	  }
   }
}


 /*-----------------------------------FLOOR MOVE-----------------------------------*/
 void floor2to1(){
 weight();
   Serial.println("Floor 2 to 1");
   servofloor1();
   servoOpen();
   delay(500);
   servoClose();
 }
 void floor2to3(){
 weight();
   Serial.println("Floor 2 to 3");
   servofloor3();
   servoOpen();
   delay(500);
   servoClose();
 }

 void floor3to2(){
 weight();
   Serial.println("Floor 3 to 2");
   servofloor2();
   servoOpen();
   delay(500);
   servoClose();
 }
 void floor1to2(){
 weight();
   Serial.println("Floor 1 to 2");
   servofloor2();
   servoOpen();
   delay(500);
   servoClose();
 }
 
 //**//

 void floor1to3(){
 weight();
   Serial.println("Floor 1 to3");
   servofloor2();
   delay(1000);
   if(f2==0){
      Serial.println("Floor 2 request up");
      servoOpen();
      delay(1000);
      servoClose();
       }
   servofloor3();
   servoOpen();
   delay(500);
   servoClose();
 }
 
  void floor3to1(){
  weight();
   Serial.println("Floor 3 to 1");
   servofloor2();
   if(f3==0){
      Serial.println("Floor 2 request down");
      servoOpen();
      delay(1000);
      servoClose();
      }
   delay(1000);
   servofloor1();
   servoOpen();
   delay(500);
   servoClose();
 }
  /*-----------------------------------XXXX----------------------------------*/
