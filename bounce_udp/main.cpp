/*
   Listen on port localhost port 1337 to receive UDP datagrams.
   Read the datagram up to the first comma, and if these bytes match one of few
   listed strings, repost the entire datagram to the corresponding IP address,
   as listed. The list is hardcoded.

*/

#include <QTextStream>
#include <QUdpSocket>
#include <QThread> // for usleep
//#include <Redirect>

QTextStream out(stdout);

void sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram)
{
  QUdpSocket udpSocket;

  out << "Sending to " << toAddress << ", port " << port << endl;

  QHostAddress toAddressObj(toAddress);

  int sent = udpSocket.writeDatagram(datagram, toAddressObj, port);

  out << "Sent " << sent << " bytes." << endl;
}

int main(void) {
  int port = 1337;

  QUdpSocket udpSocket;

  udpSocket.bind(port);

  out << "Listening on port " << port << endl;

  while (1){

    if (udpSocket.hasPendingDatagrams()) {
      const int size = udpSocket.pendingDatagramSize();

      QByteArray datagram(size, 0);

      int got = udpSocket.readDatagram(datagram.data(), datagram.size());

      out << "received " << got << " bytes:" << endl;
      out << "[[[\n" << datagram << "\n]]]" << endl;

      int tokenEnd = datagram.indexOf(',');

      if ((tokenEnd <= 0) || (tokenEnd >= datagram.size())) {
        out << "No redirect token available." << endl;
        continue;
      }

      QByteArray redirectTokenBytes(datagram.data(), tokenEnd);
      QString redirectToken(redirectTokenBytes);
      out << "Redirect token: '" << redirectToken << "'" << endl;

      if (redirectToken.compare("FOO") == 0) {
        sendUdpDatagram("127.0.0.1", 1338, datagram);
        sendUdpDatagram("127.0.0.1", 1339, datagram);
      }
      else
      if (redirectToken.compare("BAR") == 0) {
        sendUdpDatagram("::1", 1340, datagram);
      }

    }
    else {
      // don't eat CPU
      udpSocket.thread()->usleep(1e3); // 1e6 == 1 second
      // Maybe the Qt event handling would make sense instead of this.
    }
  }

  // todo: catch ctrl-C and close socket gracefully

  udpSocket.close();
  out << "Stopped listening." << endl;

  return 0;
}

