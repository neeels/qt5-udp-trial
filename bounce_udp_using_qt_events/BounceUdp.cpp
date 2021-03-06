/*
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

#include <QtGlobal>
#include <qiostream.h>
#include "BounceUdp.h"

BounceUdp::BounceUdp(int listenPort,
                     QObject *parent)
  : QObject(parent)
{
  this->listenPort = listenPort;
  this->listenSocket = NULL;
}

BounceUdp::~BounceUdp()
{
  close();
}

bool BounceUdp::bind() {
  listenSocket = new QUdpSocket(this);
  Q_CHECK_PTR(listenSocket);

  if (! listenSocket->bind(listenPort)) {
    qerr << "*** Cannot open port " << listenPort << endl;
    delete listenSocket;
    listenSocket = NULL;
    return false;
  }

  connect(listenSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));

  qout << "Listening on port " << listenPort << endl;
  return true;
}

void BounceUdp::receiveDatagram() {
  if (listenSocket == NULL) {
    qerr << "*** BounceUdp: not bound to a socket. Forgot to call bind()?" << endl;
    return;
  }

  while (listenSocket->hasPendingDatagrams()) {
    qout << endl;

    const int size = listenSocket->pendingDatagramSize();

    QByteArray datagram(size, 0);

    int got = listenSocket->readDatagram(datagram.data(), datagram.size());

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

    QMultiMap<QString, BounceUdpTarget>::iterator it = targets.find(redirectToken);
    if (it != targets.end() && it.key() == redirectToken) {
      do {
        sendUdpDatagram(it.value(), datagram);

        ++ it;
      } while (it != targets.end() && it.key() == redirectToken);
    }
    else {
      qout << "Unknown redirect token. Ignoring datagram." << endl;
    }
  }
}

void BounceUdp::sendUdpDatagram(const BounceUdpTarget &target, QByteArray &datagram)
{

  qout << "Sending to " << target.addr.toString() << ", port " << target.port << endl;

  int sent = sendSocket.writeDatagram(datagram, target.addr, target.port);

  qout << "Sent " << sent << " bytes." << endl;

  if (sent != datagram.size()) {
    qerr << "*** Mismatch: datagram size = " << datagram.size() << ", sent bytes = " << sent << endl;
  }
}


void BounceUdp::close() {
  if (listenSocket) {
    listenSocket->close();
    qout << "Stopped listening on port " << listenPort << "." << endl;
  }
}


void BounceUdp::addTarget(const char *id, const char *target_addr,
                          int target_port)
{
  BounceUdpTarget t;
  t.addr.setAddress(target_addr);
  t.port = target_port;
  targets.insert(id, t);
}
