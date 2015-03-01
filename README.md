# qt5-udp-trial
A quick trial in Qt5, from hello world to bouncing UDP datagrams.  None of
these programs use a GUI. Some use a plain main loop, others use Qt's
QApplicationCore event loop.

To learn what each program is about, read the top comment in each subdir's
'main.cpp'.

Usually, you would just run 'make' in one of the subdirs.
But at first, there are only qmake \*.pro files available.
To get a first Makefile, go to a subdir and run

    qmake -o Makefile *.pro

As soon as the first Makefile exists, simply running

    make

is sufficient to update and rebuild all targets, including the Makefile itself.
For example:

    cd hello_world
    qmake -o Makefile *.pro
    make
    ./hello_world

Dependencies:

- qmake
- Qt5
- g++

On debian, I did
  
    apt-get install qt5-default qt5-qmake g++

(Some dependencies may still be missing in this list, but it seems to me that
this is the minimal requirement.)

