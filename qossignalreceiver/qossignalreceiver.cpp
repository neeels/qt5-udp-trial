#include <assert.h>
#include "qossignalreceiver.h"

QOsSignalReceiver *QOsSignalReceiver::global_handler = NULL;

QOsSignalReceiver::QOsSignalReceiver(QObject *parent) : QObject(parent)
{
  assert(QOsSignalReceiver::global_handler == NULL);

  QOsSignalReceiver::global_handler = this;
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

