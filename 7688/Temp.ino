/*
 *
 * Schematic:
 *   [Ground] -- [10k-pad-resistor] -- | -- [thermistor] --[Vcc (3.3v)]
 *                                               |
 *                                          Analog Pin 
*/

// resistance at 25 degrees C
#define THERMISTORNOMINAL 10000
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// how many samples to take and average
#define NUMSAMPLES 10
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 10000 
 
// measure temperature
//THERMISTORPIN == AnalogPin
double getTemperature(int THERMISTORPIN){
 int i;
 float average;
 int samples[NUMSAMPLES];
 float thermistorResistance;
 double Temperature; 
 float error;
 
 // acquire N samples
 for (i=0; i< NUMSAMPLES; i++) {
 samples[i] = analogRead(THERMISTORPIN);
 delay(10);
 }
 
 // average all the samples out
 average = 0;
 for (i=0; i< NUMSAMPLES; i++) {
 average += samples[i];
 }
 average /= NUMSAMPLES;
 
 // convert the value to resistance
 thermistorResistance = SERIESRESISTOR * (1023 - average) / average;
 
 float steinhart;
 steinhart = thermistorResistance / THERMISTORNOMINAL; // (R/Ro)
 steinhart = log(steinhart); // ln(R/Ro)
 steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
 steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
 steinhart = 1.0 / steinhart; // Invert
 steinhart -= 273.15; // convert to C
 
 // decimal value
 //Temperature = steinhart * 10;
  error = (0.19780482*steinhart)-3.1264376;
  Temperature = (double)((int)((steinhart+error)*10)/10.0);
 return(Temperature);
}
