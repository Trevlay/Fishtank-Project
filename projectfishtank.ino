int Csp=0;       //Setpoint
int C1=0;        //Initial NaCl concentration 
int C2=0;        //Target NaCl concentration
int deadtime=0;  //Deadtime
int FR=0;        //Flow rate through solenoid valve
int G=0;         //Gain
int OF=0;        //Fraction of overflow that comes from DI tank
int output=0;    //Number returned from the analogRead()
int m=0;         //Mass of water in fishtank basin
int x=0;         //Mass of correction water to be added
int t=0;         //Time since the last valve was opened
int tlast=0;     //Time since last valve opened in milliseconds
int topen=0;     //computed time for valve to stay open in ms
int setpoint=0;  //For fun
int UCL=0;       //Stands for U Can't Lel
int LCL=0;       // 52nd element
int sd=6.396;         // 
double salinity=0;

void setup()
{
Csp=;                    // given by instructor
Serial.begin(9600);
setpoint= 1950.6*pow(Csp,.1961);
UCL= setpoint + 3*sd;
LCL= setpoint - 3*sd;
  pinMode(1,OUTPUT);                   // printing to ye olde LCD
  Serial.write(12);
  Serial.write(128);
  Serial.write("Setpoint=");
  Serial.write(1)
  Serial.write(152);
  Serial.write("UCL=");
  Serial.write(189);
  Serial.write("LCL=");
  Serial.write(22);
}

void loop()
{
output=500;
salinity= 1.6671E-17*pow(output,5.0994);

Serial.print("output= "); 
Serial.print(output);
Serial.print("    salinity= "); 
Serial.println(salinity,21);


// In setup, compute UCL and LCL given a certain setpoint. Then, in loop, create if(salinity>=[UCL/LCL]) x2 and input
// solenoid valve program ~should be on Carli's pc or on pp.

}
