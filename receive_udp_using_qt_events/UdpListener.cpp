#include "UdpListener.h"

UdpListener::UdpListener(QTextStream *out, int port,
                         QObject *parent)
  : QObject(parent)
{
  this->out = out;
  this->port = port;
  this->udpSocket = NULL;
}

bool UdpListener::bind() {
  udpSocket = new QUdpSocket(this);
  Q_CHECK_PTR(udpSocket);

  if (! udpSocket->bind(port)) {
    (*out) << "Cannot open port " << port << endl;
    delete udpSocket;
    udpSocket = NULL;
    return false;
  }

  (*out) << "Listening on port " << this->port << endl;

  connect(udpSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));
  return true;
}

void UdpListener::receiveDatagram() {
  if (udpSocket == NULL) {
    (*out) << "UdpListener: not bound to a socket. Forgot to call bind()?" << endl;
    return;
  }

  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram(udpSocket->pendingDatagramSize(), 0);

    int got = udpSocket->readDatagram(datagram.data(), datagram.size());

    (*out) << "received " << got << " bytes:" << endl;
    (*out) << "[[[\n" << datagram << "\n]]]" << endl;
  }
}

void UdpListener::close() {
  udpSocket->close();
  (*out) << "Stopped listening on port" << port << "." << endl;
}


