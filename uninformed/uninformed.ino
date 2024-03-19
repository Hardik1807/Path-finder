#define TR 6 //TRIGGER_PIN_RIGHT 2 // Trigger pin for right ultrasonic sensor
#define ER 7 //ECHO_PIN_RIGHT 3    // Echo pin for right ultrasonic sensor
#define TF 4 //TRIGGER_PIN_FRONT 4 // Trigger pin for front ultrasonic sensor
#define EF 5 
#define TL 2 //TRIGGER_PIN_LEFT 6  // Trigger pin for left ultrasonic sensor
#define EL 8 //ECHO_PIN_LEFT 7     // Echo pin for left ultrasonic sensor

#define MAX_DISTANCE 200 // Maximum distance to measure in centimeters

#define M11 3 //MOTOR_LEFT_SPEED_PIN 9    // Pin for controlling left motor speed
#define M12 9 //MOTOR_LEFT_DIRECTION_PIN 10 // Pin for controlling left motor direction
#define M21 10 //MOTOR_RIGHT_SPEED_PIN 6   // Pin for controlling right motor speed
#define M22 11 //MOTOR_RIGHT_DIRECTION_PIN 5 // Pin for controlling right motor direction

#define MOTOR_SPEED 210 // Speed of the motors (0-255)

char path[1000];

int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(TR, OUTPUT);
  pinMode(ER, INPUT);
  pinMode(TL, OUTPUT);
  pinMode(EL, INPUT);
  pinMode(TF, OUTPUT);
  pinMode(EF, INPUT);
  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);
}

void loop() {

  long rightDistance = ping(TR, ER);
  long frontDistance = ping(TF, EF);
  long leftDistance = ping(TL, EL);

  Serial.print("Right: ");
  Serial.print(rightDistance);
  Serial.print(" cm, Front: ");
  Serial.print(frontDistance);
  Serial.print(" cm, Left: ");
  Serial.print(leftDistance);
  Serial.println(" cm");

  if(rightDistance<8){
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M21, HIGH);
      digitalWrite(M22, LOW);

      delay(70);
        digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  analogWrite(M11,150);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
        analogWrite(M21,150);
        delay(100);
  }

  else if(leftDistance<8){
      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      analogWrite(M11,150);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
      analogWrite(M21,150);
      delay(70);
        digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  analogWrite(M11,150);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
        analogWrite(M21,150);
        delay(100);
  }




  // while(frontDistance > 20 && leftDistance < 20){
  //   if(rightDistance > 20){
  //     path[i++]= 'F';
  //   }
  //   moveForward();
  //   rightDistance = ping(TR, ER);
  //   frontDistance = ping(TF, EF);
  //   leftDistance = ping(TL, EL);
  // }

  if (leftDistance > 30 && rightDistance >30 && frontDistance >30)
  {
    turnLeft();
    path[i++] = 'L';
  }

  else if (leftDistance > 30 && rightDistance > 30 && frontDistance < 30)
  {
    turnLeft();
    path[i++] = 'L';
  }

  else if (leftDistance > 30 && rightDistance < 30 && frontDistance > 30)
  {
    turnLeft();
    path[i++] = 'L';
  }

   else if (leftDistance < 30 && rightDistance > 30 && frontDistance > 30)
  {
    moveForward();
    path[i++] = 'F';
  }

  else if (leftDistance < 30 && rightDistance < 30 && frontDistance > 30)
  {
    moveForward();
  }

  else if (leftDistance > 30 && rightDistance <30 && frontDistance <30)
  {
    turnLeft();
    path[i++] = 'L';
  }

  else if (leftDistance < 30 && rightDistance >30 && frontDistance <30)
  {
    turnRight();
    path[i++] = 'R';
  }

  else if (leftDistance < 30 && rightDistance <30 && frontDistance <30)
  {
    uturn();
    path[i++] = 'U';
  }

  Serial.println(path);


}

int ping(int triggerPin, int echoPin) {

  long duration1, distance1;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration1 = pulseIn(echoPin, HIGH);

  distance1 = duration1 * 0.034 / 2;
  
  return distance1; 
}

void moveForward()
. {
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  analogWrite(M11,150);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  analogWrite(M21,150);
  delay(50);
}

void turnLeft() {
  delay(25);
  digitalWrite(M11, LOW);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(600); 
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(400);
}

void turnRight() {
  delay(25);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, LOW);
  digitalWrite(M22, LOW);
  delay(600); 
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(350);
}

void uturn(){
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  analogWrite(M11,150);
  digitalWrite(M21, LOW);
  digitalWrite(M22, HIGH);
  analogWrite(M21,150);
  delay(1000);
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  analogWrite(M11,150);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  analogWrite(M21,150);
  delay(350);

}