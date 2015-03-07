#include <qiostream.h>
#include "UdpListener.h"

UdpListener::UdpListener(int port,
                         QObject *parent)
  : QObject(parent)
{
  this->port = port;
  this->udpSocket = NULL;
}

bool UdpListener::bind() {
  udpSocket = new QUdpSocket(this);
  Q_CHECK_PTR(udpSocket);

  if (! udpSocket->bind(port)) {
    qerr << "*** Cannot open port " << port << endl;
    delete udpSocket;
    udpSocket = NULL;
    return false;
  }

  qout << "Listening on port " << this->port << endl;

  connect(udpSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));
  return true;
}

void UdpListener::receiveDatagram() {
  if (udpSocket == NULL) {
    qerr << "*** UdpListener: not bound to a socket. Forgot to call bind()?" << endl;
    return;
  }

  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram(udpSocket->pendingDatagramSize(), 0);

    int got = udpSocket->readDatagram(datagram.data(), datagram.size());

    qout << "received " << got << " bytes:" << endl;
    qout << "[[[\n" << datagram << "\n]]]" << endl;
  }
}

void UdpListener::close() {
  udpSocket->close();
  qout << "Stopped listening on port" << port << "." << endl;
}


