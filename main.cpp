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
    w.show();
    a.exec();
    return 0;
}
