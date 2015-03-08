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
