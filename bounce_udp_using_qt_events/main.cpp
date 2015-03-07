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

#include <QCoreApplication>
#include <qiostream.h>
#include "BounceUdp.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  int port = 1337;

  BounceUdp *bounceUdp = new BounceUdp(port, &a);
  if (! bounceUdp->bind())
    return 1;

  return a.exec();
}

