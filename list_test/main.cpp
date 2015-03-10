/*
A simplistic benchmark in traversing QMultiMap.

The reason is that the default way of iterating QMultiMap looks very
inefficient. The way that more efficient iteration is mentioned is with the
words "If you prefer the STL-style iterators", not mentioning efficiency.
http://doc.qt.io/qt-5/qmultimap.html (2015-03-10)

This program is a quick hack to show that iterators are in fact more efficient
than using the assignable trait of data types, by magnitudes.

See below an "#if 1". Like this, the less efficient way is used to traverse
the QMultiMap items. Compile and run this program, and measure its
performance, for example using 'time':

    > make
    > time ./list_test
    990000000

    real  0m2.696s
    user  0m2.688s
    sys 0m0.004s

Now change it to "#if 0", compile and measure again:

    > make
    > time ./list_test 
    990000000

    real  0m0.267s
    user  0m0.264s
    sys 0m0.000s

See that proper STL style iterating is about 10 times faster.

The reason:

    QList<Stuff> stuffs = m.values(i);

Above line actually copies the entire multimap entry including every 'Stuff'
listitem. This may also confuse object identities, since the items in 'stuffs'
are copies of the original objects.


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
#include <QFile>
#include <QtCore>
#include <QMultiMap>
#include <QHostAddress>
#include <qiostream.h>

#include <unistd.h>

typedef struct {
  QHostAddress addr;
  int port;
} Stuff;

int main(void) {

  QMultiMap<int,Stuff> m;

#define N 100

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 100; j++) {
      Stuff s;
      QString addr;
      addr += (999999 - (1000 * i + j));
      s.addr.setAddress(addr);
      s.port = i + j;
      m.insert(i, s);
    }
  }


  int y = 0;
  for (int r = 0; r < 1000; r++) {
    for (int i = 0; i < N; i++) {

#if 1
      QList<Stuff> stuffs = m.values(i);
      for (int j = 0; j < stuffs.size(); j ++) {
        y += stuffs.at(j).port;
      }
#else

      QMultiMap<int, Stuff>::iterator it = m.find(i);
      while (it != m.end() && it.key() == i) {
        y += it.value().port;
        ++ it;
      }
#endif

    }
  }

  qout << y << endl;

  return 0;
}
