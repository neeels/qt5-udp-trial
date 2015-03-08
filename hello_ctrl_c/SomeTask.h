#ifndef SOME_TASK_H_2015
#define SOME_TASK_H_2015

#include <QObject>
#include <QTextStream>
#include <QThread> // for usleep

class SomeTask : public QObject
{
  Q_OBJECT

  public:

    SomeTask(QObject *parent=0) : QObject(parent) {}

    ~SomeTask()
    {
      QTextStream out(stdout);
      out << "~SomeTask destructor invoked." << endl;
      thread()->usleep(5e5);
      out << "~SomeTask destructor done." << endl;
      
    }

    bool pleaseQuit;

  public slots:

    void run()
    {
      QTextStream out(stdout);
      pleaseQuit = false;
      while (! pleaseQuit) {
        out << "\n"
               "Still running...\n"
               "Please send a SIGINT, SIGTERM or SIGQUIT,\n"
               "e.g. hit Ctrl-C or Ctrl-\\." << endl;
        thread()->usleep(2e6);
      }
      out << "Loop exited." << endl;

      emit finished();
    }

  signals:
    void finished();

};


#endif // SOME_TASK_H_2015
