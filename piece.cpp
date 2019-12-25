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
