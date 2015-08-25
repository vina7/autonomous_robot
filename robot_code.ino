// Vinayak Nesarikar
// Date created 5/19/15
// Date last modified 8/25/15
#define FORWARDSPEED 110
#define BACKWARDSPEED 110
#define FORWARDSPEED2 130
#define BACKWARDSPEED2 130
#define STOPSPEED 0
#define BACKWARD 3
#define FORWARD 2
#define STOPPED 1
#define PWMA 2
#define AIN1 4
#define AIN2 3
#define STBY 5
#define PWMB 8
#define BIN1 6
#define BIN2 7
#define trigPin 24 //right trig 
#define echoPin 26
#define led 22
#define led2 28
#define trigPin2 10 //left trig
#define echoPin2 11
#define led3 9
#define led4 12
int motor1_speed=0;
int motor2_speed=0;
byte incomingByte=0;
int direction2=0;// motor1 direction
int direction3=0;// motor2 direction
int speed1=0;
void move1(int motor, int speed1, int direction1);
void setup() {
  Serial.begin (9600);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

}

void loop() {
  if (Serial.available() > 0) 
  {
    incomingByte = Serial.read();
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  if (incomingByte==49)//type 1 into serial monitor to stop the robot
  {
    move1(1, STOPSPEED , 1);
    move1(2, STOPSPEED , 1);
  }
  long duration, distance,duration2, distance2;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(1); 
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(3); /
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2/2) / 29.1;
  if (distance < 30 && distance2 < 30) //backward condition
    {
      Serial.println(duration2);
      // This is where the LED On/Off 
      digitalWrite(led,HIGH); 
      Serial.println("right senor blocked ");
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      Serial.println("left senor blocked ");
      digitalWrite(led4,HIGH);
      for(int i=0;i<15;i++)
      {
      move1(1, FORWARDSPEED , 1);
      move1(2, FORWARDSPEED2 , 1);
      }

    } 
    else if(distance < 30 && distance2 >= 30) //turnleft condition
    {
      Serial.println(duration2);
     // This is where the LED On/Off 
      digitalWrite(led,HIGH); 
      Serial.println("right senor blocked ");
     digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);
      Serial.println("left senor not blocked ");
      digitalWrite(led4,LOW);
      for(int i=0;i<15;i++)
      {
      move1(1, BACKWARDSPEED, 0);
      move1(2, STOPSPEED , 0);
      }
    }
    else if (distance >= 30 && distance2 < 30) //turnright condition
    {
      // This is where the LED On/Off
      digitalWrite(led,LOW);
      Serial.println("right senor not blocked ");
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      Serial.println("left senor blocked ");
      digitalWrite(led4,LOW);
      for(int i=0;i<15;i++)
      {
      move1(1, STOPSPEED , 0);
      move1(2, BACKWARDSPEED2 , 0);
      }
    } 
    else //forward condition
    {
      // This is where the LED On/Off
      digitalWrite(led,LOW); 
      Serial.println("right senor not blocked ");
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      Serial.println("neither senor blocked ");
      digitalWrite(led4,HIGH);
      move1(1, BACKWARDSPEED, 0);
      move1(2, BACKWARDSPEED2 ,0);
    }
  }

void move1(int motor, int speed1, int direction1)
{
  //Move specific motor at speed and direction
  //motor: 0 for B 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction1 == 1)
  {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1)
  {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed1);
  }
  else
  {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed1);
  }
}
