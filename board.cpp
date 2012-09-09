#include "board.h"
#include "Arduino.h"



uint8_t pin_status[MAX_BOARD_PINS];
uint8_t input_pins_count;
uint8_t input_pins[MAX_BOARD_PINS];

void init_pins(){
  input_pins_count = 0;
  for(int i=0;i<MAX_BOARD_PINS;i++){
    pin_status[i] = STATUS_UNREGISTERED;
  }
}

void reg_input_pin(uint8_t pin){
  if(pin_status[pin]!=STATUS_INPUT){
    pin_status[pin]=STATUS_INPUT;
    input_pins[input_pins_count]=pin;
    input_pins_count++;
    pinMode(pin, INPUT);
  }
}

void reg_output_pin(uint8_t pin){
  if(pin_status[pin]!= STATUS_UNREGISTERED && pin_status[pin]!= STATUS_OUTPUT){
    unreg_pin(pin);
  }
  if(pin_status[pin]!=STATUS_OUTPUT){
    pin_status[pin]=STATUS_OUTPUT;
    pinMode(pin, OUTPUT);
  }
}

void write_pin(uint8_t pin, uint8_t data){
  if(pin_status[pin]==STATUS_OUTPUT){
    digitalWrite(pin, data!=0 ? HIGH : LOW);
  }
}

void unreg_pin(uint8_t pin){
  if(pin_status[pin]==STATUS_INPUT){
    for(int i=0;i<MAX_BOARD_PINS;i++){
      if(input_pins[i]==pin){
        input_pins[i] = input_pins[input_pins_count-1];
        input_pins_count--;
        break;
      }
    }
  }
  pin_status[pin]=STATUS_UNREGISTERED;
}
