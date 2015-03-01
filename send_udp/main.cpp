/*
   Send a UDP datagram "Hello UDP" to localhost port 1337, using IPv4.
   As UDP is unreliable, there will be no indication whether the datagram has
   been received on the other end or not.

   To test:

     # listen on UDP port 1337
     nc -l -u 1337

     # in another terminal:
     ./send_udp

     # should print in first terminal:
     > ./send_udp
     Hello UDP

   To stop testing, hit Ctrl-C in the first terminal.
   send_udp will exit immediately after posting the UDP datagram.

*/

#include <QTextStream>
#include <QUdpSocket>
#include <QHostAddress>

QTextStream out(stdout);

int main(void) {
  int port = 1337;

  QUdpSocket udpSocket;

  out << "Sending to localhost, port " << port << endl;

  QByteArray helloUdp("Hello UDP\n");
  int sent = udpSocket.writeDatagram(helloUdp, QHostAddress::LocalHost, port);

  out << "Sent " << sent << " bytes." << endl;

  return 0;
}

