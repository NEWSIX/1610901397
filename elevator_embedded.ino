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

#define PC2 35 //LED
#define PC3 34

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
int jik=1;

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

}

void loop() 
{
 VALUE();

while (jik != 0){
servofloor1();
servoClose();
jik=0;
}

button_floor();
requsetfloor();
compare_floor();
button_door();
compare_door();

}

void  VALUE(){
e0= digitalRead(PF0 ); //open 
e1= digitalRead(PF1 ); // close
e2= digitalRead(PF2 ); //floor1
e3= digitalRead(PF3 ); //floor 2
e4= digitalRead(PF4 ); //floor 3

f0= digitalRead(PA0 ); //request up floor 1
f1= digitalRead(PA1); //request down floor 3
f2= digitalRead(PA2);//request up floor 2
f3= digitalRead(PA3); //request down floor 2

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
   {	
   veil=3;
    }
  }
  
void button_floor(){
   if(e2==0 && e3 == 1 && e4==1 ){
   polar=1;
   }
   if(e2==1 && e3 == 0 && e4==1){
    polar=2;
   }
    if(e2==1 && e3 == 1 && e4==0){
    polar=3;
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
      digitalWrite(PC2,HIGH);
      pos = 180;
      myservo1.write(pos);
   }
void servoClose(){
   digitalWrite(PC2,LOW);
   pos = -180;
   myservo1.write(pos);
   }
   
   //****//
   
void servofloor1(){
      fa=1;
      pos = -180;
      myservo2.write(pos);
       sevensegment(fa);
   }
  void servofloor2(){
      fa=2;
      pos = 93;
      myservo2.write(pos);
       sevensegment(fa);
   }
void servofloor3(){
      fa=3;
      pos = 180;
      myservo2.write(pos);
      sevensegment(fa);
   }
 /*-----------------------------------Weight------------------------------------*/
void weight(){
   long reading = scale.read();
   X = reading/10000;
   while(X>100){
	 long reading = scale.read();
	 X = reading/10000;
	  servoOpen();
	  digitalWrite(PC3,HIGH);
	 delay(500);
      }
      {
	 digitalWrite(PC3,LOW);
	 servoClose();
	 delay(500);
	 }
}
  /*-----------------------------------7seg Display------------------------------------*/
  
 void sevensegment(int num){
  if (num== 1){
 digitalWrite(PC0,HIGH); 
 digitalWrite(PC1,LOW);
 
 } 
  else if (num== 2){
 digitalWrite(PC0,LOW );
 digitalWrite(PC1,HIGH);

 } 
  else if (num== 3){
 digitalWrite(PC0,HIGH); 
 digitalWrite(PC1,HIGH);

 } 
}

  /*-----------------------------------Compared------------------------------------*/
   int timer;
   
void compare_door(){
      if(veil==1){
	 servoOpen();
	 timer=1;
      }
      if(e0 ==1&& e1==0){
	 servoClose();
      }
      if (timer==1){
	 for(timer;timer<=5000;timer){
	    VALUE();
	    if(e1==0){
	       veil=0;
	       break;
	    }
	    delay(1);
	    timer=timer+1;
	 }
	 servoClose();
      }
 }
 
 //*****************************//
 
 void  compare_floor(){
       if (polar == 1 ){
	 if(fa==2){
	 floor2to1();
	 }
	 
	 if(fa==3){
	 floor3to1();
	 }
	} 
	
	 //**//
	 
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
	 }
	 if(fa==2){
	    floor2to3();
	 }
	} 
}

void requsetfloor(){
   if(f0==0){
      if(fa==1){
	 veil=1;
	 compare_door();
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
	     veil=1;
	    compare_door();
	  }
   }
   
   if(f2==0 || f3==0){
      if(fa==1){
	 floor1to2();
	 }
	  if(fa==2){
	     veil=1;
	    compare_door();
	  }
	  if(fa==3){
	    floor3to2();
	  }
   }
}


 /*-----------------------------------FLOOR MOVE-----------------------------------*/
 void floor2to1(){
   weight();
   servofloor1();
   veil=1;
   compare_door();
 }
 void floor2to3(){
   weight();
   servofloor3();
   veil=1;
   compare_door();
 }

 void floor3to2(){
   weight();
   servofloor2();
   veil=1;
   compare_door();;
 }
 void floor1to2(){
   weight();
   servofloor2();
   veil=1;
   compare_door();
 }
 
 //**//

 void floor1to3(){
   weight();
   servofloor2();
   delay(1000);
   if(f2==0){
       veil=1;
      compare_door();
       }
   servofloor3();
   veil=1;
   compare_door();
 }
 
  void floor3to1(){
  weight();
   servofloor2();
   if(f3==0){
      veil=1;
      compare_door();
      }
   delay(1000);
   servofloor1();
   veil=1;
   compare_door();
 }
 
  /*-----------------------------------XXXX----------------------------------*/
