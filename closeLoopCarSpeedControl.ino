#include <MsTimer2.h>
#include "controller_motor.h"
#include "controller_PID.h"
#define _time_interval 50.0
#include <Wire.h>

#define PWMA 5
#define AIN1 6
#define AIN2 8
#define STBY 10
#define PWMB 9
#define BIN1 19 
#define BIN2 18 
int isReady = 0;
int pinInt0 = 1;
int pinInt1 = 0;
int count1=0;
int count2=0;
int x=0;
int y=0;
int cmd1;
int cmd2;

controllerMotor motors(PWMA,PWMB,AIN1,AIN2,BIN1, BIN2, STBY);
controllerPID pid1(0.0011,0.0,0.00);
controllerPID pid2(0.0011,0.0,0.00);
volatile int state = LOW;
float speed1=0;
float speed2=0;
float input1;
float input2;
void setup()
{
  Wire.begin(4);                // 鍔犲叆 i2c 鎬荤嚎锛岃缃粠鏈哄湴鍧�涓� #4
  Wire.onReceive(receiveEvent); //娉ㄥ唽鎺ュ彈鍒颁富鏈哄瓧绗︾殑浜嬩欢
  //Wire.onRequest(requestEvent);
  Serial.begin(9600);
  pinMode(pinInt0, INPUT_PULLUP);
  pinMode(pinInt1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinInt0),blink1,RISING);//瑜版悆nt.0閻㈤潧閽╂稉濠傚磳濞屾寧妞�,鐟欙箑褰傛稉顓熸焽閸戣姤鏆焍link
  attachInterrupt(digitalPinToInterrupt(pinInt1),blink2,RISING);
  MsTimer2::set(int(_time_interval), getSpeed); // INTERVAL ms 
  MsTimer2::start();
  input1=100;
  input2=100;
  pid1.setInitialInput(input1);
  pid2.setInitialInput(input2);
}
 
void loop()
{
  cmd1=257;
  cmd2=250;
  pid1.setTargetValue(cmd1);
  pid2.setTargetValue(cmd2);
  motors.setMotorSpeed(input1, input2);
 if(isReady==1){
  input1=pid1.getInput(speed1);
  input2=pid2.getInput(speed2);
 }
  Serial.print(input1);
  Serial.print("->");
  Serial.print(speed1);
  Serial.print(",");
  Serial.print(input2);
  Serial.print("->");
  Serial.println(speed2);
  delay(1);
}

// 褰撲粠鏈烘帴鍙楀埌涓绘満瀛楃锛屾墽琛岃浜嬩欢
void receiveEvent(int howMany)
{
    cmd1 = Wire.read();    // 浣滀负鏁存暟鎺ュ彈瀛楄妭
    cmd2 = Wire.read();
} 

void blink1()//娑擃厽鏌囬崙鑺ユ殶
{
  if(cmd1>0)count1++;
  else count1--;
  isReady=1;
}
void blink2()//娑擃厽鏌囬崙鑺ユ殶
{
  if(cmd2>0)count2++;
  else count2--;
  isReady=1;
}
void getSpeed()
{
  speed1 = count1;
  speed2 = count2;
  count1 = 0;  
  count2 = 0;
  isReady=0;
}
