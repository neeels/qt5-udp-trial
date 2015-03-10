/* hello_event.cpp

A short trial in sending and receiving events in Qt5.

A SayHello instance receives a signal to its 'run' slot (the recevier of a
signal is called a slot). It then prints "Hello Event" and emits its
'finished' signal. The 'finished' signal is connected to the
QCoreApplication's 'quit' slot and closes the application.

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

#include <QtCore>
#include "SayHello.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SayHello task;

    // This will cause the application to exit when
    // the task signals finished.    
    QObject::connect(&task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, &task, SLOT(run()));

    return a.exec();
}
