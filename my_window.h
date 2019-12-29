#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QPainter>
#include <vector>
#include "player.h"
#include "rectangle.h"

#define pieceRadius 15
QT_BEGIN_NAMESPACE
namespace Ui { class MyWindow; }
QT_END_NAMESPACE

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    QTimer* timer;
    std::vector<Player> players;
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();
   QPainter painter;
    void DrawTable(QPainter& painter);
    void DrawPlayers(QPainter& painter);
    void UpdateLabels();
private slots:
    virtual void paintEvent(QPaintEvent *event);
    virtual void update();

private:
    Ui::MyWindow *ui;
};
#endif // MYWINDOW_H
