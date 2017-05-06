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

Adafruit_FeatherOLED_WiFi oled = Adafruit_FeatherOLED_WiFi();

void setupDisplay()
{
  oled.init();
  oled.clearDisplay();

  oled.setBatteryIcon(true);
  oled.setBatteryVisible(true);
  oled.setBattery(.0f);

  oled.setConnectedVisible(false);
  oled.setConnected(true);

  oled.setRSSIVisible(true);

  oled.setIPAddressVisible(false);
  oled.setIPAddress(0);

  oled.refreshIcons();
  oled.clearMsgArea();

  oled.setTextSize(3);
  oled.println("LOADING");
  oled.setTextSize(1);

  oled.display();
}

void updateRssi()
{
  // Received Signal Strength in dBm (0 to -100, closer to 0 is better)
  oled.setRSSI(WiFi.RSSI());
}

void updateBattery(float voltage)
{
  oled.setBattery(voltage);
}

void updateTime()
{
  oled.setTextSize(3);
  oled.clearMsgArea();
  oled.print(" ");
  byte hours = (byte) hour() + timeZone;
  if (hours < (byte) 10)
  {
    oled.print("0");
  }
  oled.print(hours);
  oled.print(":");
  byte minutes = minute();
  if (minutes < (byte) 10)
  {
    oled.print("0");
  }
  oled.println(minutes);
  oled.setTextSize(1);
  oled.display();
}

void refreshDisplay()
{
  oled.refreshIcons();
}

