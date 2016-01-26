float Csp=0;       //Setpoint in decimal form
float setpoint=0;  //Setpoint (Csp) in analog form 
double C1=0;     //Salinity
float C2=0;        //Target NaCl concentration
float deadtime=6.89;  //Deadtime
float FR=0;        //Flow rate through solenoid valve
float G=0;         //Gain
float OF=0;        //Fraction of overflow that comes from DI tank
int output=0;      //Number returned from the analogRead()
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

void setup()
{
Csp=0.001;                // given by instructor
G=.8;                      // randomly determined
FR=.17;                    // L/min ************
m=65.9;                   // mass of water two inches deep (g)
OF=.15;
Serial.begin(9600);
setpoint= (1950.6*pow(Csp,.1961));
UCL= setpoint + 3*sd;
LCL= setpoint - 3*sd;
u= 1.6671E-17*pow(UCL,5.0994);
l= 1.6671E-17*pow(LCL,5.0994);
  
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(4,INPUT);
  
  pinMode(1,OUTPUT);                   // printing to ye olde LCD
  Serial.write(12);
  Serial.write(136);
  Serial.write("SP");
  Serial.write(155);
  Serial.print(Csp*100,3);
  Serial.write(129);
  Serial.write("LCL");
  Serial.write(148);
  Serial.print(l*100,3);
  Serial.write(143);
  Serial.write("UCL");
  Serial.write(162);
  Serial.print(u*100,3);
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
output=analogRead(4);
C1= 1.6671E-17*pow(output,5.0994);      // current salinity as decimal (wt %)

  Serial.write(175);
  Serial.print(float(C1*100),3);
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
}

void belowLCL(){
  C2=C1+(Csp-C1)*G;                     //Target concentration
  x=(m*(C2-C1))/((1-OF)*(.01-C1));      //Mass of salty water to be added (grams)
  topen=60*(x/FR);                      //Time to leave valve open (milliseconds)
  
  
  
    Serial.write(169);                  //Display salty valve on
    Serial.write("ON");
    Serial.write(183);
    Serial.write("OFF");                //Display DI valve off
    Serial.write(22);

   digitalWrite(12, HIGH);              //Open salty valve
   delay(topen);              
   digitalWrite(12, LOW);    
   delay(2000); 

    Serial.write(169);                  //Display both valves off
    Serial.write("OFF");                 
    Serial.write(183);
    Serial.write("OFF");
    Serial.write(22);
    Serial.write(22);
    

tlast=millis();
}

void aboveUCL(){
  C2=C1-(C1-Csp)*G;                       //Target concentration
  x=(m*(C1-C2))/((1-OF)*C1);              //Mass of DI water to be added (grams)
  topen=60*(x/FR);                 //Time to leave valve open (milliseconds)
  
    Serial.write(169);
    Serial.write("OFF");                  //Display salty valve off
    Serial.write(183);
    Serial.write("ON");                   //Display DI valve on
    Serial.write(22);

   digitalWrite(11, HIGH);                //Open DI valve
   delay(topen);              
   digitalWrite(11, LOW);    
   delay(2000); 

    Serial.write(169);                    //Display both valves off
    Serial.write("OFF");
    Serial.write(183);
    Serial.write("OFF");
    Serial.write(22);

tlast=millis();
}
