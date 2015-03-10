/*
Send a UDP datagram "Hello UDP" to localhost port 1337, using IPv4.
As UDP is unreliable by nature, there will be no indication whether the
datagram has been received on the other end or not.

To test:

    # listen on UDP port 1337
    nc -l -u -p 1337

    # in another terminal:
    ./send_udp

    # should print in first terminal:
    > ./send_udp
    Hello UDP

To stop testing, hit Ctrl-C in the first terminal.
send_udp will exit immediately after posting the UDP datagram.

Due to the nature of netcat, only one datagram will be received by the nc
command.

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
#include <QHostAddress>
#include <qiostream.h>

int main(void) {
  int port = 1337;

  QUdpSocket udpSocket;

  qout << "Sending to localhost, port " << port << endl;

  QByteArray helloUdp("Hello UDP\n");
  int sent = udpSocket.writeDatagram(helloUdp, QHostAddress::LocalHost, port);

  qout << "Sent " << sent << " bytes." << endl;

  if (sent != helloUdp.size()) {
    qerr << "*** Mismatch: datagram size = " << helloUdp.size() << ", sent bytes = " << sent << endl;
  }

  return 0;
}

