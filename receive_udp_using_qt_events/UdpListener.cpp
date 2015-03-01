#include "UdpListener.h"

UdpListener::UdpListener(QTextStream *out, int port,
                         QObject *parent)
  : QObject(parent)
{
  this->out = out;
  this->port = port;

  udpSocket = new QUdpSocket(this);
  udpSocket->bind(this->port);

  (*this->out) << "Listening on port " << this->port << endl;

  connect(udpSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));
}

void UdpListener::receiveDatagram() {
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


