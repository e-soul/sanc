/*
   Copyright 2016-2017 e-soul.org
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification, are permitted
   provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of conditions
      and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
      and the following disclaimer in the documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <TimeLib.h>
#include <WiFi101.h>
#include <WiFiUdp.h>

#include <Adafruit_FeatherOLED_WiFi.h>

const time_t NTP_REQUEST_PERIOD = (time_t) 3600;

const int NTP_DATAGRAM_SIZE = 48;

// time between 01.01.1900 and 01.01.1970, see https://tools.ietf.org/html/rfc868
const unsigned long UNIX_EPOCH_OFFSET = 2208988800UL;

const char *ssid = "YOUR_SSID";
const char *pass = "YOUR_PASSPHRASE";

const long timeZone = +10800L;

const unsigned int localUdpPort = 2390;

const char *ntpServer = "time.google.com";

byte ntpPacketBuf[NTP_DATAGRAM_SIZE] = {0};

time_t timeSinceLastNtpRequest = (time_t) NTP_REQUEST_PERIOD * -2 ;

WiFiUDP WiFiUdp;

void setup()
{
  connectSerial();

  // Adafruit Feather M0 WiFi (ATSAMD21 + ATWINC1500) pins
  WiFi.setPins(8, 7, 4, 2);
  WiFi.maxLowPowerMode();

  setupDisplay();
}

void loop()
{
  updateBattery(getBatteryVoltage());

  requestInternetTime();

  refreshDisplay();

  updateTime();

  delay(10000);
}

void requestInternetTime()
{
  if ((now() - timeSinceLastNtpRequest) > NTP_REQUEST_PERIOD)
  {
    connectWifi();
    if (!WiFiUdp.begin(localUdpPort))
    {
      // TODO report UDP error
    }
    initRequest(ntpPacketBuf);
    sendRequest(ntpPacketBuf);
    delay(1000);
    if (!receiveResponse(ntpPacketBuf))
    {
      // TODO handle packet not recieved
    }
    WiFiUdp.stop();
    disconnectWifi();

    timeSinceLastNtpRequest = now();
  }
}

void connectWifi()
{
  printWifiConnectingStatus();
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    printWifiRetryStatus();
    delay(10000);
  }
  updateRssi();
  printWifiConnectedStatus();
}

void disconnectWifi()
{
  WiFi.end();
  printWifiDisconnectedStatus();
}

