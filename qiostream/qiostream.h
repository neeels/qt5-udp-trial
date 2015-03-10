/* qiostream.h

Provide global console output qout and qerr, like cout and cerr,
to conveniently print Qt object instances.

For example, cout cannot handle QString or QByteArray, but qout can.

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

#ifndef QIOSTREAM_H_2015
#define QIOSTREAM_H_2015

#include <QTextStream>

extern QTextStream qout;
extern QTextStream qerr;

#endif // QIOSTREAM_H_2015
