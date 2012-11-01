#include "packet.h"
#include "board.h"
#include <stdio.h>
int process_packet(cmd_packet *packet){
  char buf[16];
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
    default:
      return -1;
  }
  return 0;
}

int read_packet(AndroidAccessory* adk, cmd_packet *packet){
  uint8_t msg[2];
  int read_len = 0;
  while(read_len != 2){
    int len = adk->read(msg+read_len, 2-read_len, 1);
    if(len < 0){
      return -1;
    }else{
      read_len += len;
    }
  }
  packet->type = msg[0];
  packet->length = msg[1];
  
  Serial.print("packet:");
  Serial.print(packet->type);
  Serial.print(",");
  Serial.print(packet->length);
  Serial.print("\n");
  if(packet->length <= MAX_PACKET_SIZE){
    int read_len = 0;
    int len;
    while((len = adk->read(packet->data+read_len, packet->length-read_len, 1))>=0){
      read_len += len;
      if(read_len > packet->length){
        return -1;
      }else if(read_len == packet->length){
        break;
      }
    }
  }
  return 0;
}

int write_packet(AndroidAccessory* adk, cmd_packet *packet){
  adk->write(&(packet->type), 1);
  adk->write(&(packet->length), 1);
  adk->write(packet->data, packet->length);
}
