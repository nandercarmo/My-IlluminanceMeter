/*
 *  DataAcquisition.ino
 *  Universidade Federal de Minas Gerais
 *  Created on: Fev 2021
 *  Author: channelsCountander Carmo, Igor Radichi 
 *  Version: 1.0
 *  License: MIT
 */

const int channelsCount = 2; // number of channels
const int dataBufferSize = 300; // size of the data buffers
bool isProcessing = false; // flag to start data processing
int dataVector[channelsCount][dataBufferSize]; // data vectors for each channel
int dataReadCount = 0; // controls the number of samples

void setup() {

  Serial.begin(115200);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  ADMUX = 0x00; // MUX[3:0] = 0000 -> select analog channel 0, ADLAR = 0 -> AD samples are right adjusted 
  ADMUX |= 0x40; // REFS[1:0] = 01, set voltage reference to AVcc

  ADCSRA = 0x00;
  ADCSRA |= 0x07; // ADPS[2:0] = 111, set prescaler to 128 -> fs = 4807.69Hz (2 channels)
  ADCSRA |= 0x08; // ADIE = 1, enable ADC interrupts
  ADCSRA |= 0x20; // ADATE = 1, enable auto-trigger

  ADCSRB = 0x00; // ACME = 0, ADTS[2:0] = 000 -> trigger source = free running mode

  DIDR0 = 0xFF; // disablethe ADC digital input buffers

  SREG |= 0x80; // enable global interrupts

  ADCSRA |= 0x80; // ADEchannelsCount = 1, enable AD converter
  ADCSRA |= 0x40;// ADSC = 1, start AD conversion

  Serial.println("$ Setup finished!");
}

void loop() {

  int i;
  char cmd;

  if(isProcessing) {

    char message[100] = "";
    sprintf(message, "$ isProcessing = %s\n", isProcessing ? "true" : "false");
    Serial.println(message);

    noInterrupts();
    isProcessing = false;
    interrupts();
  }
}

ISR(ADC_vect) {

  //Serial.println("$ ISR");

  int sample, CH;
  
  sample = ADCL; // read the lower byte
  sample += ADCH << 8; // read the upper byte shift by 8 bits left

  // char message[100] = "";
  // sprintf(message, "$ isProcessing = %s\n", isProcessing ? "true" : "false");
  // Serial.println(message);

  if(!isProcessing) {

    CH = ADMUX & 0x0F; // get AD channel
    dataVector[CH][dataReadCount] = sample; // store data read
    
    if(++CH < channelsCount) ADMUX += 1; // verify if all channels were acquired, if not, go to the next channel
    else {

      ADMUX &= 0xF0; // if so, turn to channel 0
      dataReadCount++; // update the number of samples
    }

    if(dataReadCount ==  dataBufferSize) {

      dataReadCount = 0; // data vector full, restart dataReadCount
      isProcessing = true; // set the flag to start processing
    }
    
  }
}
