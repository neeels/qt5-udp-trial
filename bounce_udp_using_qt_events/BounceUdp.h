/*
This file is part of qt5-udp-trial,
a short trial in Qt5 basics and networking API (no GUI)
Copyright (C) 2015  Neels Hofmeyr
http://hofmeyr.de
http://github.com/neeels/qt5-udp-trial

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef BOUNCE_UDP_H_2015
#define BOUNCE_UDP_H_2015

#include <QUdpSocket>

class BounceUdp : public QObject
{
  Q_OBJECT

  public:
    
    /*! \param listenPort  Port number to listen on (on "any" localhost IPs).
     */
    BounceUdp(int listenPort, QObject *parent=0);

    ~BounceUdp();

    /*! Open a socket. Return false if binding to the socket failed.
        The socket is managed internally.
     */ 
    bool bind();

    /*! Close a previously opened socket. */
    void close();

  private slots:
    /*! Receive any datagrams available from the bound socket, and
        resend them according to the hardcoded internal rules.
        bind() must have been called successfully.
     */
    void receiveDatagram();

  private:
    int listenPort;
    QUdpSocket *listenSocket;
    QUdpSocket sendSocket;

    void sendUdpDatagram(const char *toAddress, int port, QByteArray &datagram);

};

#endif // BOUNCE_UDP_H_2015
