#ifndef KY_PACKET_H
#define KY_PACKET_H

#include <Usb.h>
#include <AndroidAccessory.h>
#include <stdint.h>

#define MAX_PACKET_SIZE 14

#define TYPE_REG_READ 0x01
#define TYPE_REG_WRITE 0x02
#define TYPE_UNREG 0x03
#define TYPE_VALUE 0x04
#define TYPE_SET 0x05
#define TYPE_RESET 0xFF

typedef struct{
  uint8_t type;
  uint8_t length;
  uint8_t data[MAX_PACKET_SIZE];
} cmd_packet;

int read_packet(AndroidAccessory* adk, cmd_packet *packet);
int write_packet(AndroidAccessory* adk, cmd_packet *packet);
int process_packet(cmd_packet *packet);

#endif
