#ifndef PIECE_H
#define PIECE_H
#include "Vec2.h"
#include <QPainter>
#define playerRay 20
class Piece
{
private:
    Vec2 position;
    Qt::GlobalColor color;
public:
    Piece(const Vec2& nPos,const Qt::GlobalColor& nColor)
        :
      position(nPos),
      color(nColor)
        {};
    Vec2 GetPosition() const;
    Qt::GlobalColor GetColor() const;
    void UpdatePosition(const Vec2& newPos);
private slots:
    void Draw(QPainter& painter);
};

#endif // PIECE_H
