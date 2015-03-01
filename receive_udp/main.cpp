/*
   Listen on port localhost port 1337 to receive UDP datagrams.
   Print received data to stdout.

   To test:

     ./receive_udp

     # in another terminal:
     netcat -u localhost 1337
     then type things

     # should print in first terminal:
     > ./receive_udp
     Listening on port 1337
     received 17 bytes:
     [[[
     then type things

     ]]]

   To stop testing, hit Ctrl-C in each terminal.

*/

#include <QTextStream>
#include <QUdpSocket>
#include <QThread> // for usleep

QTextStream out(stdout);

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
      const int size = udpSocket.pendingDatagramSize();

      QByteArray datagram(size, 0);

      int got = udpSocket.readDatagram(datagram.data(), datagram.size());

      out << "received " << got << " bytes:" << endl;
      out << "[[[\n" << datagram << "\n]]]" << endl;

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

