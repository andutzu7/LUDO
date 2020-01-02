#ifndef PIECE_H
#define PIECE_H
#include "Vec2.h"
#include <QPainter>
#define playerRay 20
class Piece
{
private:
    Vec2 position;
    Vec2 velocity;
    Qt::GlobalColor color;

public:
    Piece(const Vec2& nPos,const Vec2& nVelocity,const Qt::GlobalColor& nColor)
        :
      position(nPos),
      velocity(nVelocity),
      color(nColor)
        {};
    bool selected=false;
    bool inBase=true;
    int traveledSquares=0;
    bool Contains(const Vec2& other);
    Vec2 GetPosition() const;
    void SetVelocity(const Vec2& newVel);
    Vec2 GetVelocity() const;
    Qt::GlobalColor GetColor() const;
    void UpdatePosition(const Vec2& newPos);
};

#endif // PIECE_H
