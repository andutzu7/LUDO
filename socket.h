#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
class mySocket : public QObject
{
  Q_OBJECT
public:
    explicit mySocket(QObject *parent = nullptr);
    void Connect();
signals:
public slots:
private:
    QTcpSocket* socket;
};

#endif // SOCKET_H
