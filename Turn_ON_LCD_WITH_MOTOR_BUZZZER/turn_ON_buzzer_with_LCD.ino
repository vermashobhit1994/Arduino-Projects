
/* File that will turn the Motor clockwise when obstacle come with distance less than MIN_DESIRED_DISTANCE and also turn ON buzzer*/
#include <HCSR04.h>//library for using the ultrasonic sensor
#include<LCD_I2C.h>




//pins for ultrasonic sensor
const uint8_t echo = 2;
const uint8_t trig  = 6;
const uint8_t motorIP3 = 4;//Pin for motor input 3
const uint8_t motorIP4 = 5;//Pin for motor input 4

#define MIN_DESIRED_DISTANCE  5
#define MAX_DESIRED_DISTANCE  15

#define BUZZER_PIN        3
      


//Initialize the ultrasonic sensor with pins
UltraSonicDistanceSensor distanceSensor(trig,echo);  

#define LCD_ADDR         0x27// Default address of most PCF8574 module

//Initialize the LCD pins
#define LCD_SS_PIN         

//Initialize the LCD 
LCD_I2C lcd(LCD_ADDR); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  

  //setting the mode for PWM pin which is connected to buzzer
  pinMode(BUZZER_PIN,OUTPUT);



  //setting the mode for trigger and echo pin
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);

  //Initialize the trigger pin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

   //setting the mode for motor
  pinMode(motorIP3, OUTPUT);
  pinMode(motorIP4, OUTPUT);

  /* Note : Here there are 2 pin each for SCL and SDA*/

  //initialize the LCD
  lcd.begin();

  //turn ON LCD backlight
  lcd.backlight();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance = distanceSensor.measureDistanceCm();
  
  //rotate the motor clockwise if distance is less than min desired distance
  if(distance < MIN_DESIRED_DISTANCE )  
  {
      analogWrite(BUZZER_PIN,130);//turn ON buzzer
      digitalWrite(motorIP3, HIGH);//write 1 to IP3 pin
      digitalWrite(motorIP4, LOW);//write 0 to IP3 pin
      //delay(100);
      lcd.setCursor(0,0);
      lcd.print("Distance: ");
      lcd.print(distance);
      delay(800);
      lcd.clear();  

  }
  
  //stop the motor 
  else
  {
      analogWrite(BUZZER_PIN,0);//turn OFF buzzer
      digitalWrite(motorIP3, LOW);
      digitalWrite(motorIP4, LOW);
      
      lcd.setCursor(0,0);
      lcd.print("Distance: ");
      lcd.print(distance);
      delay(800);
      lcd.clear();  

  }
   
 
}
