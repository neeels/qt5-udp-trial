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
#ifndef Q_OS_SIGNAL_RECEIVER_H_2015
#define Q_OS_SIGNAL_RECEIVER_H_2015

#include <signal.h>
#include <QObject>

/*! Receive operating system signals like SIGINT.
 *
 * Since receiveOsSignal is called from a signal handler routine, this function
 * cannot reliably trigger Qt events to class instance slots. Instead, a flag
 * can be set and handled later. Incidentally, sending the QCoreApplication a
 * signal to the quit slot effectively exits the Qt event loop if no other
 * tasks are running.
 *
 * This works only for POSIX systems (like Linux), and only one
 * QOsSignalHandler can be used in a running program (see global_handler).
 *
 * Usage:
 *
 *     #include <QOsSignalHandler>
 * 
 *     class RecvImpl : public QOsSignalHandler
 *     {
 *       [...]
 *       bool done;
 *       void run() {
 *         while (! done)
 *           do_stuff();
 *       }
 *       void receiveOsSignal(int) {
 *         done = true;
 *       }
 *     }
 *   
 *     {
 *       RecvImpl impl;
 *       impl.handleOsSignal(SIGINT);
 *       impl.handleOsSignal(SIGQUIT);
 *       impl.handleOsSignal(SIGTERM);
 *     }
 */
class QOsSignalReceiver : public QObject
{
  Q_OBJECT

  public:

    QOsSignalReceiver(QObject *parent=0);
    ~QOsSignalReceiver();

    /*! Register the OS signal handler to call receiveOsSignal for the given
     * signal number.
     */
    void handleOsSignal(int signal);

    /*! When an OS signal is received, this function is called.
     */
    virtual void receiveOsSignal(int signal) = 0;

    /*! Stores the global QOsSignalReceiver derived instance to receive
     * callbacks from a signal handler routine.
     */
    static QOsSignalReceiver *global_handler;
};

#endif // Q_OS_SIGNAL_RECEIVER_H_2015
