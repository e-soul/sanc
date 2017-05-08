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

void initRequest(byte *buf)
{
  memset(buf, 0, NTP_DATAGRAM_SIZE);
  // see https://tools.ietf.org/html/rfc5905
  buf[0] = 0b00100011; // LI - 00 VN - 100 Mode - 011
  buf[1] = 2; // stratum
}

void sendRequest(byte *buf)
{
  WiFiUdp.beginPacket(ntpServer, 123);
  WiFiUdp.write(buf, NTP_DATAGRAM_SIZE);
  WiFiUdp.endPacket();
}

boolean receiveResponse(byte *buf)
{
  boolean packetReceived = WiFiUdp.parsePacket();
  if (packetReceived)
  {
    WiFiUdp.read(buf, NTP_DATAGRAM_SIZE);

    unsigned long ntpEpoch = getNtpEpoch(buf);
    time_t unixEpoch = (time_t) (ntpEpoch - UNIX_EPOCH_OFFSET);
    unixEpoch = applyTimeZone(unixEpoch);

    // set the controller system time
    setTime(unixEpoch);

    printTime(ntpEpoch);
  }
  return packetReceived;
}

unsigned long getNtpEpoch(byte *buf)
{
  unsigned long ntpEpoch = buf[40];
  for (int i = 41; i < 44; i++)
  {
    ntpEpoch <<= 8;
    ntpEpoch |= buf[i];
  }
  return ntpEpoch;
}

