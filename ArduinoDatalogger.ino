#include <Time.h>
#include "Adafruit_MAX31855.h"

/*
Datalog sketch

This sketch will take values from sensors and prints it out to 
the Serial Monitor in a format that is friendly for excel files.
*/

//Define the tiner interval between each reads
#define TIME_INTERVAL  1 

//Define the number of ADC ports you will be using
#define NO_ADC_PORTS   1  

//Define variables here
unsigned long startTime, currentTime;
unsigned long timeInterval = TIME_INTERVAL * 1000UL; 

//Define Pins for Thermocouple IC
int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);
int adcPort[5];

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //Initialize all the ADC ports
  Serial.print("Time [ms],");
  for(int i=0; i<NO_ADC_PORTS; i++)
  {
    String adcVal = "Analog Sensor" + String((int)i);
    Serial.print(adcVal);
    Serial.print(",");
  }
  Serial.println("Thermocouple [F]");
  
  startTime = millis();
}

void loop() 
{
    // put your main code here, to run repeatedly: 
    currentTime = millis(); // Start counting the time
    float displayTime = currentTime/1000;
    // Post ADC values on Terminal
    if(currentTime - startTime > timeInterval)
    {
      // Post analog sensor values
      Serial.print(displayTime);
      Serial.print(",");
      for(int i=0; i<NO_ADC_PORTS; i++)
      {
        adcPort[i] = analogRead(i);
        Serial.print(adcPort[i], DEC);
        Serial.print(",");
      }
      double f = thermocouple.readFarenheit();
      Serial.println(f);
    
      startTime = millis();  // Reset the counter
    }
}
