/* hello_event.cpp

   A short trial in sending and receiving events in Qt5.

   A SayHello instance receives a signal to its 'run' slot (the recevier of a
   signal is called a slot). It then prints "Hello Event" and emits its
   'finished' signal. The 'finished' signal is connected to the
   QCoreApplication's 'quit' slot and closes the application.

*/

#include <QtCore>
#include <QTextStream>
#include "SayHello.h"

QTextStream out(stdout);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // SayHello parented to the application so that it
    // will be deleted by the application.
    SayHello *task = new SayHello(&out, &a);

    // This will cause the application to exit when
    // the task signals finished.    
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));

    return a.exec();
}
