#include "socket.h"
#include <qhostaddress.h>
mySocket::mySocket(QObject *parent) : QObject(parent)
{

}

void mySocket::Connect()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"), 2024);
    if(socket->waitForConnected(3000))
    {

        qDebug()<<"Connected";

        socket->waitForBytesWritten(1000);
        socket->write("3",1);
        socket->waitForReadyRead(1000);
        qDebug()<<"Reading"<<socket->bytesAvailable();
        qDebug()<<socket->readAll();
        socket->disconnect();
    }
    else
    {
        qDebug()<<"Aiurea";
    }

}
