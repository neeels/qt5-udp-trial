#include <string.h>
#include <qiostream>

#include <qosquit.h>

QOsQuit::QOsQuit(QCoreApplication &application) : QOsSignalReceiver(0)
{
  this->application = &application;
  handleOsSignal(SIGINT);
  handleOsSignal(SIGTERM);
  handleOsSignal(SIGQUIT);
}

void QOsQuit::receiveOsSignal(int signalNr)
{
  qout << "\nSignal received: '" << strsignal(signalNr) << "'." << endl;
  QTimer::singleShot(0, application, SLOT(quit()));
}

