#ifndef Q_OS_QUIT_H_2015
#define Q_OS_QUIT_H_2015

#include <QtCore>
#include <QOsSignalReceiver>

class QOsQuit : public QOsSignalReceiver
{
  Q_OBJECT

  public:

    QOsQuit(QCoreApplication &application);

    virtual void receiveOsSignal(int);

  private:
    QCoreApplication *application;

};

#endif // Q_OS_QUIT_H_2015
