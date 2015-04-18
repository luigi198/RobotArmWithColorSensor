#include <Wire.h>
#include "Adafruit_TCS34725.h"

int minValueClose = 3000; //Ajusta que tan cerca debe estar el objeto
int minValueGreen = 2500; //Ajusta la cantidad mínima de verde para decidir si es amarillo
uint16_t r, g, b, c, colorTemp, lux;

boolean isRed() 
{
  if (r > g && r > b && r > minValueClose) 
  {
    return true;
  } 
  else
  {
    return false;
  }
}

boolean isYellow() 
{
  if (b < r && b < g && r > minValueClose && g > minValueGreen)
  {
    return true;
  }
  else
  {
    return false;
  }
}



/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);
  
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

}

void loop(void) {
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);
  
//  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
//  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
//  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
//  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
//  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
//  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
//  Serial.println(" ");
  
  if(isRed() && isYellow())
  {
    int aux = r - g;
    if (aux < 0 )
    {
      aux = aux * -1;
    }
    
    if (aux > 300 && aux < 700) 
    {
      Serial.print("Is Yellow!");
    } 
    else
    {
      Serial.print("Is Red!");
    } 
  } 
  else if (isRed()) 
  {
    Serial.print("Is Red!");
  }
  else if (isYellow())
  {
    Serial.print("Is Yellow!");
  }
  else 
  {
    Serial.print("No idea what color it is. :P");
  }
  
  Serial.println("");
  
}
