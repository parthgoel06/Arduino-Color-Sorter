#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int frequency = 0;
int color=0;
int top_servo_start = 90;
int top_servo_sensor = 26;
int top_servo_end = 0 ;


void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  topServo.attach(7);
  bottomServo.attach(8);

  Serial.begin(9600);
}

void loop() {

  topServo.write(top_servo_start);
  delay(500);
  
  for(int i = top_servo_start; i > top_servo_sensor; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(500);
  
  color = readColor();
  Serial.print("color");
  Serial.println(color);

  delay(10);  

  switch (color) {
    case 1:
    bottomServo.write(10);
    break;

    case 2:
    bottomServo.write(35);
    break;

    case 3:
    bottomServo.write(65);
    break;

    case 4:
    bottomServo.write(95);
    break;

    case 0:
    bottomServo.write(125);
    break;
  }
  delay(300);
  
  for(int i = top_servo_sensor; i >top_servo_end ; i--) {
    topServo.write(i);
    delay(2);
  } 
  delay(200);
  
  for(int i = top_servo_end; i < top_servo_start; i++) {
    topServo.write(i);
    delay(2);
  }
  color=0;
}

// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
//  Serial.print("R= ");//printing name
//  Serial.print(frequency);//printing RED color frequency
//  Serial.print("  ");
  R = map(frequency,0, 255,0,100000);
  Serial.print("R_remapped= ");//printing name
  Serial.print(R);//printing RED color frequency
  Serial.print("  ");
  
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
//  Serial.print("G= ");//printing name
//  Serial.print(frequency);//printing RED color frequency
//  Serial.print("  ");
  G = map(frequency,0, 255,0,100000);
  Serial.print("G_remapped= ");//printing name
  Serial.print(G);//printing RED color frequency
  Serial.print("  ");
  delay(50);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
//  Serial.print("B= ");//printing name
//  Serial.print(frequency);//printing RED color frequency
//  Serial.println("  ");
  B = map(frequency,0, 255,0,100000);
  Serial.print("B_remapped= ");//printing name
  Serial.print(B);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  int color = 0;
  if(R<11800 & R>11300 & G<17700 & G>16800){
    color = 1; // Red
    return color;
  }
  if(R<10000 & R>8000 & G<11800 & G>11300){
    color = 2; // yellow
    return color;
  }
  if(R<15000 & R>13320 & G<1670 & G>1445){
    color = 3; // green
    return color;
  }
  if(R<12600 & R>11850 & G<1750 & G>1450){
    color = 4; // pink
    return color;
  }
  return color;
    
}
