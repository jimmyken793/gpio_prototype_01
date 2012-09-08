#include <Usb.h>
#include <AndroidAccessory.h>
#include "packet.h"

#define  LED_RED       12

AndroidAccessory adk("Kingyoung co. ltd.", "unnamed", "unnamed product", "0.1", "http://www.kingyoung.com.tw", "0000000000000001");
/*
USB Usb;
ADK adk(&Usb, "Google, Inc.",
"DemoKit",
"DemoKit Arduino Board",
"1.0",
"http://www.android.com",
"0000000012345678");
*/
void setup();
void loop();


void init_leds()
{
  digitalWrite(LED_RED, 1);
  pinMode(LED_RED, OUTPUT);
}

void setup()
{
  Serial.begin(115200);
  Serial.print("\n");
  Serial.print("Start\n");
  init_leds();
  /*while (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    delay(1000);
  }*/
  adk.powerOn();
  Serial.print("Initial setup complete.\n");
}


int process_packet(cmd_packet *packet){
  switch(packet->type){
    
  }
}

int read_packet(AndroidAccessory* adk, cmd_packet *packet){
  uint8_t msg[MAX_PACKET_SIZE];
  adk->read(msg, 2);
  packet->type = msg[0];
  packet->length = msg[1];
  adk->read(packet->data, packet->length);
}

void loop()
{
  if(adk.isConnected()) {
    uint8_t msg[1];
    uint16_t len = adk.read(msg, sizeof(msg), 1);
    if(len > 0) {
      Serial.print(F("\r\nData Packet: "));
      Serial.print(msg[0]);
    }
  } 
  else{
  }
}


