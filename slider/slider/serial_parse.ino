void SerialParser(void) {
  if (Serial1.available())  {
    char c = Serial1.read();  //gets one byte from Serial1 buffer
    if (c == '*') {
      //do stuff

      if (DEBUG == 1) {
        Serial1.println();
        Serial1.print("captured String is : ");
        Serial1.println(readString); //prints string to Serial1 port out
      }

      ind1 = readString.indexOf(',');  //finds location of first ,
      Xval = readString.substring(0, ind1).toInt();   //captures first data String
      if(Xval > X_MAX){
        Xval = X_MAX;
      }else if(Xval <0){
        Xval = 0;
      }
      ind2 = readString.indexOf(',', ind1 + 1 ); //finds location of second ,
      Yval = readString.substring(ind1 + 1, ind2 + 1).toInt(); //captures second data String
      if(Yval > Y_MAX){
        Yval = Y_MAX;
      }else if(Yval <0){
        Yval = 0;
      }
      ind3 = readString.indexOf(',', ind2 + 1 );
      Zval = readString.substring(ind2 + 1, ind3 + 1).toInt();
      if(Zval > Z_MAX){
        Zval = Z_MAX;
      }else if(Zval <0){
        Zval = 0;
      }
      ind4 = readString.indexOf(',', ind3 + 1 );
      func = readString.substring(ind3 + 1).toInt(); //captures remaining part of data after last ,

      if (DEBUG == 1) {
        Serial1.print("X = ");
        Serial1.println(Xval);
        Serial1.print("Y = ");
        Serial1.println(Yval);
        Serial1.print("Z = ");
        Serial1.println(Zval);
        Serial1.print("func = ");
        Serial1.println(func);
        Serial1.println();
        Serial1.println();
      }
      readString = ""; //clears variable for new input

      if (ENABLE_ACTUATORS == 1 && func == 0) {
        XMOTOR.runToNewPosition(Xval*X_PER_MM);
        YMOTOR.runToNewPosition(Yval*Y_PER_MM);
        ZMOTOR.runToNewPosition(Zval);
        tone(PA8, 31, 100);
        Serial1.println("OK");
        
        

      }else if(func == 1){
        ZMOTOR.runToNewPosition(Zval);
        XMOTOR.runToNewPosition(Xval*X_PER_MM);
        YMOTOR.runToNewPosition(Yval*Y_PER_MM);
        tone(PA8, 31, 100);
        Serial1.println("OK");
      }else if(func == 2){
        //set function2
        Serial1.println("OK");
      }
      
      

    }
    else {
      readString += c; //makes the string readString
    }
  }
}

