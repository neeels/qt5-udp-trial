/*
Listen on port localhost port 1337 to receive UDP datagrams.
Read the datagram up to the first comma, and if these bytes match one of few
listed strings, repost the entire datagram to the corresponding IP address,
as listed. The list is hardcoded.

See also the ./test.sh script.

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

#include <string.h>
#include <QCoreApplication>
#include <QtCore>
#include <qiostream.h>
#include <QOsQuit>
#include "BounceUdp.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QOsQuit signalCatcher(a);

  int port = 1337;

  BounceUdp bounceUdp(port, &a);

  bounceUdp.addTarget("FOO", "127.0.0.1", 1339);
  bounceUdp.addTarget("FOO", "127.0.0.1", 1338);
  bounceUdp.addTarget("BAR", "::1", 1340);

  if (! bounceUdp.bind())
    return 1;

  return a.exec();
}

