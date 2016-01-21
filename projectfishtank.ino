double salinity;
int output;

void setup()
{
Serial.begin(9600);

}

void loop()
{
// output=analogRead (0);
output=500;
salinity= 1.6671E-17*pow(output,5.0994);
Serial.print("output= "); Serial.print(output);
Serial.print("    salinity= "); Serial.println(salinity,21);


// In setup, compute UCL and LCL given a certain setpoint. Then, in loop, create if(salinity>=[UCL/LCL]) x2 and input
// solenoid valve program ~should be on Carli's pc or on pp.

}
