#define TR 3 //TRIGGER_PIN_RIGHT 2 // Trigger pin for right ultrasonic sensor
#define ER 2 //ECHO_PIN_RIGHT 3    // Echo pin for right ultrasonic sensor
#define TF 4 //TRIGGER_PIN_FRONT 4 // Trigger pin for front ultrasonic sensor
#define EF 5 //ECHO_PIN_FRONT 5    // Echo pin for front ultrasonic sensor
#define TL 6 //TRIGGER_PIN_LEFT 6  // Trigger pin for left ultrasonic sensor
#define EL 7 //ECHO_PIN_LEFT 7     // Echo pin for left ultrasonic sensor

#define MAX_DISTANCE 200 // Maximum distance to measure in centimeters

#define M11 10  //MOTOR_LEFT_SPEED_PIN 9    // Pin for controlling left motor speed
#define M12 9 //MOTOR_LEFT_DIRECTION_PIN 10 // Pin for controlling left motor direction
#define M21 11 //MOTOR_RIGHT_SPEED_PIN 6   // Pin for controlling right motor speed
#define M22 12 //MOTOR_RIGHT_DIRECTION_PIN 5 // Pin for controlling right motor direction

#define MOTOR_SPEED 210 // Speed of the motors (0-255)

char c[] = {'F','L','L','L','R','U','L','R','L','U','F','R','R','R','L','L','R','F','R','L','L','U','F','R','L','R','L','L','L','R','L','U','F'};
  int size = sizeof(c) / sizeof(c[0]);

  int i=0;


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
  
  int i = 0;

  
  while (i < 10) {
    int j = 0;
    while (j < (size - 2)) {
      char a = c[j];
      char b = c[j+1];
      char d = c[j+2];
      
      if ((a == 'L' && b == 'U' && d == 'L') || (a == 'R' && b == 'U' && d == 'R')) {
        c[j] = 'F';
        for (int k = j + 1; k < size - 2; k++) {
          c[k] = c[k + 2];
        }
        size = size - 2;
      } 
      else if ((a == 'L' && b == 'U' && d == 'R') || (a == 'R' && b == 'U' && d == 'L')) {
        c[j] = 'U';
        for (int k = j + 1; k < size - 2; k++) {
          c[k] = c[k + 2];
        }
        size = size - 2;
      }
      else if ((a == 'L' && b == 'U' && d == 'F') || (a == 'F' && b == 'U' && d == 'L')) {
        c[j] = 'R';
        for (int k = j + 1; k < size - 2; k++) {
          c[k] = c[k + 2];
        }
        size = size - 2;
      }
      else if ((a == 'R' && b == 'U' && d == 'F') || (a == 'F' && b == 'U' && d == 'R')) {
        c[j] = 'L';
        for (int k = j + 1; k < size - 2; k++) {
          c[k] = c[k + 2];
        }
        size = size - 2;
      }
      else if (a == 'F' && b == 'U' && d == 'F') {
        c[j] = 'U';
        for (int k = j + 1; k < size - 2; k++) {
          c[k] = c[k + 2];
        }
        size = size - 2;
      }
      j++;
    }
    i++;
  }
  
  for (int l = 0; l < size; l++) {
    Serial.print(c[l]);
    Serial.print(" ");
  }

}

void loop() {

  long rightDistance = ping(TR, ER);
  long frontDistance = ping(TF, EF);
  long leftDistance = ping(TL, EL);

    if(rightDistance<3){
      digitalWrite(M11, LOW);
      digitalWrite(M12, HIGH);
      digitalWrite(M21, HIGH);
      digitalWrite(M22, LOW);
      delay(250);
  }

  else if(leftDistance<3){
      digitalWrite(M11, HIGH);
      digitalWrite(M12, LOW);
      digitalWrite(M21, LOW);
      digitalWrite(M22, HIGH);
      delay(250);
  }

  while(leftDistance<20 && rightDistance<20){
    moveForward();

    rightDistance = ping(TR, ER);
    frontDistance = ping(TF, EF);
    leftDistance = ping(TL, EL);

  }
if(i<size){

  if(c[i++]=='F'){
    digitalWrite(M11, HIGH);
    digitalWrite(M12, LOW);
    digitalWrite(M21, HIGH);
    digitalWrite(M22, LOW);
    delay(600);
  }

  else if(c[i++]=='L')
  {
    turnLeft();
  }

  else if(c[i++]=='R')
  {
    turnRight();
  }

  else if(c[i++]=='U')
  {
    uturn();
  }
}

}


int ping(int triggerPin, int echoPin) {

  long duration, distance;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  return distance; 
}

void moveForward() {
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
}

void turnLeft() {
  digitalWrite(M11, LOW);
  digitalWrite(M12, HIGH);
  digitalWrite(M21, HIGH);
  digitalWrite(M22, LOW);
  delay(500); 
}

void turnRight() {
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, LOW);
  digitalWrite(M22, HIGH);
  delay(500); 
}

void uturn(){
  digitalWrite(M11, HIGH);
  digitalWrite(M12, LOW);
  digitalWrite(M21, LOW);
  digitalWrite(M22, HIGH);
  delay(500);

}
