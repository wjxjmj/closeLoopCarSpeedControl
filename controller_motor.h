class controllerMotor
{
  private:
  int stbyPin;
  int in1Pin[2];
  int in2Pin[2];
  int pwmPin[2];
  public:
  controllerMotor(int pwmAPin,int pwmBPin,int aIn1Pin,int aIn2Pin,int bIn1Pin, int bIn2Pin, int stbyPin)
  {
    this->pwmPin[0] = pwmAPin;
    this->in1Pin[0] = aIn1Pin;
    this->in2Pin[0] = aIn2Pin;
    
    this->pwmPin[1] = pwmBPin;
    this->in1Pin[1] = bIn1Pin;
    this->in2Pin[1] = bIn2Pin;
    
    this->stbyPin = stbyPin;
    
    pinMode(pwmAPin,OUTPUT);
    pinMode(pwmBPin,OUTPUT);
    pinMode(aIn1Pin,OUTPUT);
    pinMode(aIn2Pin,OUTPUT);
    pinMode(bIn1Pin,OUTPUT);
    pinMode(bIn2Pin,OUTPUT);
    pinMode(stbyPin,OUTPUT);
  }
  void doMotorControl(boolean bit1,boolean bit2, boolean bitStby, int pwm, int motorIndex)
  {
    //Serial.println(pwm);
    digitalWrite(this->stbyPin,bitStby);
    digitalWrite(this->in1Pin[motorIndex],bit1);
    digitalWrite(this->in2Pin[motorIndex],bit2);
    analogWrite(this->pwmPin[motorIndex],pwm);
  }
  float norm(float x)
  {
    if (x>0)return x;
    else return (-x);
  }
  void setMotorSpeed(int speed1, int speed2)
  {
    speed1=int(speed1);
    speed2=int(speed2);
    if(speed1==0){
      doMotorControl(HIGH,HIGH,HIGH,LOW,0);
    }
    else
    {
      if (speed1>255)speed1=255;
      else if (speed1<-255)speed1=-255;
      if (speed1>0){
      doMotorControl(LOW,HIGH,HIGH,speed1,0);
      }
      else
      doMotorControl(HIGH,LOW,HIGH,-speed1,0);
    }
    if(speed2==0){
      doMotorControl(HIGH,HIGH,HIGH,LOW,1);
    }
    else
    {
      if (speed2>255)speed2=255;
      else if (speed2<-255)speed2=-255;
      float sat = norm(speed2);
      if (speed2>0)
      doMotorControl(LOW,HIGH,HIGH,speed2,1);
      else
      doMotorControl(HIGH,LOW,HIGH,-speed2,1);
    }
  }
};
