/*
 * WorldPoint.h
 *
 *  Created on: 2010-6-28
 *      Author: Administrator
 */

#ifndef WORLDPOINT_H_
#define WORLDPOINT_H_

#include <e32std.h>
#include <e32base.h>

typedef TInt T;

class TWorldPoint
{
public:
    TWorldPoint()
    {
    }
    ;
    inline TWorldPoint(T aX, T aY);
    inline T X() const;
    inline T Y() const;
    inline void SetX(T aX);
    inline void SetY(T aY);
    inline void SetXY(T aY, T aX);

    inline TInt operator==(const TWorldPoint& aPoint) const;
    inline TInt operator!=(const TWorldPoint& aPoint) const;
    inline TWorldPoint& operator-=(const TWorldPoint& aPoint);
    inline TWorldPoint& operator+=(const TWorldPoint& aPoint);
    inline TWorldPoint operator-(const TWorldPoint& aPoint) const;
    inline TWorldPoint operator+(const TWorldPoint& aPoint) const;
    inline TWorldPoint operator-() const;

public:
    T iX;
    T iY;
};

inline TWorldPoint::TWorldPoint(T aX, T aY) :
    iX(aX), iY(aY)
{
}

inline T TWorldPoint::X() const
{
    return iX;
}
inline T TWorldPoint::Y() const
{
    return iY;
}
inline void TWorldPoint::SetX(T aX)
{
    iX = aX;
}

inline void TWorldPoint::SetY(T aY)
{
    iY = aY;
}
inline void TWorldPoint::SetXY(T aY, T aX)
{
    SetX(aX);
    SetY(aY);
}

inline TInt TWorldPoint::operator!=(const TWorldPoint& aPoint) const
{
    return !(*this == aPoint);
}

inline TWorldPoint& TWorldPoint::operator-=(const TWorldPoint& aPoint)
{
    iX -= aPoint.X();
    iY -= aPoint.Y();
    return *this;
}

inline TWorldPoint& TWorldPoint::operator+=(const TWorldPoint& aPoint)
{
    iX += aPoint.X();
    iY += aPoint.Y();
    return *this;
}

inline TInt TWorldPoint::operator==(const TWorldPoint& aPoint) const
{
    return (X() == aPoint.X()) && (Y() == aPoint.Y());
}

inline TWorldPoint TWorldPoint::operator-(const TWorldPoint& aPoint) const
{
    return TWorldPoint(X() - aPoint.X(), Y() - aPoint.Y());
}

inline TWorldPoint TWorldPoint::operator+(const TWorldPoint& aPoint) const
{
    return TWorldPoint(X() + aPoint.X(), Y() + aPoint.Y());
}

inline TWorldPoint TWorldPoint::operator-() const
{
    return TWorldPoint(-X(), -Y());
}

#endif /* WORLDPOINT_H_ */
