//Limit Switches
#define XLIMIT PB1 //Limit switches must be Normally Open and connected to GND.
#define YLIMIT PB10
#define ZLIMIT PB11

#define XSTEP PA3
#define XDIR PA4

#define YSTEP PA5
#define YDIR PA6

#define ZSTEP PA7
#define ZDIR PB0

#define ENABLE PB12

#define XMOTORACC 500
#define XMOTORMAXSPEED 800

#define YMOTORACC 1000
#define YMOTORMAXSPEED 1000

#define ZMOTORACC 1000
#define ZMOTORMAXSPEED 1000

#define X_PER_MM 5
#define Y_PER_MM 5
#define Z_PER_MM 100

#define X_MAX 200
#define Y_MAX 200
#define Z_MAX 400

#include <AccelStepper.h>

AccelStepper XMOTOR(1,XSTEP,XDIR);
AccelStepper YMOTOR(1,YSTEP,YDIR);
AccelStepper ZMOTOR(1,ZSTEP,ZDIR);


//=====[ CONSTANTS ]============================================================
#define   DEBUG   0   // 0 = debugging disabled, 1 = enabled
#define ENABLE_ACTUATORS 1 //Set to one to make steppers move according to serial input

//=====[ VARIABLES ]============================================================

String readString; //main captured String 
int Xval = 0; //Absolute positions of X,Y,Z. 
int Yval = 0;
int Zval = 0;
int func = 0;

int ind1; // , location indexes for serial parse
int ind2;
int ind3;
int ind4;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial1.setTimeout(1);
  pinsetup();
  for (int i = 0; i<5; i++){
    tone(PA8, 31, 300);
    delay(200);
    tone(PA8, 61, 300);
    delay(200);
  }
  
  delay(2000);
  autohome(); //I've disabled autohome for now.

}

void loop() {
  //=====[ IMPORTANT ]============================================================
  //Your input string must use , as the data delimiter and * as the line delimeter. Eg - to move X to 2 Y to 5 and Z to 10 and grabber to 20, you should send   2,5,10,20*
  //You can see if its correct by setting DEBUG to 1 and looking at the output.
  //Set ENABLE_ACTUATORS to enable movement of steppers.
  //Once you're sure about the movement and directions, test autohome function.
  SerialParser();

  
}
