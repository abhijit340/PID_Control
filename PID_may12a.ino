  double In, Out, Set;
  double K_i, K_p, K_d;
  double err, err_D, err_I, errLast;
  unsigned long prevTime = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void PID() {
  //my version of a PID control algorithim
  
  // first step is to figure out the current time
  unsigned long currTime = millis();  //millis is a built in function that returns the time ince the program started
                                      //currTime is an unsigned long since this varible type holds 32 bits and milliseconds have a lot of digits
  double deltaT = (double)(currTime - prevTime) // detlaT is cast as a double so save space and value shouldn't be too big

  //finding the error relative to to the setpoint
  err = Set - In;
  err_D = (err - errLast)/deltaT;
  err_I = err_I + (err * deltaT);
 
  //update these varibles for the next iteration
  errLast = err;
  prevTime = currTime;
  
  

}

