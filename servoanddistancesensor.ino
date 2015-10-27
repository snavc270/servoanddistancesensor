#include <Servo.h>


//This code was developed partially from Ping))) code found in the public domain
//written by David A. Mellis, and adapted to the HC-SRO4 by Tautvidas Sipavicius

const int trigPin= 6; 
const int echoPin= 7; 
 
Servo rightServo;
Servo leftServo;   
int pos = 0;

int x; 

void setup() {
  Serial.begin(9600); 
  
  rightServo.attach(9); 
  leftServo.attach(8); 
}

void loop() {

  long duration, inches, cm;

  //cleans out sensor signal
  pinMode(trigPin, OUTPUT); 
  digitalWrite(trigPin,LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 

  pinMode(echoPin, INPUT);

  //reads time takes for ping to hit object and echo back to sensor
  duration = pulseIn(echoPin, HIGH);

  
  inches = microsecondsToInches(duration); 
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches); 
  Serial.print("in, "); 
  Serial.print(cm); 
  Serial.print("cm"); 
  Serial.print(x); 
  Serial.println(); 



  if(inches<=15){
    x=1*inches;  
    sweep(1);
  }else if (inches>15){
    leftServo.write(pos);
    rightServo.write(pos);  
  }
}


  

  
  
  long microsecondsToInches(long microseconds){
    //73.746 microseconds per inch, /2 = distance to object
    return microseconds/ 74/ 2; 
    }
    
  long microsecondsToCentimeters(long microseconds){
    //speed of sound to obstacle 
    return microseconds /29/2; 
    } 

 void sweep(int cycle){
//      for(int j=0; j<cycle; j++){
//        for(pos = 0; pos<45; pos +=1){
//          myservo.write(pos); 
//          delay(x);
//        }
//        for(pos=45; pos>=0; pos -=1){
//          myservo.write(pos); 
//          delay(x); 
//          
//        }
        for(pos = 60; pos <= 120; pos += 1){                                 
            leftServo.write(pos);               
            delay(x*.75);     
        
            rightServo.write(120-pos);
            delay(x*.75); 
          } 
          
        for(pos = 120; pos>=60; pos-=1){                                
          leftServo.write(pos);              
          delay(x*.5); 
      
          rightServo.write(120-pos); 
          delay(x*.5); 
        } 
     }

