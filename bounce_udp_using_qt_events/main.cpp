/*
   Listen on port localhost port 1337 to receive UDP datagrams.
   Read the datagram up to the first comma, and if these bytes match one of few
   listed strings, repost the entire datagram to the corresponding IP address,
   as listed. The list is hardcoded.

   See also the ./test.sh script.
*/

#include <string.h>
#include <QCoreApplication>
#include <QtCore>
#include <qiostream.h>
#include <QOsQuit>
#include "BounceUdp.h"

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QOsQuit signalCatcher(a);

  int port = 1337;

  BounceUdp *bounceUdp = new BounceUdp(port, &a);
  if (! bounceUdp->bind())
    return 1;

  return a.exec();
}

