/*
 * ButtonElement.h
 *
 *  Created on: 2010-8-29
 *      Author: panda
 */

#ifndef BUTTONELEMENT_H_
#define BUTTONELEMENT_H_

#include <W32STD.H> 
#include "WorldPoint.h"
#include "BitMapPosition.h"
#include "Enum.h"

class TButtonElement
{
public:
    void Quantum();
    void Draw(CWsBitmap* aBitmap, CWsBitmap* aResourceBitmap);
    void DrawHighLight(CWsBitmap* aBitmap,CWsBitmap* aResourceBitmap);
    TBool IsEnterPositionFinish();
    TBool IsButtonLeaveFinish();
    void SetHighLightRect(TRect aLeftTopRect,TRect aRect);
    void ReSet();
    void SetStartAndEndPoint(TPoint aStartPoint, TPoint aEndPoint);
    void SetBitMapRect(TRect aBitMapRect);
    void UpdateObjectByCenter();
public:
    TPoint iStartPoint;//起点
    TPoint iEndPoint;//终点
    TRect iBitMapRect;//图形中资源中的位置
    TRect iHighLightRect;
    TRect iHighLightLeftTopRect;
    //Button的当前运动类型
    TEnum::TButtonState iActionType;
    TPoint iCenter;//中心点
    TRect iWorldPosition;//在屏幕上的位置
    TRect iDrawableBitMapRect;//图形资源图中可以被画的位置
    TInt iDetalX;//当前速度
    TInt iTicks;
    TBool iIsNeedDraw;
    TBool iIsButtonDown;
    TInt iHalfHeight;
    TInt iHalfWidth;
    TBool iIsNeedHighLight;
};

#endif /* BUTTONELEMENT_H_ */
