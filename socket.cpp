#include "socket.h"
#include <qhostaddress.h>
mySocket::mySocket(QObject *parent) : QObject(parent)
{

}

void mySocket::Connect()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"), PORT);
    if(socket->waitForConnected(3000))
    {

        qDebug()<<"Connected";
    }
    else
    {
        qDebug()<<"Aiurea";
    }

}
void mySocket::writeData(const char* data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
        {
        socket->write(data);
        }

}
int mySocket::Read()
{
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(1000);
    return socket->readAll().toInt();
}
