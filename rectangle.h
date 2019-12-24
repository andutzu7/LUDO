#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <QObject>
#include <QPainter>
#include "Vec2.h"
class Rectangle
{
public:
        Rectangle();
        Rectangle( float left_in,float right_in,float top_in,float bottom_in );
        Rectangle( const Vec2& topLeft,const Vec2& bottomRight );
        Rectangle( const Vec2& topLeft,float width,float height );
        bool IsOverlappingWith( const Rectangle& other ) const;
        bool IsContainedBy( const Rectangle& other ) const;
        static Rectangle FromCenter( const Vec2& center,float halfWidth,float halfHeight );
        Rectangle GetExpanded( float offset ) const;
        Vec2 GetCenter() const;
    public:
        float left;
        float right;
        float top;
        float bottom;
};

#endif // RECTANGLE_H
