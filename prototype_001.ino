#include <Usb.h>
#include <AndroidAccessory.h>
#include <stdint.h>
#include "packet.h"
#include "board.h"

AndroidAccessory adk("Kingyoung co. ltd.", "gpio_prototype_01", "GPIO accessory prototype 01", "0.1", "http://www.kingyoung.com.tw", "0000000000000001");

void setup()
{
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
      init_pins();
    }
    cmd_packet packet;
    if(read_packet(&adk, &packet)==0){
      process_packet(&packet);
    }
    send_status(&adk);
  }else{
    if(connect_status){
      Serial.print("Disconnected.\n");
      connect_status=false;
    }
  }
  delay(10);
}



