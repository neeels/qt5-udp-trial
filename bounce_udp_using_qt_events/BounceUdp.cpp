#include <QtGlobal>
#include <qiostream>
#include "BounceUdp.h"

BounceUdp::BounceUdp(int listenPort,
                     QObject *parent)
  : QObject(parent)
{
  this->listenPort = listenPort;
  this->listenSocket = NULL;
}

BounceUdp::~BounceUdp()
{
  close();
}

bool BounceUdp::bind() {
  listenSocket = new QUdpSocket(this);
  Q_CHECK_PTR(listenSocket);

  if (! listenSocket->bind(listenPort)) {
    qerr << "*** Cannot open port " << listenPort << endl;
    delete listenSocket;
    listenSocket = NULL;
    return false;
  }

  connect(listenSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));

  qout << "Listening on port " << listenPort << endl;
  return true;
}

void BounceUdp::receiveDatagram() {
  if (listenSocket == NULL) {
    qerr << "*** BounceUdp: not bound to a socket. Forgot to call bind()?" << endl;
    return;
  }

  while (listenSocket->hasPendingDatagrams()) {
    qout << endl;

    const int size = listenSocket->pendingDatagramSize();

    QByteArray datagram(size, 0);

    int got = listenSocket->readDatagram(datagram.data(), datagram.size());

    qout << "received " << got << " bytes:" << endl;
    qout << "[[[\n" << datagram << "\n]]]" << endl;

    int tokenEnd = datagram.indexOf(',');

    if ((tokenEnd <= 0) || (tokenEnd >= datagram.size())) {
      qout << "No redirect token in this datagram. Ignoring." << endl;
      continue;
    }

    QByteArray redirectTokenBytes(datagram.data(), tokenEnd);
    QString redirectToken(redirectTokenBytes);
    qout << "Redirect token: '" << redirectToken << "'" << endl;

    if (redirectToken.compare("FOO") == 0) {
      sendUdpDatagram("127.0.0.1", 1338, datagram);
      sendUdpDatagram("127.0.0.1", 1339, datagram);
    }
    else
    if (redirectToken.compare("BAR") == 0) {
      sendUdpDatagram("::1", 1340, datagram);
    }
    else {
      qout << "Unknown redirect token. Ignoring datagram." << endl;
    }
  }
}

void BounceUdp::sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram)
{

  qout << "Sending to " << toAddress << ", port " << port << endl;

  QHostAddress toAddressObj(toAddress);

  int sent = sendSocket.writeDatagram(datagram, toAddressObj, port);

  qout << "Sent " << sent << " bytes." << endl;

  if (sent != datagram.size()) {
    qerr << "*** Mismatch: datagram size = " << datagram.size() << ", sent bytes = " << sent << endl;
  }
}


void BounceUdp::close() {
  if (listenSocket) {
    listenSocket->close();
    qout << "Stopped listening on port" << listenPort << "." << endl;
  }
}


