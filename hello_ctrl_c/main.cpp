/* hello_ctrl_c

   A short trial in handling OS signals in Qt5.

   This works on POSIX systems only (e.g. Linux).

*/

#include <QtCore>
#include <QTextStream>

#include <signal.h>
#include <string.h>

#include "SomeTask.h"

QTextStream out(stdout);

SomeTask *gl_task = NULL;

void handler(int sig)
{
  out << "\n" << strsignal(sig) << " signal received." << endl;
  if (gl_task)
    gl_task->pleaseQuit = true;
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  SomeTask task;
  gl_task = &task;
  QObject::connect(&task, SIGNAL(finished()), &a, SLOT(quit()));

  struct sigaction act;
  act.sa_handler = handler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESETHAND;

  sigaction(SIGINT, &act, NULL);
  sigaction(SIGTERM, &act, NULL);
  sigaction(SIGQUIT, &act, NULL);

  QTimer::singleShot(0, &task, SLOT(run()));

  return a.exec();
}
