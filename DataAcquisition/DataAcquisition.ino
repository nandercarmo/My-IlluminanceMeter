/*
 *  DataAcquisition.ino
 *  Universidade Federal de Minas Gerais
 *  Created on: Fev 2021
 *  Author: Nander Carmo, Igor Radichi 
 *  Version: 1.0
 *  License: MIT
 */

const uint8_t STOP_READ = 0x7F;
const uint8_t START_READ = 0x80;

const uint8_t channelsCount = 1; // number of channels
const uint8_t dataBufferSize = 100; // size of the data buffers
uint8_t isProcessing = false; // flag to start data processing
uint16_t dataVector[channelsCount][dataBufferSize]; // data vectors for each channel
uint32_t dataReadCount = 0; // controls the number of samples

uint8_t RESET = 0x00; // Leitura pausada
uint8_t ANALOG_CHANNEL = 0x00; // Leitura pausada
uint8_t VOLTAGE_REF = 0x40; // Leitura pausada
uint8_t PRESCALER = 0x07; // Leitura pausada
uint8_t EN_ADC_IRQ = 0x08; // Leitura pausada
uint8_t EN_ADC_AUTO_TRIGGER = 0x20; // Leitura pausada
uint8_t FREE_RUNNING_MODE = 0x00; // Leitura pausada
uint8_t DIS_ADC_DIG = 0xFF; // Leitura pausada
uint8_t EN_GLOBAL_IRQ = 0x80; // Leitura pausada
uint8_t MUST_READ = START_READ; // Leitura pausada
uint8_t ADC_START = 0x40; // Leitura pausada

void handleSerial();

void setup() {

  Serial.begin(19200);
    
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
}

void loop() {

  handleSerial();
  
  while(MUST_READ == START_READ) {

    if(isProcessing) {

      for(uint8_t i = 0; i < channelsCount; i++) {
  
        for(uint8_t j = 0; j < dataBufferSize; j++) {
  
          Serial.println((int) dataVector[i][j]);
          delay(1);
        }
      }
  
      noInterrupts();
      isProcessing = false;
      interrupts();
    
    } else handleSerial();
  }
}

void handleSerial() {

  if(Serial.available()) {
  
    uint8_t readChar = Serial.read();

    if(readChar == START_READ) {

      while(!Serial.available()) continue;

      PRESCALER = Serial.read();

      while(!Serial.available()) continue;

      ANALOG_CHANNEL = Serial.read();
      MUST_READ = START_READ;
      
    } else MUST_READ = STOP_READ;

    resetRegisters();
  }
}

void resetRegisters() {

  noInterrupts();

  ADMUX = ANALOG_CHANNEL; // MUX[3:0] = 0000 -> select analog channel 0, ADLAR = 0 -> AD samples are right adjusted 
  ADMUX |= VOLTAGE_REF; // REFS[1:0] = 01, set voltage reference to AVcc

  ADCSRA = RESET;
  ADCSRA |= PRESCALER; // ADPS[2:0] = 111, set prescaler to 128 -> fs = 4807.69Hz (2 channels)
  ADCSRA |= EN_ADC_IRQ; // ADIE = 1, enable ADC interrupts
  ADCSRA |= EN_ADC_AUTO_TRIGGER; // ADATE = 1, enable auto-trigger

  ADCSRB = FREE_RUNNING_MODE; // ACME = 0, ADTS[2:0] = 000 -> trigger source = free running mode

  DIDR0 = DIS_ADC_DIG; // disable the ADC digital input buffers

  SREG |= EN_GLOBAL_IRQ; // enable global interrupts

  ADCSRA |= MUST_READ; // ADEN = 1, enable AD converter
  ADCSRA |= ADC_START;// ADSC = 1, start AD conversion

  interrupts();
}

ISR(ADC_vect) {

  uint16_t sample;
  uint8_t CH;
  
  sample = ADCL; // read the lower byte
  sample += ADCH << 8; // read the upper byte shift by 8 bits left

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
