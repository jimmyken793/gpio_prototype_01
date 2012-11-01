#ifndef KY_BOARD_H
#define KY_BOARD_H

#include <Usb.h>
#include <AndroidAccessory.h>
#include <stdint.h>

#define MAX_BOARD_PINS 49
#define STATUS_UNREGISTERED 0x00
#define STATUS_INPUT 0x01
#define STATUS_OUTPUT 0x02

extern uint8_t pin_status[MAX_BOARD_PINS];
extern uint8_t input_pins_count;
extern uint8_t input_pins[MAX_BOARD_PINS];

void init_pins();
void reg_input_pin(uint8_t pin);
void reg_output_pin(uint8_t pin);
void unreg_pin(uint8_t pin);
void write_pin(uint8_t pin, uint8_t data);
void send_status(AndroidAccessory* adk);
#endif
