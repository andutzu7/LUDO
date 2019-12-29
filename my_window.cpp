#include "my_window.h"
#include "ui_mywindow.h"
#include <QDebug>
#include <string>
MyWindow::MyWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    QPainter painter(this);


    const int screenWidth=800;
    const int screenHeight=600;
    const int squareDelta=50;
for (size_t i=0;i<screenWidth;i+=squareDelta)
{
    for(size_t j=0;j<screenHeight;j+=squareDelta)
    {
        QRect r(i,j,i+squareDelta,j+squareDelta);
    }
}

for(size_t i=0;i<4;i++)//initializam toti playerii
{
    //urmeaza o portiune de cod rusinoasa
    if(i==0)
    {
        std::vector<Piece> pl;
        Piece p(Vec2(51,61),Qt::red);
        pl.push_back(p);
        Piece p2(Vec2(121,61),Qt::red);
        pl.push_back(p2);
        Piece p3(Vec2(51,151),Qt::red);
        pl.push_back(p3);
        Piece p4(Vec2(121,151),Qt::red);
        pl.push_back(p4);

        players.emplace_back(pl,i+1);

   }
   if(i==1) //albastu
   {
       std::vector<Piece> pl;
       Piece p(Vec2(340,61),Qt::blue);
       pl.push_back(p);
       Piece p2(Vec2(410,61),Qt::blue);
       pl.push_back(p2);
       Piece p3(Vec2(340,151),Qt::blue);
       pl.push_back(p3);
       Piece p4(Vec2(410,151),Qt::blue);
       pl.push_back(p4);

       players.emplace_back(pl,i+1);

   }
    if(i==2) //green
   {


        std::vector<Piece> pl;
        Piece p(Vec2(51,330),Qt::green);
        pl.push_back(p);
        Piece p2(Vec2(121,330),Qt::green);
        pl.push_back(p2);
        Piece p3(Vec2(51,420),Qt::green);
        pl.push_back(p3);
        Piece p4(Vec2(121,420),Qt::green);
        pl.push_back(p4);

        players.emplace_back(pl,i+1);
   }
   if(i==3) //yellow
   {

       std::vector<Piece> pl;
       Piece p(Vec2(340,330),Qt::yellow);
       pl.push_back(p);
       Piece p2(Vec2(410,330),Qt::yellow);
       pl.push_back(p2);
       Piece p3(Vec2(340,420),Qt::yellow);
       pl.push_back(p3);
       Piece p4(Vec2(410,420),Qt::yellow);
       pl.push_back(p4);

       players.emplace_back(pl,i+1);
   }

       timer=new QTimer(this);
       timer->setInterval(500);
       timer->start();
       connect(timer,SIGNAL(timeout()),this,SLOT(update()));

}
}
MyWindow::~MyWindow()
{
    delete ui;
}

//aici hardcodez interfata
void MyWindow::DrawTable(QPainter &painter)
{
    painter.fillRect(QRect(0,0,600,600),QBrush(Qt::black));

    QPen inverter(Qt::white);
    inverter.setWidth(1);
    painter.setBrush(QColor(0,0,0));
    painter.setPen(inverter);
//tabla
     painter.drawRect(QRect(0,0,680,680));
     painter.drawRect(QRect(20,20,470,470));
     painter.drawLine(QLine(200,20,200,490));
     painter.drawLine(QLine(230,20,230,200));
     painter.drawLine(QLine(230,290,230,490));
     painter.drawLine(QLine(290,230,490,230));
     painter.drawLine(QLine(260,20,260,200));
     painter.drawLine(QLine(260,290,260,490));
     painter.drawLine(QLine(290,20,290,490));
     painter.drawLine(QLine(20,200,490,200));
     painter.drawLine(QLine(20,230,200,230));
     painter.drawLine(QLine(290,230,490,230));
     painter.drawLine(QLine(20,260,200,260));
     painter.drawLine(QLine(290,260,490,260));
     painter.drawLine(QLine(20,290,490,290));
     painter.drawLine(QLine(200,200,290,290));
     painter.drawLine(QLine(200,290,290,200));
     painter.fillRect(QRect(20,20,180,180),QBrush(Qt::red));//st sus
     painter.fillRect(QRect(20,290,180,200),QBrush(Qt::green));//st jos
     painter.fillRect(QRect(290,290,200,200),QBrush(Qt::yellow));//dr jos
     painter.fillRect(QRect(290,20,200,180),QBrush(Qt::blue));//dr sus
//liniile de la tabla
     for(int i=0;i<15;i++)
      {
          if(i>=6&&i<=9)
            continue;
             painter.drawLine(QLine(20+i*30,200,20+i*30,290));
      }
      for(int i=0;i<15;i++)
      {
          if(i>=6&&i<=9)
          continue;
        painter.drawLine(QLine(200,20+i*30,290,20+i*30));
      }
/*
      int x=55,y=55;
        painter.drawEllipse(x,y,30,30);
        painter.drawEllipse(x+270,y,30,30);
        painter.drawEllipse(x,y+270,30,30);
        painter.drawEllipse(x+270,y+270,30,30);
*/

//patrate rosii
    painter.fillRect(QRect(51,201,29,29),QBrush(Qt::red));//st sus
    //for care deneseaza 5 patrate rosii
    for (int i=0;i<150;i+=30)
    {
        painter.fillRect(QRect(51+i,231,29,29),QBrush(Qt::red));

    }
    //patrate galbene
    painter.fillRect(QRect(411,260,29,29),QBrush(Qt::yellow));
    for (int i=0;i<150;i+=30)
    {
        painter.fillRect(QRect(411-i,230,29,29),QBrush(Qt::yellow));

    }

    //bleu
    painter.fillRect(QRect(261,51,28,28),QBrush(Qt::blue));
    for (int i=0;i<150;i+=30)
    {
        painter.fillRect(QRect(231,51+i,29,29),QBrush(Qt::blue));

    }
    painter.fillRect(QRect(201,411,29,29),QBrush(Qt::green));
    for (int i=0;i<150;i+=30)
    {
        painter.fillRect(QRect(231,411-i,29,29),QBrush(Qt::green));

    }
    auto drawTriangle=[](QPainter& painter,qreal startPointX1,qreal startPointY1,qreal endPointX1,qreal endPointY1,qreal endPointX2,qreal endPointY2,const Qt::GlobalColor& color)
    {
        QPainterPath path;
        path.moveTo (startPointX1, startPointY1);
        path.lineTo (endPointX1, endPointY1);
        path.lineTo (endPointX2,   endPointY2);

        path.lineTo (startPointX1, startPointY1);

        painter.setPen (Qt :: NoPen);
        painter.fillPath (path, QBrush (color));
};
    // Start point of bottom line
    qreal startPointX1 = 201.0;
    qreal startPointY1 = 200.0;

    // End point of bottom line
    qreal endPointX1   = 201.0;
    qreal endPointY1   = 290.0;

    // End point of top line
    qreal endPointX2   = 245.0;
    qreal endPointY2   = 245.0;

    drawTriangle(painter,startPointX1,startPointY1,endPointX1,endPointY1,endPointX2,endPointY2,Qt::red);
//red
//blue area
    endPointX2=291.0;
    endPointY2=200.0;
    endPointX1=245.0;
    endPointY1=245.0;
    drawTriangle(painter,startPointX1,startPointY1,endPointX1,endPointY1,endPointX2,endPointY2,Qt::blue);
//blue

//yellow area
    startPointX1=291.0;
    startPointY1=200.0;
    endPointX1=291.0;
    endPointY1=291.0;
    endPointX2=245.0;
    endPointY2=245.0;

    drawTriangle(painter,startPointX1,startPointY1,endPointX1,endPointY1,endPointX2,endPointY2,Qt::yellow);
//yellow

//green area
    startPointX1=291.0;
    startPointY1=291.0;
    endPointX1=201.0;
    endPointY1=291.0;

drawTriangle(painter,startPointX1,startPointY1,endPointX1,endPointY1,endPointX2,endPointY2,Qt::green);

//green

}
void MyWindow::UpdateLabels()
{

}
void MyWindow::DrawPlayers(QPainter& painter)
{
    for(const auto&i: players)
    {
        for(size_t j=0;j<i.pieces.size();j++)
        {
            QPen inverter(Qt::white);
            inverter.setWidth(1);
            painter.setBrush(i.pieces[j].GetColor());
            painter.setPen(inverter);
            size_t x=i.pieces[j].GetPosition().x;
            size_t y=i.pieces[j].GetPosition().y;
            painter.drawEllipse(x,y,pieceRadius,pieceRadius);
        }
    }
}
void MyWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    DrawTable(painter);
    DrawPlayers(painter);
}

void MyWindow::update()
{
    this->repaint(0,0,600,600);//mandatory to work
}
