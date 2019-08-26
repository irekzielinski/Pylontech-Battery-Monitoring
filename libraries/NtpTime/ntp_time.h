#ifndef ntp_time_h
#define ntp_time_h

#include <WiFiUdp.h>

// NTP Servers:
static const char ntpServerName[] = "0.uk.pool.ntp.org";
const int timeZone = 0;
unsigned int localPort = 8888;       // local port to listen for UDP packets

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets
WiFiUDP udpNtp;

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udpNtp.beginPacket(address, 123); //NTP requests are to port 123
  udpNtp.write(packetBuffer, NTP_PACKET_SIZE);
  udpNtp.endPacket();
}


time_t getNtpTime()
{
  if(WiFi.status() != WL_CONNECTED)
  {
    return 0;
  }
  
  static bool udpStarted = false;
  if(udpStarted == false)
  {
    udpStarted = true;
    udpNtp.begin(localPort);
  }
  
  IPAddress ntpServerIP; // NTP server's ip address

  while (udpNtp.parsePacket() > 0) ; // discard any previously received packets
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  sendNTPpacket(ntpServerIP);
  delay(100);
  
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = udpNtp.parsePacket();    
    if (size >= NTP_PACKET_SIZE) {
      udpNtp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }

    delay(10);
  }
  return 0; // return 0 if unable to get the time
}
#endif //ntp_time_h