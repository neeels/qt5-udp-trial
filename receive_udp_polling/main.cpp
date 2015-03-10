/*
Listen on port localhost port 1337 to receive UDP datagrams.
Print received data to stdout.

To test:

    ./receive_udp

    # in another terminal:
    netcat -u localhost 1337
    then type things

    # should print in first terminal:
    > ./receive_udp
    Listening on port 1337
    received 17 bytes:
    [[[
    then type things

    ]]]

To stop testing, hit Ctrl-C in each terminal.

This file is part of qt5-udp-trial,
a short trial in Qt5 basics and networking API (no GUI)
Copyright (C) 2015  Neels Hofmeyr
http://hofmeyr.de
http://github.com/neeels/qt5-udp-trial

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <QUdpSocket>
#include <QThread> // for usleep
#include <qiostream.h>

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
      const int size = udpSocket.pendingDatagramSize();

      QByteArray datagram(size, 0);

      int got = udpSocket.readDatagram(datagram.data(), datagram.size());

      qout << "received " << got << " bytes:" << endl;
      qout << "[[[\n" << datagram << "\n]]]" << endl;

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

