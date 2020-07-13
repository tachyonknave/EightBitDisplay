#include "SN74LS164.h"

SN74LS164* display = NULL;

void setup() {
  
  Serial.begin(115200);

  display = new SN74LS164();
}


void loop() {

  for(unsigned int outputValue = 0; outputValue < 0xFF; outputValue++)
  {    
    Serial.print("Output Value: ");
    Serial.println(outputValue);

    display->writeByte(outputValue);

    //Wait 500ms
    delay(500);
    
  }
  
}
