/*
   Listen on port localhost port 1337 to receive UDP datagrams.
   Read the datagram up to the first comma, and if these bytes match one of few
   listed strings, repost the entire datagram to the corresponding IP address,
   as listed. The list is hardcoded.

   To test, run the ./test.sh script, or run manually:

     ./bounce_udp

     # in another terminal:
     netcat -l -u -p 1338

     # in yet another terminal:
     netcat -l -u -p 1339

     # and in yet another terminal:
     nc6 -l -u -p 1340

     # and in the final terminal, send various datagrams:
     netcat -u localhost 1337
     # and then type:
     FOO,1,2,3
     BAR,asdf,asd,fasd,f

     # in first terminal, this should print something like:
     > ./bounce_udp 
     Listening on port 1337

     received 10 bytes:
     [[[
     FOO,1,2,3

     ]]]
     Redirect token: 'FOO'
     Sending to 127.0.0.1, port 1338
     Sent 10 bytes.
     Sending to 127.0.0.1, port 1339
     Sent 10 bytes.

     received 20 bytes:
     [[[
     BAR,asdf,asd,fasd,f

     ]]]
     Redirect token: 'BAR'
     Sending to ::1, port 1340
     Sent 20 bytes.

     received 9 bytes:
     [[[
     BAZ,lala

     ]]]
     Redirect token: 'BAZ'
     Unknown redirect token. Ignoring datagram.

     received 20 bytes:
     [[[
     the quick brown fox

     ]]]
     No redirect token in this datagram. Ignoring.

*/

#include <QTextStream>
#include <QUdpSocket>
#include <QThread> // for usleep

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

  if (! udpSocket.bind(port)) {
    out << "Failed to bind to port " << port << endl;
    return 1;
  }

  out << "Listening on port " << port << endl;

  while (1){

    if (udpSocket.hasPendingDatagrams()) {
      out << endl;

      const int size = udpSocket.pendingDatagramSize();

      QByteArray datagram(size, 0);

      int got = udpSocket.readDatagram(datagram.data(), datagram.size());

      out << "received " << got << " bytes:" << endl;
      out << "[[[\n" << datagram << "\n]]]" << endl;

      int tokenEnd = datagram.indexOf(',');

      if ((tokenEnd <= 0) || (tokenEnd >= datagram.size())) {
        out << "No redirect token in this datagram. Ignoring." << endl;
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
      else {
        out << "Unknown redirect token. Ignoring datagram." << endl;
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

