#ifndef UDP_LISTENER_H_2015
#define UDP_LISTENER_H_2015

#include <QUdpSocket>
#include <QTextStream>

class UdpListener : public QObject
{
  Q_OBJECT

  public:
    
    /*! \param out  Print any log output to this stream.
        \param port  Port number to listen on (on "any" localhost IPs).
     */
    UdpListener(QTextStream *out, int port, QObject *parent=0);

    /*! Open a socket. Return false if binding to the socket failed.
        The socket is managed internally.
     */ 
    bool bind();

    /*! Close a previously opened socket. */
    void close();

  private slots:
    /*! Receive any datagrams available from the bound socket, and
        print their content on the out textstream passed to the constructor.
     */
    void receiveDatagram();

  private:
    QTextStream *out;
    int port;
    QUdpSocket *udpSocket;

};

#endif // UDP_LISTENER_H_2015
