#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QPainter>
#include <vector>
#include "rectangle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MyWindow; }
QT_END_NAMESPACE

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer* timer;
    std::vector<QRect> rectangles;
    std::vector<QLine> lines;
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();
    virtual void paintEvent(QPaintEvent *event);
    virtual void update();
    void Draw();
private:
    Ui::MyWindow *ui;
};
#endif // MYWINDOW_H
