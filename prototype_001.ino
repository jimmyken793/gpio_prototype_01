#include <Usb.h>
#include <AndroidAccessory.h>
#include <stdint.h>
#include "packet.h"
#include "board.h"

AndroidAccessory adk("Kingyoung co. ltd.", "gpio_prototype_01", "GPIO accessory prototype 01", "0.1", "http://www.kingyoung.com.tw", "0000000000000001");
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

void setup()
{
  init_pins();
  Serial.begin(115200);
  Serial.print("\n");
  Serial.print("Start\n");
  adk.powerOn();
  Serial.print("Initial setup complete.\n");
}
bool connect_status = false;

void loop()
{
  if(adk.isConnected()) {
    if(!connect_status){
      Serial.print("Connected.\n");
      connect_status=true;
    }
    cmd_packet packet;
    read_packet(&adk, &packet);
    process_packet(&packet);
  }else{
    if(connect_status){
      Serial.print("Disconnected.\n");
      connect_status=false;
    }
  }
}


