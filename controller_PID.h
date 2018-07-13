class controllerPID
{
  private:
  float p;
  float i;
  float d;
  float k1;
  float k2;
  float k3;
  float input;
  float output;
  float error;
  float targetValue;
  unsigned long time;
  public:
  controllerPID(float k1, float k2, float k3)
  {
    this->k1=k1;
    this->k2=k2;
    this->k3=k3;
    this->p=0;
    this->i=0;
    this->d=0;
    this->input=0;
    this->error=0;
    this->targetValue=0;
    this->time = millis();
  }
  void setInitialInput(float input)
  {
    this->input = input;
  }
  void setTargetValue(float targetValue)
  {
    this->targetValue = targetValue;
  }
  float getInput(float sensorValue)
  {
//    Serial.print("target value is: ");
//    Serial.print( this->targetValue);
//    Serial.print(", and sensor value is: ");
//    Serial.println( sensorValue);
    float currentErr = this->targetValue - sensorValue;
    float returnValue=0;
    float deltaTime = float(millis()-this->time);
    if (deltaTime<0.0001)
    return this->input;
    else{
    returnValue = this->input + 
             this->k1*currentErr+
             this->k2*this->i+
             this->k3*(currentErr - this->error)/deltaTime;
    if (this->targetValue>=0)
    {
      if(returnValue>255)returnValue=255;
      else if (returnValue<0)returnValue=0;
    }
    else
    {
      if(returnValue<-255)returnValue=-255;
      else if(returnValue>0)returnValue=0;
    }
//    if (returnValue>255)returnValue=255;
//    if (returnValue<-255)returnValue=-255;
//             Serial.println("---------------------");
//             Serial.println(this->input);
//             Serial.println(this->k1*currentErr);
//             Serial.println(this->k2*this->i);
//             Serial.println(this->k3*(currentErr - this->error)/deltaTime);
    this->i+=deltaTime*currentErr;
    this->error = currentErr;
    this->d = (currentErr - this->error)/deltaTime;
    this->p = currentErr;
    this->input = returnValue;
    return returnValue;
    }
  }
  void print(void)
  {
    Serial.print("P: ");
    Serial.print(this->p);
    Serial.print(" I: ");
    Serial.print(this->i);
    Serial.print(" D: ");
    Serial.print(this->d);
    Serial.print(" O: ");
    Serial.print(this->output);
    Serial.println(" ");
  }
};
