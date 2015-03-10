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
#include <assert.h>
#include "qossignalreceiver.h"

QOsSignalReceiver *QOsSignalReceiver::global_handler = NULL;

QOsSignalReceiver::QOsSignalReceiver(QObject *parent) : QObject(parent)
{
  assert(QOsSignalReceiver::global_handler == NULL);

  QOsSignalReceiver::global_handler = this;
}

QOsSignalReceiver::~QOsSignalReceiver()
{
  if (QOsSignalReceiver::global_handler == this)
    QOsSignalReceiver::global_handler = NULL;
}

void handler(int sig)
{
  if (QOsSignalReceiver::global_handler)
    QOsSignalReceiver::global_handler->receiveOsSignal(sig);
}

void QOsSignalReceiver::handleOsSignal(int signal)
{
  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESETHAND;

  sigaction(signal, &act, NULL);
}

