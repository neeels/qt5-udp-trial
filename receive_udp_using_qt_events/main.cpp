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

#include <QCoreApplication>
#include <QTextStream>
#include "UdpListener.h"


int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QTextStream out(stdout);
  UdpListener udpListener(&out, 1337);
  if (! udpListener.bind())
    return 1;

  return a.exec();
}

