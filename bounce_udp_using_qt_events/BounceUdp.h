#ifndef BOUNCE_UDP_H_2015
#define BOUNCE_UDP_H_2015

#include <QUdpSocket>
#include <QTextStream>

class BounceUdp : public QObject
{
  Q_OBJECT

  public:
    
    /*! \param out  Print any log output to this stream.
        \param listenPort  Port number to listen on (on "any" localhost IPs).
     */
    BounceUdp(QTextStream *out, int listenPort, QObject *parent=0);

    ~BounceUdp();

    /*! Open a socket. Return false if binding to the socket failed.
        The socket is managed internally.
     */ 
    bool bind();

    /*! Close a previously opened socket. */
    void close();

  private slots:
    /*! Receive any datagrams available from the bound socket, and
        resend them according to the hardcoded internal rules.
        bind() must have been called successfully.
     */
    void receiveDatagram();

  private:
    QTextStream *out;
    int listenPort;
    QUdpSocket *listenSocket;
    QUdpSocket sendSocket;

    void sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram);

};

#endif // BOUNCE_UDP_H_2015
