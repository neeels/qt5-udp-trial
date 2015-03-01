#ifndef UDP_LISTENER_H_2015
#define UDP_LISTENER_H_2015

#include <QUdpSocket>
#include <QTextStream>

class UdpListener : public QObject
{
  Q_OBJECT

  public:
    
    UdpListener(QTextStream *out, int port, QObject *parent=0);

    void close();

  private slots:
    void receiveDatagram();

  private:
    QTextStream *out;
    int port;
    QUdpSocket *udpSocket;

};

#endif // UDP_LISTENER_H_2015
