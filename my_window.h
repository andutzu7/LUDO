#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QPainter>
#include <vector>
#include "player.h"
#include "rectangle.h"
#include <QPushButton>
#include "socket.h"
#include <QMouseEvent>
#define pieceRadius 15
QT_BEGIN_NAMESPACE
namespace Ui { class MyWindow; }
QT_END_NAMESPACE

class MyWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool gameHasStarted=false;
    mySocket s;
    bool requested=false;
    int j=0;//???
    size_t playersNumber=1;
    QTimer* timer;
    std::vector<Player> players;
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();
    QPainter painter;
    void  Game();
    void InitPlayers(int playersNumber);
    void UpdateVelocity(int nrOfSquaresTraveled);
    void DrawTable(QPainter& painter);
    void DrawPlayers(QPainter& painter);
    void  mousePressEvent(QMouseEvent* event);
    void UpdateLabels();
    int currentPlayer=1;
    bool gameOver=false;
    bool diceWRolled=false;
private slots:
    virtual void paintEvent(QPaintEvent *event);
    virtual void update();
    virtual void diceButton_onClicked();
private:
    Ui::MyWindow *ui;
};
#endif // MYWINDOW_H
