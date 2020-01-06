#ifndef SOCKET_H
#define SOCKET_H
#define PORT 2024
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>
class mySocket : public QObject
{
  Q_OBJECT
public:
    QTimer* updateRate;
    explicit mySocket(QObject *parent = nullptr);
    void Connect();

    char* c;
signals:
public slots:
 virtual void Read();
private:
    QTcpSocket* socket;
};

#endif // SOCKET_H
