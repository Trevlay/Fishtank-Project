int Csp=0;       //Setpoint in decimal form
int setpoint=0;  //Setpoint (Csp) in analog form 
double C1=0;     //Salinity
int C2=0;        //Target NaCl concentration
int deadtime=6.89;  //Deadtime
int FR=0;        //Flow rate through solenoid valve
int G=0;         //Gain
int OF=0;        //Fraction of overflow that comes from DI tank
int output=0;    //Number returned from the analogRead()
int m=0;         //Mass of water in fishtank basin
int x=0;         //Mass of correction water to be added
int t=0;         //Time since the last valve was opened
int tlast=0;     //Time since last valve opened in milliseconds
int topen=0;     //Computed time for valve to stay open in ms
int UCL=0;       //Upper control limit
int LCL=0;       //Lower control limit
int sd=6.396;    //Standard Deviation

void setup()
{
Csp=;                    // given by instructor
G=;                      // received from proctor
FR=.17;                  // L/min
Serial.begin(9600);
setpoint= 1950.6*pow(Csp,.1961);
UCL= setpoint + 3*sd;
LCL= setpoint - 3*sd;
  
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  
  pinMode(1,OUTPUT);                   // printing to ye olde LCD
  Serial.write(12);
  Serial.write(132);
  Serial.write("SP=");
  Serial.write(155);
  Serial.write(setpoint,3)
  Serial.write(129);
  Serial.write("UCL=");
  Serial.write(148);
  Serial.write(UCL,3);
  Serial.write(143);
  Serial.write("LCL=");
  Serial.write(162);
  Serial.write(LCL,3);
  Serial.write(188);
  Serial.write("salty");
  Serial.write(194);
  Serial.write("current");
  Serial.write(203);
  Serial.write("DI");
  Serial.write(22);
}

void loop()
{
output=analogRead(0);
C1= 1.6671E-17*pow(output,5.0994);      // salinity as 0.001 etc

  Serial.write(175);
  Serial.write(C1);
  t=millis()-tlast



Serial.print("output= "); 
Serial.print(output);
Serial.print("    salinity= "); 
Serial.println(C1,21);

if(t>==deadtime)
{
  if(UCL<==output){
    void aboveUCL;
  }
  if(LCL>==output){
    void belowLCL;
  }
}
}

void belowLCL(){
  C2=C1+(Csp-C1)*G;                    //Target concentration
  x=(m(C1-C2))/((1-OF)*(Csp-C1));      //Mass of salty water to be added (grams)
  topen=60*(x/FR);                     //Time to leave valve open (milliseconds)
    Serial.write(169);
    Serial.write(ON);

   digitalWrite(12, HIGH);            //Open salty valve
   delay(topen);              
   digitalWrite(12, LOW);    
   delay(2000); 

    Serial.write(169);
    Serial.write(OFF);


tlast=millis();
}

void aboveUCL(){
  C2=C1-(C1-Csp)*G;                      //Target concentration
  x=(m(C1-C2))/((1-OF)*C1);              //Mass of DI water to be added (grams)
  topen=60*(x/FR);                       //Time to leave valve open (milliseconds)
    Serial.write(183);
    Serial.write(ON);

   digitalWrite(11, HIGH);               //Open DI valve
   delay(topen);              
   digitalWrite(11, LOW);    
   delay(2000); 

    Serial.write(183);
    Serial.write(OFF);

tlast=millis();
}
