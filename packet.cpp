#include "packet.h"
#include "board.h"

int process_packet(cmd_packet *packet){
  switch(packet->type){
    case TYPE_REG_READ:
      reg_input_pin(packet->data[0]);
    break;
    case TYPE_REG_WRITE:
      reg_output_pin(packet->data[0]);
    break;
    case TYPE_UNREG:
      unreg_pin(packet->data[0]);
    break;
    case TYPE_SET:
      write_pin(packet->data[0],packet->data[1]);
    break;
    case TYPE_RESET:
    break;
  }
  return 0;
}

int read_packet(AndroidAccessory* adk, cmd_packet *packet){
  uint8_t msg[2];
  int len = adk->read(msg, 2);
  if(len != 2){
    return -1;
  }
  packet->type = msg[0];
  packet->length = msg[1];
  if(packet->length <= MAX_PACKET_SIZE){
    adk->read(packet->data, packet->length);
  }
  return 0;
}
