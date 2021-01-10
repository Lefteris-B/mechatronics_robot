#include <SoftwareSerial.h>    //preprocesor commands
#include <Servo.h>
#define PI 3.1415926535897932384626433832795

                      //initialising robot  related variables
int wheelbase = 12;  //metaksonio
int completeTrajectoryTime = 0; //xrisimopoiw tin metavliti gia na ipoloisw to telos tis troxias
float radsPerSec = 0.39; //xrisimopoiw tin metavliti gia na ipoloisw to telos tis troxias 2XPI/radsPerSec

int state = 0;    //initialise bluetooth variables 
int txPin = 11;
int rxPin = 10;
SoftwareSerial bluetoothInput(rxPin, txPin);   //constructor

int leftServoPin = 12;  //initialise servo variables
int rightServoPin = 9;
Servo leftServo;
Servo rightServo;

int led = 8;      //initialise led pins

void setup() {
  bluetoothInput.begin(9600);     //setting bluetooth software serial
  leftServo.attach(leftServoPin);   //setting servo pins
  rightServo.attach(rightServoPin); 

  pinMode(led, OUTPUT);   //setting led ouput pin
}


void loop() {

  digitalWrite(led,HIGH);
  if(bluetoothInput.available() > 0){
    state = bluetoothInput.read();
    }
        if (state == '0'){    //emergency stop,turn off led as a signal
          Stop();
          digitalWrite(led,LOW);
        }
        if ((state >= '1') && (state <= '150')) { //start the circle
          digitalWrite(led,HIGH);
          doCircle(state);
        }
        else{
          bluetoothInput.write("Wrong number,  try again!");  
        }
}


void doCircle(int x){
  int lspeed = 0;
  int rspeed = 140;
  unsigned int timenow = millis();

  completeTrajectoryTime = (((2 * PI)/radsPerSec)* 1000);  //Ypologismos tou telous tis troxias, pollaplasiazw me to 1000 gia na xrisimopoihsw tin milis()
  lspeed = ((((1+wheelbase)/2*x)/((1+wheelbase))/2*x)*rspeed);  //ipologismos taxititas

  while (millis() - timenow > completeTrajectoryTime) {
    leftServo.write(lspeed);
    rightServo.write(rspeed);    
  }
}

void Stop(){            //stop servos
  leftServo.write(90);
  rightServo.write(90);
}
