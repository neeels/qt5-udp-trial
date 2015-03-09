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
#ifndef SOME_TASK_H_2015
#define SOME_TASK_H_2015

#include <QObject>
#include <QTextStream>
#include <QThread> // for usleep

class SomeTask : public QObject
{
  Q_OBJECT

  public:

    SomeTask(QObject *parent=0) : QObject(parent) {}

    ~SomeTask()
    {
      QTextStream out(stdout);
      out << "~SomeTask destructor invoked." << endl;
      thread()->usleep(5e5);
      out << "~SomeTask destructor done." << endl;
      
    }

    bool pleaseQuit;

  public slots:

    void run()
    {
      QTextStream out(stdout);
      pleaseQuit = false;
      while (! pleaseQuit) {
        out << "\n"
               "Still running...\n"
               "Please send a SIGINT, SIGTERM or SIGQUIT,\n"
               "e.g. hit Ctrl-C or Ctrl-\\." << endl;
        thread()->usleep(2e6);
      }
      out << "Loop exited." << endl;

      emit finished();
    }

  signals:
    void finished();

};


#endif // SOME_TASK_H_2015
