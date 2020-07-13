
//SN74LS164N Pin 8 (CLK)
#define CLOCK_PIN 24

//SN74LS164N Pin 9 (CLR)
#define CLEAR_PIN 25 

//SN74LS164N Pin 1 (A), tied to Pin 2 (B) on the board
#define INPUT_PIN 26

//SN74LS164N Pins Qa - Qe have an LED and 220 Ohm resister each 

//Short hand for unsigned int
#define U_INT unsigned int

#define DEBUG 1

/** 
 *  Hardware interface for outputing to the SN74LS164 for the Arduino 
 */
class SN74LS164{

  public:
    SN74LS164();
    void writeBit(U_INT bitToWrite);
    void writeByte(U_INT byteToWrite);

  private:
    void pulseClock();
    void writeInput(U_INT input);
    void init();
};

/**
 * Constructor
 */
SN74LS164::SN74LS164(){
  
  init();
}

/**
 * Init 
 * Set pin modes and initial state
 * Should be called first and can be called to reset state 
 */
void SN74LS164::init(){

  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(CLEAR_PIN, OUTPUT);
  pinMode(INPUT_PIN, OUTPUT);

  //Start with pins off (n.b. Clear is active low)
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(INPUT_PIN, LOW);

  //Clear output
  digitalWrite(CLEAR_PIN, HIGH);
  digitalWrite(CLEAR_PIN, LOW);
  digitalWrite(CLEAR_PIN, HIGH);

  
}

/**
 * Send a clock pulse
 *
 * Simulate a clock because we don't want to use a timer
 */
void SN74LS164::pulseClock(){

  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);

}

/**
 * Send a bit to the serial in of the chip
 */
void SN74LS164::writeInput(U_INT input){

    if(input == 0)
      digitalWrite(INPUT_PIN, LOW);
    else
      digitalWrite(INPUT_PIN, HIGH);
}

/**
 * Send the serial input and pulse the clock to load the value
 */
void SN74LS164::writeBit(U_INT bitToWrite){

  writeInput(bitToWrite);
  pulseClock();
}

/**
 * Write 8 bits to the chip, one bit at a time
 */
void SN74LS164::writeByte(U_INT byteToWrite){

    U_INT bitToWrite = 0;
    char  bitsString[9];

    //Initialize last char to ensure string is null terminated
    bitsString[8] = '\0';

    //For each bit in the byte
    for(U_INT bitIndex = 0; bitIndex < 8; bitIndex++)
    {
      //Shift by bit index to get desired bit and then mask
      bitToWrite = (byteToWrite >> bitIndex) & 0x01;
      
      writeBit(bitToWrite);

      //Reverse order of bits to display properly
      bitsString[7 - bitIndex] = (bitToWrite == 0) ? '0' : '1';
     
    }

    if(DEBUG != 0)
    {
      Serial.print(" Bits: ");
      Serial.print(bitsString);
      Serial.println("");
    }
}
