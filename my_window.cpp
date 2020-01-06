#include "my_window.h"
#include "ui_mywindow.h"
#include <QDebug>
#include <string>
#include <QLayout>
MyWindow::MyWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWindow)
{
    ui->setupUi(this);
    QPainter painter(this);
    const int screenWidth=800;
    const int screenHeight=600;
    const int squareDelta=50;
    ui->valzar->setText(QString::fromStdString(""));
for (size_t i=0;i<screenWidth;i+=squareDelta)
{
    for(size_t j=0;j<screenHeight;j+=squareDelta)
    {
        QRect r(i,j,i+squareDelta,j+squareDelta);
    }
}
     this->ui->text_cast->hide();
    this->ui->nr_cast->hide();

for(size_t i=0;i<playersNumber;i++)//initializam toti playerii
{
    //urmeaza o portiune de-9 cod rusinoasa
    if(i==0)
    {
        std::vector<Piece> pl;
        Piece p(Vec2(51,61),Vec2(1,0),Qt::red);
        pl.push_back(p);
        Piece p2(Vec2(121,61),Vec2(1,0),Qt::red);
        pl.push_back(p2);
        Piece p3(Vec2(51,151),Vec2(1,0),Qt::red);
        pl.push_back(p3);
        Piece p4(Vec2(121,151),Vec2(1,0),Qt::red);
        pl.push_back(p4);

        players.emplace_back(pl,i+1);

   }
   if(i==1) //albastu
   {
       std::vector<Piece> pl;
       Piece p(Vec2(340,61),Vec2(0,1),Qt::blue);
       pl.push_back(p);
       Piece p2(Vec2(410,61),Vec2(0,1),Qt::blue);
       pl.push_back(p2);
       Piece p3(Vec2(340,151),Vec2(0,1),Qt::blue);
       pl.push_back(p3);
       Piece p4(Vec2(410,151),Vec2(0,1),Qt::blue);
       pl.push_back(p4);

       players.emplace_back(pl,i+1);

   }
    if(i==2) //green
   {


        std::vector<Piece> pl;
        Piece p(Vec2(51,330),Vec2(0,-1),Qt::green);
        pl.push_back(p);
        Piece p2(Vec2(121,330),Vec2(0,-1),Qt::green);
        pl.push_back(p2);
        Piece p3(Vec2(51,420),Vec2(0,-1),Qt::green);
        pl.push_back(p3);
        Piece p4(Vec2(121,420),Vec2(0,-1),Qt::green);
        pl.push_back(p4);

        players.emplace_back(pl,i+1);
   }
   if(i==3) //yellow
   {

       std::vector<Piece> pl;
       Piece p(Vec2(340,330),Vec2(-1,0),Qt::yellow);
       pl.push_back(p);
       Piece p2(Vec2(410,330),Vec2(-1,0),Qt::yellow);
       pl.push_back(p2);
       Piece p3(Vec2(340,420),Vec2(-1,0),Qt::yellow);
       pl.push_back(p3);
       Piece p4(Vec2(410,420),Vec2(-1,0),Qt::yellow);
       pl.push_back(p4);

       players.emplace_back(pl,i+1);
   }

       timer=new QTimer(this);
       timer->setInterval(500);
       timer->start();
       connect(timer,SIGNAL(timeout()),this,SLOT(update()));
       connect(this->ui->diceButton, SIGNAL(clicked()), this, SLOT(diceButton_onClicked()));

}
setMouseTracking(true);

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
      ;
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
    ui->nr_juc->setText(QString::fromStdString(std::to_string(playersNumber)));
    ui->labelPlayer->setText(QString::fromStdString(std::to_string(currentPlayer)));
}
void MyWindow::mousePressEvent(QMouseEvent *event)
{
    for(auto& i:players) //vedem care/daca o piesa a fost selectata
    {
        for(int j=0;j<4;j++)
        {
            int x=event->pos().x();
            int y=event->pos().y();
            if(i.pieces[j].Contains(Vec2(x,y)))
            {
                i.pieces[j].selected=true;

                break;
            }

        }
    }

}
void MyWindow::diceButton_onClicked()
{
      int roll;
      int min = 1; // the min number a die can roll is 1
      int max = 6;// this->dieSize; // the max value is the die size
      roll = rand() % (max - min + 1) + min;
      this->ui->valzar->setText(QString::fromStdString(std::to_string(roll)));
       diceWRolled=true;
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
void MyWindow::UpdateVelocity(int nrOfSquaresTraveled)
{
    std::vector<Vec2>redVel=   {Vec2(0,-1),Vec2(1,0),Vec2(0,1),Vec2(1,0),Vec2(0,1),Vec2(-1,0),Vec2(0,1),Vec2(-1,0),Vec2(0,-1),Vec2(-1,0),Vec2(0,-1),Vec2(1,0)};
    std::vector<Vec2>blueVel=  {Vec2(1,0),Vec2(0,1),Vec2(-1,0),Vec2(0,1),Vec2(-1,0),Vec2(0,-1),Vec2(-1,0),Vec2(0,-1),Vec2(1,0),Vec2(0,-1),Vec2(1,0),Vec2(0,1)};
    std::vector<Vec2>greenVel= {Vec2(-1,0),Vec2(0,-1),Vec2(1,0),Vec2(0,-1),Vec2(1,0),Vec2(0,1),Vec2(1,0),Vec2(0,1),Vec2(-1,0),Vec2(0,1),Vec2(-1,0),Vec2(0,-1) };
    std::vector<Vec2>yellowVel={Vec2(0,1),Vec2(-1,0),Vec2(0,-1),Vec2(-1,0),Vec2(0,-1),Vec2(1,0),Vec2(0,-1),Vec2(1,0),Vec2(0,1),Vec2(1,0),Vec2(0,1),Vec2(-1,0)};
    switch(nrOfSquaresTraveled)
{

    case 6:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[0]);
            }
        }
        if(currentPlayer==2)//albastru
        {

            for(int i=0;i<4;i++)
            if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                players[currentPlayer-1].pieces[i].SetVelocity(blueVel[0]);
        }
        if(currentPlayer==3)//verde
        {

            for(int i=0;i<4;i++)
            if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                players[currentPlayer-1].pieces[i].SetVelocity(greenVel[0]);
        }
        if(currentPlayer==4)//galben
        {

            for(int i=0;i<4;i++)
            if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[0]);
        }
        break;
    case 12:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[1]);
            }
        }
          if(currentPlayer==2)//albastru
          {
              for(int i=0;i<4;i++)
              {
               if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                   players[currentPlayer-1].pieces[i].SetVelocity(blueVel[1]);
              }
          }
         if(currentPlayer==3)//verde
         {
             for(int i=0;i<4;i++)
             {
              if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                  players[currentPlayer-1].pieces[i].SetVelocity(greenVel[1]);
             }
         }
                  if(currentPlayer==4)//galben

                  {
                      for(int i=0;i<4;i++)
                      {
                       if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                           players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[1]);
                      }
                  }
                      break;
    case 14:
        if(currentPlayer==1)//ROSU
            {
                for(int i=0;i<4;i++)
                {
                 if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                     players[currentPlayer-1].pieces[i].SetVelocity(redVel[2]);
                }
            }
            if(currentPlayer==2)//albastru

                {
                    for(int i=0;i<4;i++)
                    {
                     if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                         players[currentPlayer-1].pieces[i].SetVelocity(blueVel[2]);
                    }
                }
                if(currentPlayer==3)//verde
                    {
                        for(int i=0;i<4;i++)
                        {
                         if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                             players[currentPlayer-1].pieces[i].SetVelocity(greenVel[2]);
                        }
                    }
                    if(currentPlayer==4)//galben
                        {
                            for(int i=0;i<4;i++)
                            {
                             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[2]);
                            }
                        }
        break;
    case 20:
        if(currentPlayer==1)//ROSU
            {
                for(int i=0;i<4;i++)
                {
                 if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                     players[currentPlayer-1].pieces[i].SetVelocity(redVel[3]);
                }
            }
        if(currentPlayer==2)//albastru
            {
                for(int i=0;i<4;i++)
                {
                 if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                     players[currentPlayer-1].pieces[i].SetVelocity(blueVel[3]);
                }
            }
        if(currentPlayer==3)//verde
            {
                for(int i=0;i<4;i++)
                {
                 if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                     players[currentPlayer-1].pieces[i].SetVelocity(greenVel[3]);
                }
            }
        if(currentPlayer==4)//galbe
            {
                for(int i=0;i<4;i++)
                {
                 if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                     players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[3]);
                }
            }
        break;
    case 26:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[4]);
            }
        }


        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[4]);
            }
        }

            if(currentPlayer==3)//verde
            {
                for(int i=0;i<4;i++)
                {
                 if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                     players[currentPlayer-1].pieces[i].SetVelocity(greenVel[4]);
                }
            }

                if(currentPlayer==4)//galben
                {
                    for(int i=0;i<4;i++)
                    {
                     if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                         players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[4]);
                    }
                }

        break;
    case 28:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[5]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[5]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[5]);
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[5]);
            }
        }

        break;
    case 34:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[6]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[6]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[6]);
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[6]);
            }
        }

        break;
    case 40:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[7]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[7]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[7]);
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[7]);
            }
        }

        break;
    case 42:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[8]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[8]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[8]);
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[8]);
            }
        }

        break;
    case 48:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[9]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[9]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[9]);
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[9]);
            }
        }

        break;
    case 54:
        if( currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[10]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[10]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[10]);
            }
        }

        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[10]);
            }
        }

        break;
    case 55:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(redVel[11]);
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(blueVel[11]);
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(greenVel[11]);
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(yellowVel[11]);
            }
        }

        break;
    case 61:
        if(currentPlayer==1)//ROSU
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(Vec2(0,0));
            }
        }
        if(currentPlayer==2)//albastru
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(Vec2(0,0));
            }
        }
        if(currentPlayer==3)//verde
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(Vec2(0,0));
            }
        }
        if(currentPlayer==4)//galben
        {
            for(int i=0;i<4;i++)
            {
             if(players[currentPlayer-1].pieces[i].selected)//schimbam piesa care se misca
                 players[currentPlayer-1].pieces[i].SetVelocity(Vec2(0,0));
            }
        }

        break;
    }

}// win condition
void MyWindow::Game()
{
    std::vector<Vec2> startingPositions={{56,205},{266,56},{207,416},{417,266}};
    std::vector<int> dontDrawIndexes={5,19,33,47};
    if(!gameOver)
    {
        if(diceWRolled)//mutam piesa
        {
            players[currentPlayer].nrOfMoves++;
            int amount = ui->valzar->text().toInt();
            //some code for testing purposes
            //currentplayer-1 ptc eu afisez nr ala pe ecran

            if(amount==6)//scoatem o piesa
            {   int i;
                for(i=0;i<4;i++)
                {
                 if( players[currentPlayer-1].pieces[i].inBase==true)
                 {
                     players[currentPlayer-1].pieces[i].inBase=false;

                     players[currentPlayer-1].pieces[i].UpdatePosition(startingPositions.at(currentPlayer-1));

                     players[currentPlayer-1].pieces[i].selected=true;
                        break;
                 }

                }
            }
            int i;
            for( i=0;i<4;i++)
            {
                if(players[currentPlayer-1].pieces[i].selected )
            {
                    if(players[currentPlayer-1].pieces[i].inBase==false)
                    {

                    Vec2 delta={30,30};//Cat ma deplasez pe x i pe y


                    if(players[currentPlayer-1].pieces[i].inFinalArea)
                    {

                        if( players[currentPlayer-1].pieces[i].traveledSquares+amount!=61)//daca nu pica un nr exact dupa ce esti in area resp
                            amount=0;
                        if(players[currentPlayer-1].pieces[i].traveledSquares+amount==61)
                        {
                        players[currentPlayer-1].nrOfPiecesHome++;
                            if(players[currentPlayer-1].nrOfPiecesHome==4)
                            {
                                gameOver=true;
                                this->ui->nr_cast->setText(QString::fromStdString(std::to_string(currentPlayer-1)));
                                this->ui->text_cast->show();
                                this->ui->nr_cast->show();
                            //SEND TO THE SERVER THE NROFMOVES
                            }
                        }
                        UpdateVelocity(players[currentPlayer-1].pieces[i].traveledSquares);
                        Vec2 currentPosition=players[currentPlayer-1].pieces[i].GetPosition();
                        Vec2 currentVelocity=players[currentPlayer-1].pieces[i].GetVelocity();
                        players[currentPlayer-1].pieces[i].UpdatePosition(currentPosition+(delta*currentVelocity));
                        amount--;
                        //nu e chiar asa elegant dar nu imi vine nici o alta idee cum sa nu fac insta update
                       auto Sleep=[](int ms)
                       {
                           struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
                               nanosleep(&ts, NULL);
                       };

                       if(std::find(dontDrawIndexes.begin(),dontDrawIndexes.end(),players[currentPlayer-1].pieces[i].traveledSquares)==dontDrawIndexes.end())//daca nr parcurs pna acum nu se afla printre astea
                       {
                           this->repaint(0,0,600,600);//mandatory to work
                           Sleep(500); //ca sa nu se refaca desenu instant

                       }
                    }
                    else
                      {
                        while(amount)
                    {
                        players[currentPlayer-1].pieces[i].traveledSquares++;
                        if( players[currentPlayer-1].pieces[i].traveledSquares>55 )
                            players[currentPlayer-1].pieces[i].inFinalArea=true;
                        UpdateVelocity(players[currentPlayer-1].pieces[i].traveledSquares);
                        Vec2 currentPosition=players[currentPlayer-1].pieces[i].GetPosition();
                        Vec2 currentVelocity=players[currentPlayer-1].pieces[i].GetVelocity();
                        players[currentPlayer-1].pieces[i].UpdatePosition(currentPosition+(delta*currentVelocity));
                        amount--;
                        //nu e chiar asa elegant dar nu imi vine nici o alta idee cum sa nu fac insta update
                       auto Sleep=[](int ms)
                       {
                           struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
                               nanosleep(&ts, NULL);
                       };

                       if(std::find(dontDrawIndexes.begin(),dontDrawIndexes.end(),players[currentPlayer-1].pieces[i].traveledSquares)==dontDrawIndexes.end())//daca nr parcurs pna acum nu se afla printre astea
                       {
                           this->repaint(0,0,600,600);//mandatory to work
                           Sleep(500); //ca sa nu se refaca desenu instant

                       }
                       else
                       {
                       amount++;//pt cum am proiectat jocu ar fi fost un patrat pierdere la colturi;
                       }
                    }
                    }

                    }

            }
            players[currentPlayer-1].pieces[i].selected=false;

            }
            diceWRolled=false;

                if(currentPlayer!=(int)playersNumber)
            {
                currentPlayer++;

            }
                else
            {
               currentPlayer=1;
            }


        }


    }
}
void MyWindow::update()
{
    Game();
    UpdateLabels();
    this->repaint(0,0,600,600);//mandatory to work

}
