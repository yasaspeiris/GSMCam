void autohome() {
  xhome();
  yhome();
  zhome();
}

void yhome() {
  int initial_yhome = -1;
  YMOTOR.setMaxSpeed(1000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  YMOTOR.setAcceleration(1000.0);  // Set Acceleration of Stepper

  while (1) { // Make the Stepper move CCW until the switch is activated
    YMOTOR.moveTo(initial_yhome);  // Set the position to move to
    initial_yhome--;
    YMOTOR.run();
    delay(10);
    if(!digitalRead(YLIMIT)){
      delay(5);
      if(!digitalRead(YLIMIT)){
        break;
      }
    }
  }

  YMOTOR.setCurrentPosition(0);  // Set the current position as zero for now
  YMOTOR.setMaxSpeed(500.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  YMOTOR.setAcceleration(500.0);  // Set Acceleration of Stepper
  initial_yhome = 1;
  
  while (!digitalRead(YLIMIT)) { // Make the Stepper move CW until the switch is deactivated

    YMOTOR.moveTo(initial_yhome);
    YMOTOR.run();
    initial_yhome++;
    delay(10);
  }

  YMOTOR.setCurrentPosition(0);
  YMOTOR.setMaxSpeed(YMOTORMAXSPEED);      // Set Max Speed of Stepper (Faster for regular movements)
  YMOTOR.setAcceleration(YMOTORACC);  // Set Acceleration of Stepper

}

void xhome() {
  int initial_xhome = -1;

  //  Set Max Speed and Acceleration of each Steppers at startup for homing
  XMOTOR.setMaxSpeed(1000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  XMOTOR.setAcceleration(1000.0);  // Set Acceleration of Stepper
  // Start Homing procedure of Stepper Motor at startup

  while (digitalRead(XLIMIT)) { // Make the Stepper move CCW until the switch is activated
    XMOTOR.moveTo(initial_xhome);  // Set the position to move to
    initial_xhome--;  // Decrease by 1 for next move if needed
    XMOTOR.run();  // Start moving the stepper
    delay(5);
  }

  XMOTOR.setCurrentPosition(0);  // Set the current position as zero for now
  XMOTOR.setMaxSpeed(500.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  XMOTOR.setAcceleration(500.0);  // Set Acceleration of Stepper
  initial_xhome = 1;

  while (!digitalRead(XLIMIT)) { // Make the Stepper move CW until the switch is deactivated
    XMOTOR.moveTo(initial_xhome);
    XMOTOR.run();
    initial_xhome++;
    delay(5);
  }

  XMOTOR.setCurrentPosition(0);
  XMOTOR.setMaxSpeed(XMOTORMAXSPEED);      // Set Max Speed of Stepper (Faster for regular movements)
  XMOTOR.setAcceleration(XMOTORACC);  // Set Acceleration of Stepper

}


void zhome() {
  int initial_zhome = -1;
  //  Set Max Speed and Acceleration of each Steppers at startup for homing
  ZMOTOR.setMaxSpeed(1000.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  ZMOTOR.setAcceleration(1000.0);  // Set Acceleration of Stepper

  // Start Homing procedure of Stepper Motor at startup

  while (1) {  // Make the Stepper move CCW until the switch is activated
    ZMOTOR.moveTo(initial_zhome);  // Set the position to move to
    initial_zhome--;  // Decrease by 1 for next move if needed
    ZMOTOR.run();  // Start moving the stepper
    delay(10);
    if(!digitalRead(ZLIMIT)){
      delay(10);
      if(!digitalRead(ZLIMIT)){
        break;
      }
    }
  }

  ZMOTOR.setCurrentPosition(0);  // Set the current position as zero for now
  ZMOTOR.setMaxSpeed(500.0);      // Set Max Speed of Stepper (Slower to get better accuracy)
  ZMOTOR.setAcceleration(500.0);  // Set Acceleration of Stepper
  initial_zhome = 1;

  while (!digitalRead(ZLIMIT)) { // Make the Stepper move CW until the switch is deactivated
    ZMOTOR.moveTo(initial_zhome);
    ZMOTOR.run();
    initial_zhome++;
    delay(20);
  }

  ZMOTOR.setCurrentPosition(0);
  ZMOTOR.setMaxSpeed(ZMOTORMAXSPEED);      // Set Max Speed of Stepper (Faster for regular movements)
  ZMOTOR.setAcceleration(ZMOTORACC);  // Set Acceleration of Stepper

}

