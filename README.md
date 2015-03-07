# qt5-udp-trial
A quick trial in Qt5, from hello world to bouncing UDP datagrams. None of
these programs use a GUI. Some use a plain main loop, others use Qt's
QCoreApplication event loop.

To learn what each program is about, read the top comment in each subdir's
`main.cpp`. The `qiostream` folder is different, as it provides a tiny library
to be used by the other programs, see `qiostream/qiostream.h`.

Usually, you would just run `make` in the root folder, or one of the subdirs.
But at first, there are only qmake \*.pro files available.
To generate Makefiles in all subdirs, simply run

    qmake

in the root folder. As soon as the first Makefiles exist, simply running

    make

is sufficient to update and rebuild all targets, including the Makefiles
themselves.

Dependencies:

- make
- g++
- qmake
- Qt5

On debian testing (2015-03-04), this was sufficient:

    apt-get install make g++ qt5-default

