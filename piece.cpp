#include "piece.h"

Qt::GlobalColor Piece::GetColor() const
{
    return color;
}

Vec2 Piece::GetPosition() const
{
    return position;
}
void Piece::UpdatePosition(const Vec2 &newPos)
{
    position=newPos;
}
 void Piece::SetVelocity(const Vec2 &newVel)
 {
     velocity=newVel;
 }
 Vec2 Piece::GetVelocity() const
 {
     return velocity;
 }
bool Piece::Contains(const Vec2& other)
{
    return (position.x<=other.x && (position.x+playerRay)>=other.x && position.y<=other.y && (position.y+playerRay)>=other.y);
}
