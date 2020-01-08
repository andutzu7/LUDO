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
    updateRate=new QTimer(this);
    updateRate->setInterval(5000);
    updateRate->start();
    connect(updateRate,SIGNAL(timeout()),this,SLOT(Read()));
    updateRate->setInterval(5000);
    updateRate->start();
    connect(updateRate,SIGNAL(timeout()),this,SLOT(writeData()));


}
bool mySocket::writeData()
{
    QByteArray q=QByteArray('m',10);
    if(socket->state() == QAbstractSocket::ConnectedState)
        {
        socket->write(q);
        qDebug()<<"WROTE SHIT";

        return socket->waitForBytesWritten();
    }
        else
            return false;

}
void mySocket::Read()
{
    socket->waitForBytesWritten(1000);
    socket->waitForReadyRead(1000);
    qDebug()<<"Reading"<<socket->bytesAvailable();
    qDebug()<<socket->readAll()<<endl;
    qDebug()<<socket->readAll()<<endl;
}
