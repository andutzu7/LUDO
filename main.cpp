#include "my_window.h"
#include "socket.h"
#include <QApplication>
void onUserCreate()
{

}
void onUserUpdate()
{

}
void Draw()
{

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow w;
    mySocket s;
    s.Connect();
    s.Read();
    w.show();
    a.exec();
    return 0;
}
