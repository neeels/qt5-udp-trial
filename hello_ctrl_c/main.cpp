/* hello_ctrl_c

A short trial in handling OS signals in Qt5.

This works on POSIX systems only (e.g. Linux).

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

#include <QtCore>
#include <QTextStream>

#include <signal.h>
#include <string.h>

#include "SomeTask.h"

QTextStream out(stdout);

SomeTask *gl_task = NULL;

void handler(int sig)
{
  out << "\n" << strsignal(sig) << " signal received." << endl;
  if (gl_task)
    gl_task->pleaseQuit = true;
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  SomeTask task;
  gl_task = &task;
  QObject::connect(&task, SIGNAL(finished()), &a, SLOT(quit()));

  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESETHAND;

  sigaction(SIGINT, &act, NULL);
  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGQUIT, &act, NULL);

  QTimer::singleShot(0, &task, SLOT(run()));

  return a.exec();
}
