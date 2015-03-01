#ifndef BOUNCE_UDP_H_2015
#define BOUNCE_UDP_H_2015

#include <QUdpSocket>
#include <QTextStream>

class BounceUdp : public QObject
{
  Q_OBJECT

  public:
    
    BounceUdp(QTextStream *out, int listenPort, QObject *parent=0);

    bool bind();
    void close();

  private slots:
    void receiveDatagram();

  private:
    QTextStream *out;
    int listenPort;
    QUdpSocket *listenSocket;
    QUdpSocket sendSocket;

    void sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram);

};

#endif // BOUNCE_UDP_H_2015
