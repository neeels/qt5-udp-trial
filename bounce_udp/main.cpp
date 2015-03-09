/*
Listen on port localhost port 1337 to receive UDP datagrams.
Read the datagram up to the first comma, and if these bytes match one of few
listed strings, repost the entire datagram to the corresponding IP address,
as listed. The list is hardcoded.


This file is part of qt5-udp-trial,
a short trial in Qt5 basics and networking API (no GUI)
Copyright (C) 2015  Neels Hofmeyr
http://hofmeyr.de
http://github.com/neeels/qt5-udp-trial

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


To test, run the ./test.sh script, or run manually:

     ./bounce_udp

     # in another terminal:
     netcat -l -u -p 1338

     # in yet another terminal:
     netcat -l -u -p 1339

     # and in yet another terminal:
     nc6 -l -u -p 1340

     # and in the final terminal, send various datagrams:
     netcat -u localhost 1337
     # and then type:
     FOO,1,2,3
     BAR,asdf,asd,fasd,f

     # in first terminal, this should print something like:
     > ./bounce_udp 
     Listening on port 1337

     received 10 bytes:
     [[[
     FOO,1,2,3

     ]]]
     Redirect token: 'FOO'
     Sending to 127.0.0.1, port 1338
     Sent 10 bytes.
     Sending to 127.0.0.1, port 1339
     Sent 10 bytes.

     received 20 bytes:
     [[[
     BAR,asdf,asd,fasd,f

     ]]]
     Redirect token: 'BAR'
     Sending to ::1, port 1340
     Sent 20 bytes.

     received 9 bytes:
     [[[
     BAZ,lala

     ]]]
     Redirect token: 'BAZ'
     Unknown redirect token. Ignoring datagram.

     received 20 bytes:
     [[[
     the quick brown fox

     ]]]
     No redirect token in this datagram. Ignoring.

*/

#include <qiostream.h>
#include <QUdpSocket>
#include <QThread> // for usleep


/*! Send a UDP datagram.
    /param toAddress  A numeric IP address to send to (IPv4 or IPv6).
    /param port       Which port to send to.
    /param datagram   The datagram data to send.
 */
void sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram)
{
  QUdpSocket udpSocket;

  qout << "Sending to " << toAddress << ", port " << port << endl;

  QHostAddress toAddressObj(toAddress);

  int sent = udpSocket.writeDatagram(datagram, toAddressObj, port);

  qout << "Sent " << sent << " bytes." << endl;

  if (sent != datagram.size()) {
    qerr << "*** Mismatch: datagram size = " << datagram.size() << ", sent bytes = " << sent << endl;
  }
}

int main(void) {
  int port = 1337;

  QUdpSocket udpSocket;

  if (! udpSocket.bind(port)) {
    qerr << "*** Failed to bind to port " << port << endl;
    return 1;
  }

  qout << "Listening on port " << port << endl;

  while (1){

    if (udpSocket.hasPendingDatagrams()) {
      qout << endl;

      const int size = udpSocket.pendingDatagramSize();

      QByteArray datagram(size, 0);

      int got = udpSocket.readDatagram(datagram.data(), datagram.size());

      qout << "received " << got << " bytes:" << endl;
      qout << "[[[\n" << datagram << "\n]]]" << endl;

      int tokenEnd = datagram.indexOf(',');

      if ((tokenEnd <= 0) || (tokenEnd >= datagram.size())) {
        qout << "No redirect token in this datagram. Ignoring." << endl;
        continue;
      }

      QByteArray redirectTokenBytes(datagram.data(), tokenEnd);
      QString redirectToken(redirectTokenBytes);
      qout << "Redirect token: '" << redirectToken << "'" << endl;

      if (redirectToken.compare("FOO") == 0) {
        sendUdpDatagram("127.0.0.1", 1338, datagram);
        sendUdpDatagram("127.0.0.1", 1339, datagram);
      }
      else
      if (redirectToken.compare("BAR") == 0) {
        sendUdpDatagram("::1", 1340, datagram);
      }
      else {
        qout << "Unknown redirect token. Ignoring datagram." << endl;
      }
    }
    else {
      // don't eat CPU
      udpSocket.thread()->usleep(1e3); // 1e6 == 1 second
      // Maybe the Qt event handling would make sense instead of this.
    }
  }

  // todo: catch ctrl-C and close socket gracefully

  udpSocket.close();
  qout << "Stopped listening." << endl;

  return 0;
}

