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
#ifndef SAY_HELLO_H_2015
#define SAY_HELLO_H_2015

#include <qiostream.h>

class SayHello : public QObject
{
    Q_OBJECT
  public:
    /*! \param out  Print any log output to this stream. */
    SayHello(QObject *parent = 0)
      : QObject(parent)
    { }

  public slots:

    /*! Print "Hello Event" and emit signal finished(). */
    void run()
    {
        qout << "Hello Event" << endl;  

        emit finished();
    }

  signals:
    void finished();
};

#endif // SAY_HELLO_H_2015
