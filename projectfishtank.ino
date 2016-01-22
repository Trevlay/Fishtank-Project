float Csp=0;       //Setpoint in decimal form
float setpoint=0;  //Setpoint (Csp) in analog form 
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
float UCL=0;     //stands for
float LCL=0;     //52nd element
float u=0;       //UCL as wt. %
float l=0;       //LCL as wt. %
float sd=6.396;    //Standard deviation

void setup()
{
Csp=0.1;                // given by instructor
G=.8;                      // randomly determined
FR=.17;                    // L/min
m=2*pow(.8,2)*3.14;
OF=.15*m;
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
  Serial.print(Csp,3);
  Serial.write(129);
  Serial.write("LCL");
  Serial.write(148);
  Serial.print(l,3);
  Serial.write(143);
  Serial.write("UCL");
  Serial.write(162);
  Serial.print(u,3);
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
C1= 1.6671E-17*pow(output,5.0994)*100;      // salinity as 0.1 etc

  Serial.write(175);
  Serial.print(float(C1),3);
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
  x=(m*(C1-C2))/((1-OF)*(Csp-C1));      //Mass of salty water to be added (grams)
  topen=60*((x*1000)/FR);               //Time to leave valve open (milliseconds)
    Serial.write(169);
    Serial.write("ON");

   digitalWrite(12, HIGH);             //Open salty valve
   delay(topen);              
   digitalWrite(12, LOW);    
   delay(2000); 

    Serial.write(169);
    Serial.write("OFF");


tlast=millis();
}

void aboveUCL(){
  C2=C1-(C1-Csp)*G;                       //Target concentration
  x=(m*(C1-C2))/((1-OF)*C1);              //Mass of DI water to be added (grams)
  topen=60*((x*1000)/FR);                 //Time to leave valve open (milliseconds)
    Serial.write(183);
    Serial.write("ON");

   digitalWrite(11, HIGH);                //Open DI valve
   delay(400);              
   digitalWrite(11, LOW);    
   delay(2000); 

    Serial.write(183);
    Serial.write("OFF");

tlast=millis();
}

