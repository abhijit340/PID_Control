  //Libraries
  #include <Servo.h>
  
  // PID Varibles
  double In, Out;
  double K_i, K_p, K_d;
  double err, err_D, err_I;
  double errLast = 0;
  unsigned long prevTime = 0;
  double Set = 11;

  // Pinout Varibles 
  int servoPin = 3;
  int trigPin = 4;
  int echoPin = 5;

  //Servos
  Servo Servo1;
  int horizPos = 80; // the postion where the servo is hoizontal
  int minPos = horizPos - 10; //set max and min rotation postion so that it won't break anything
  int maxPos = horizPos + 10;
  int newPos; // postion assigned by PID

  //SystemVaribles
  double maxDistance = 40.64; //the arm is 16 inches long

  //Ultrasonic sensor vars
  double dur, dist;
  
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  
  // Assign Servo to pin
  Servo1.attach(servoPin);

  //Ultrasonic sensor
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}

void loop() 
{
  // get the current ball position
  // Code Adapted From http://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
 
  // clear pin  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //send trigger for 50 milsec
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(50);
  digitalWrite(trigPin, LOW);

  // read ultrasound response
  dur = pulseIn(echoPin, HIGH);
  dist = dur*0.034/2;
  if (dist > maxDistance)
  {
    dist = maxDistance;
  }
  In = dist;
  //the distance is now the input for the PID algorithim 
  K_p = 1.3;
  K_d = 3;
  K_i = 0;

  PID();
  newPos = horizPos + Out;
  
  //enforcing the movement limits
  if (newPos > maxPos)
  {
    newPos = maxPos;
  }
  else if (newPos < minPos)
  {
     newPos = minPos;
  }

  Servo1.write(newPos); 
//   delay(50); 
// Serial.print("I");

//Serial.print("err");
  Serial.print(newPos);
  Serial.print(" ");
//Serial.print("eD");
//Serial.print(err_D);
//Serial.print(" ");

}

void PID() {
  //my version of a PID control algorithim
  
  // first step is to figure out the current time
  unsigned long currTime = millis();  //millis is a built in function that returns the time ince the program started
                                      //currTime is an unsigned long since this varible type holds 32 bits and milliseconds have a lot of digits
  double deltaT = (double)(currTime - prevTime); // detlaT is cast as a double so save space and value shouldn't be too big

  //finding the error relative to to the setpoint
  err = Set - In;
  err_D = (err - errLast)/deltaT;
  err_I = err_I + (err * deltaT);
 
  //update these varibles for the next iteration
  errLast = err;
  prevTime = currTime;

// Serial.print(currTime);
// Serial.print(" ");
  
  //Output calcs
  Out = (K_p * err) + (K_i * err_I) + (K_d * err_D);
  

}

