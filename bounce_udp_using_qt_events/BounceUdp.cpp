#include <QtGlobal>
#include "BounceUdp.h"

BounceUdp::BounceUdp(QTextStream *out, int listenPort,
                     QObject *parent)
  : QObject(parent)
{
  this->out = out;
  Q_CHECK_PTR(this->out);
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
    (*out) << "Cannot open port " << listenPort << endl;
    delete listenSocket;
    listenSocket = NULL;
    return false;
  }

  connect(listenSocket, SIGNAL(readyRead()),
          this, SLOT(receiveDatagram()));

  (*out) << "Listening on port " << listenPort << endl;
  return true;
}

void BounceUdp::receiveDatagram() {
  if (listenSocket == NULL) {
    (*out) << "BounceUdp: not bound to a socket. Forgot to call bind()?" << endl;
    return;
  }

  while (listenSocket->hasPendingDatagrams()) {
    (*out) << endl;

    const int size = listenSocket->pendingDatagramSize();

    QByteArray datagram(size, 0);

    int got = listenSocket->readDatagram(datagram.data(), datagram.size());

    (*out) << "received " << got << " bytes:" << endl;
    (*out) << "[[[\n" << datagram << "\n]]]" << endl;

    int tokenEnd = datagram.indexOf(',');

    if ((tokenEnd <= 0) || (tokenEnd >= datagram.size())) {
      (*out) << "No redirect token in this datagram. Ignoring." << endl;
      continue;
    }

    QByteArray redirectTokenBytes(datagram.data(), tokenEnd);
    QString redirectToken(redirectTokenBytes);
    (*out) << "Redirect token: '" << redirectToken << "'" << endl;

    if (redirectToken.compare("FOO") == 0) {
      sendUdpDatagram("127.0.0.1", 1338, datagram);
      sendUdpDatagram("127.0.0.1", 1339, datagram);
    }
    else
    if (redirectToken.compare("BAR") == 0) {
      sendUdpDatagram("::1", 1340, datagram);
    }
    else {
      (*out) << "Unknown redirect token. Ignoring datagram." << endl;
    }
  }
}

void BounceUdp::sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram)
{

  (*out) << "Sending to " << toAddress << ", port " << port << endl;

  QHostAddress toAddressObj(toAddress);

  int sent = sendSocket.writeDatagram(datagram, toAddressObj, port);

  (*out) << "Sent " << sent << " bytes." << endl;
}


void BounceUdp::close() {
  if (listenSocket) {
    listenSocket->close();
    if (out) {
      (*out) << "Stopped listening on port" << listenPort << "." << endl;
    }
  }
}


