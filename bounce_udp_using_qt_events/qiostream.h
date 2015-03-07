/* qiostream.h

   Provide global console output qout and qerr, like cout and cerr,
   to conveniently print Qt object instances.

   For example, cout cannot handle QString or QByteArray, but qout can.

*/

#ifndef QIOSTREAM_H_2015
#define QIOSTREAM_H_2015

#include <QTextStream>

extern QTextStream qout;
extern QTextStream qerr;

#endif // QIOSTREAM_H_2015
