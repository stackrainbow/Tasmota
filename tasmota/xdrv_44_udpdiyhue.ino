
#define XDRV_44                44

#include "UdpListener.h"
WiFiUDP UdpCtxA;

struct DiyHueState {
  bool isListening = false;
} diyHueState;

void UdpDiyHueInit()
{
    AddLog_P2(LOG_LEVEL_INFO, PSTR("Hello from UdpDiyHueInit funct"));
    UdpCtxA.begin(2100);
    AddLog_P2(LOG_LEVEL_INFO, PSTR("Init UDP socket"));
}

void UdpDiyHueLoop()
{
  int packetSize = UdpCtxA.parsePacket(); //begin parsing udp packet
  if (packetSize) {
    byte packetBuffer[8];
    UdpCtxA.read(packetBuffer, packetSize);
    if (((packetBuffer[1])+(packetBuffer[2])+(packetBuffer[3])) == 0) {
      light_controller.changeBri(0);
    }
    else {
      light_controller.changeRGB((packetBuffer[1]), (packetBuffer[2]), (packetBuffer[3]));
      //light_controller.changeDimmer((packetBuffer[1]) / 255 * 100);
    }
  }
}

bool Xdrv44(uint8_t function)
{
  bool result = false;
  switch(function){
      case FUNC_PRE_INIT:
        UdpDiyHueInit();
        break;
      case FUNC_LOOP:
        UdpDiyHueLoop();
        break;
  }
  return result;
}