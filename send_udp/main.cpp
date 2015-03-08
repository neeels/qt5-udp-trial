/*
   Send a UDP datagram "Hello UDP" to localhost port 1337, using IPv4.
   As UDP is unreliable by nature, there will be no indication whether the
   datagram has been received on the other end or not.

   To test:

     # listen on UDP port 1337
     nc -l -u -p 1337

     # in another terminal:
     ./send_udp

     # should print in first terminal:
     > ./send_udp
     Hello UDP

   To stop testing, hit Ctrl-C in the first terminal.
   send_udp will exit immediately after posting the UDP datagram.

   Due to the nature of netcat, only one datagram will be received by the nc
   command.

*/

#include <QUdpSocket>
#include <QHostAddress>
#include <qiostream.h>

int main(void) {
  int port = 1337;

  QUdpSocket udpSocket;

  qout << "Sending to localhost, port " << port << endl;

  QByteArray helloUdp("Hello UDP\n");
  int sent = udpSocket.writeDatagram(helloUdp, QHostAddress::LocalHost, port);

  qout << "Sent " << sent << " bytes." << endl;

  if (sent != helloUdp.size()) {
    qerr << "*** Mismatch: datagram size = " << helloUdp.size() << ", sent bytes = " << sent << endl;
  }

  return 0;
}

