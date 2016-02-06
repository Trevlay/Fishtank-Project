float temp=0;
int analogT=0;
int tempsetpoint=0;
float tempset=0;
float tempsd=1.465390194;
float tempUCL=0;
float tempLCL=0;
float tempU=0;
float tempL=0;

void setup() {
pinMode(10,OUTPUT);
Serial.begin(9600);

tempsetpoint=27;           //setpoint given by instructor degrees celsius
tempset=8.5499*tempsetpoint+270.43;    //temperature setpoint analog 
tempUCL=tempset+3*tempsd;  //temperature UCL analog
tempLCL=tempset-3*tempsd;   //temperature LCL analog
tempU=.11696*tempUCL-31.6296;  //temperature UCL degrees celsius
tempL=.11696*tempLCL-31.6296;  //temperature LCL degrees celsius

//print tempU, tempL and temp to LCD screen

}

void loop() {
 analogT=analogRead(2);     //temperature analog
 temp=.11696*analogT-31.6296; //temperature degrees celsius

 //Serial.println(temp);
 //Serial.println(tempUCL);

 if(analogT<tempLCL){
  digitalWrite(10,HIGH);

  //display that heater is on on the LCD screen
  }

 if(analogT>tempUCL){
  digitalWrite(10,LOW);

  //display that the heater is off on the LCD screen
  }

}
