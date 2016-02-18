float Csp=0;       //Setpoint in decimal form
float setpoint=0;  //Setpoint (Csp) in analog form 
double C1=0;     //Salinity
float C2=0;        //Target NaCl concentration
float deadtime=9.89;  //Deadtime
float FR=0;        //Flow rate through solenoid valve
float G=0;         //Gain
float OF=0;        //Fraction of overflow that comes from DI tank
float output=0;    //Number returned from the analogRead()
float m=0;         //Mass of water in fishtank basin
float x=0;         //Mass of correction water to be added
float t=0;         //Time since the last valve was opened
float tlast=0;     //Time since last valve opened in milliseconds
float topen=0;     //Computed time for valve to stay open in ms
float UCL=0;     //stands for
float LCL=0;     //52nd element
float u=0;       //UCL as decial
float l=0;       //LCL as decimal
float sd=6.396;    //Standard deviation
float temp=0;
int analogT=0;
float tempsetpoint=0;
float tempset=0;
float tempsd=1.465390194;
float tempUCL=0;
float tempLCL=0;
float tempU=0;
float tempL=0;

void setup()
{
Csp=0.001;                // given by instructor
G=.8;                      // randomly determined
FR=.39;                    // L/min
m=65.9;                   // mass of water two inches deep (g)
OF=.15;
Serial.begin(9600);
setpoint= (10598*pow(Csp,.4776));
UCL= setpoint + 3*sd;
LCL= setpoint - 3*sd;
u= 3.732301E-9*pow(UCL,2.093802);
l= 3.732301E-9*pow(LCL,2.093802);

tempsetpoint=25;           //setpoint given by instructor degrees celsius
tempset=8.5499*tempsetpoint+270.43;    //temperature setpoint analog 
tempUCL=tempset+3*tempsd;  //temperature UCL analog
tempLCL=tempset-3*tempsd;   //temperature LCL analog
tempU=.11696*tempUCL-31.6296;  //temperature UCL degrees celsius
tempL=.11696*tempLCL-31.6296;  //temperature LCL degrees celsius
  
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
  
  pinMode(1,OUTPUT);                   // printing to ye olde LCD
  Serial.write(12);
  Serial.write(148);
  Serial.write("S:");
  Serial.write(139);
  Serial.write("SP");
  Serial.write(132);
  Serial.write("LCL");
  Serial.write(151);
  Serial.print(l*100,3);
  Serial.write(143);
  Serial.write("UCL");
  Serial.write(163);
  Serial.print(u*100,3);
  Serial.write(139);
  Serial.write(SP);
  Serial.write(157);
  Serial.print(Csp*100,3);
Serial.write(168);
Serial.write("T:");
Serial.write(172);
Serial.print(tempL,1);
Serial.write(178);
Serial.print(tempsetpoint,1);
Serial.write(184);
Serial.print(tempU,1);
Serial.write(203);
Serial.write("H=");
  Serial.write(22);
}

void loop()
{
pinMode(8,HIGH);
delay(100);
output=analogRead(1);
pinMode(8,LOW);


C1= 3.732301E-9*pow(output,2.093802);      // current salinity as decimal (wt %)

 analogT=analogRead(2);     //temperature analog
 temp=.11696*analogT-31.6296; //temperature degrees celsius

  Serial.write(188);
  Serial.write("S=");
  Serial.write(190);
  Serial.print(float(C1*100),3);
  Serial.write(196);
  Serial.write("T=");
  Serial.print(temp,1);
  t=millis()-tlast;

//Serial.print("output= "); 
//Serial.print(output);
//Serial.print("    salinity= "); 
//Serial.println(C1,21);

//  delay(350);   // not necessary, may effect millis()

if(t>=deadtime)
{
  if(UCL<=output){
    aboveUCL();
}
  if(LCL>=output){
    belowLCL();
}
}

 if(analogT<tempLCL){
  digitalWrite(10,HIGH);

  Serial.write(205);
  Serial.write("on ");
  //display that heater is on on the LCD screen
  }

 if(analogT>tempUCL){
  digitalWrite(10,LOW);

  Serial.write(205);
  Serial.write("off");
  //display that the heater is off on the LCD screen
  }
}

void belowLCL(){
  C2=C1+(Csp-C1)*G;                     //Target concentration
  x=(m*(C2-C1))/((1-OF)*(.01-C1));      //Mass of salty water to be added (grams)
  topen=60*(x/FR);                      //Time to leave valve open (milliseconds)

   digitalWrite(12, HIGH);              //Open salty valve
   delay(topen);              
   digitalWrite(12, LOW);    
   delay(2000); 

tlast=millis();
}

void aboveUCL(){
  C2=C1-(C1-Csp)*G;                       //Target concentration
  x=(m*(C1-C2))/((1-OF)*C1);              //Mass of DI water to be added (grams)
  topen=60*(x/FR);                 //Time to leave valve open (milliseconds)

   digitalWrite(11, HIGH);                //Open DI valve
   delay(topen);              
   digitalWrite(11, LOW);    
   delay(2000); 

tlast=millis();
}
