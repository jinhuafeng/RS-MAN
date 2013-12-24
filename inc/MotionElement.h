/*
 * MotionElement.h
 *
 *  Created on: 2010-9-15
 *      Author: Administrator
 */

#ifndef MOTIONELEMENT_H_
#define MOTIONELEMENT_H_


#include <W32STD.H> 
#include "WorldPoint.h"
#include "BitMapPosition.h"
#include "Enum.h"

class TMotionElement
{
public:
    enum TMotionDirection
    {
        EEastToWest, EWestToEast, ENorthToSouth, ESouthToNorth
    };
public:
    void Quantum();
    void Draw(CWsBitmap* aBitmap, CWsBitmap* aResourceBitmap);
    //先行函数
    void SetVisibleArea(TRect aVisibleArea);
    void SetNewAndOldMapRect(TRect aNewMapRect,TRect aOldMapRect);
    void UpdateObjectData();
    //
    void UpdateWorldPosition();
    void CalcDrawableRect();
    void GetBitMapRect();
public:
    TPoint iNewMapCenter;//准备进入视线的位图的Center的位置
    TPoint iOldMapCenter;//准备离开视线的位图的Center的位置
    TInt iMotionDistance;//此次动作需要移动的距离
    TInt iCurrMotionDistance;//当前已经移动的距离
    //
    TRect iNewBitMapRect;
    TRect iOldBitMapRect;
    TRect iNewMapDrawableRect;
    TRect iOldMapDrawableRect;
    TRect iNewMapWorldPosition;
    TRect iOldMapWorldPosition;
    TRect iVisibleArea;//对于此对象来说，可见域范围
    TMotionDirection iMotionDirection;
    TInt iDetal;//移动速度,该值为正值
    TBool iIsNewMapNeedDraw;
    TBool iIsOldMapNeedDraw;
    TInt iHalfHeight;
    TInt iHalfWidth;
};

#endif /* MOTIONELEMENT_H_ */
