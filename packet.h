

#ifndef KY_PACKET_H
#define KY_PACKET_H
#define MAX_PACKET_SIZE 14
typedef struct{
  uint8_t type;
  uint8_t length;
  uint8_t data[MAX_PACKET_SIZE - 2];
} cmd_packet;

#endif
