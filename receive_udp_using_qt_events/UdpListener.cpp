/*
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
*/
#include <qiostream.h>
#include "UdpListener.h"

UdpListener::UdpListener(int port,
                         QObject *parent)
  : QObject(parent)
{
  this->port = port;
  this->udpSocket = NULL;
}

bool UdpListener::bind() {
  udpSocket = new QUdpSocket(this);
  Q_CHECK_PTR(udpSocket);

  if (! udpSocket->bind(port)) {
    qerr << "*** Cannot open port " << port << endl;
    delete udpSocket;
    udpSocket = NULL;
    return false;
  }

  qout << "Listening on port " << this->port << endl;

  connect(udpSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));
  return true;
}

void UdpListener::receiveDatagram() {
  if (udpSocket == NULL) {
    qerr << "*** UdpListener: not bound to a socket. Forgot to call bind()?" << endl;
    return;
  }

  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram(udpSocket->pendingDatagramSize(), 0);

    int got = udpSocket->readDatagram(datagram.data(), datagram.size());

    qout << "received " << got << " bytes:" << endl;
    qout << "[[[\n" << datagram << "\n]]]" << endl;
  }
}

void UdpListener::close() {
  udpSocket->close();
  qout << "Stopped listening on port" << port << "." << endl;
}


