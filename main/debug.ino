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

void connectSerial()
{
  int retries = 2;
  Serial.begin(9600);
  while (!Serial && (retries > 0))
  {
    delay(1000);
    retries--;
  }
}

void printWifiConnectingStatus()
{
  if (!Serial) return;

  Serial.print("Connecting to: ");
  Serial.println(ssid);
}

void printWifiConnectedStatus()
{
  if (!Serial) return;

  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Signal strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void printWifiDisconnectedStatus()
{
  if (!Serial) return;

  Serial.println("Wifi disconnected.");
}

void printWifiRetryStatus()
{
  if (!Serial) return;

  Serial.println("Retrying Wifi connection...");
}

void printTime(unsigned long ntpEpoch)
{
  if (!Serial) return;

  Serial.print("NTP epoch " );
  Serial.println(ntpEpoch);

  Serial.print("controller system time and date: ");
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print("-");
  Serial.print(month());
  Serial.print("-");
  Serial.println(year());
}

