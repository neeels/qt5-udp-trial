#ifndef SAY_HELLO_H_2015
#define SAY_HELLO_H_2015

#include <QTextStream>

class SayHello : public QObject
{
    Q_OBJECT
  public:
    SayHello(QTextStream *out, QObject *parent = 0)
      : QObject(parent)
    {
      this->out = out;
    }

  private:
    QTextStream *out;

  public slots:
    void run()
    {
        (*out) << "Hello Event" << endl;  

        emit finished();
    }

  signals:
    void finished();
};

#endif // SAY_HELLO_H_2015
