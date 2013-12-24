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
    //���к���
    void SetVisibleArea(TRect aVisibleArea);
    void SetNewAndOldMapRect(TRect aNewMapRect,TRect aOldMapRect);
    void UpdateObjectData();
    //
    void UpdateWorldPosition();
    void CalcDrawableRect();
    void GetBitMapRect();
public:
    TPoint iNewMapCenter;//׼���������ߵ�λͼ��Center��λ��
    TPoint iOldMapCenter;//׼���뿪���ߵ�λͼ��Center��λ��
    TInt iMotionDistance;//�˴ζ�����Ҫ�ƶ��ľ���
    TInt iCurrMotionDistance;//��ǰ�Ѿ��ƶ��ľ���
    //
    TRect iNewBitMapRect;
    TRect iOldBitMapRect;
    TRect iNewMapDrawableRect;
    TRect iOldMapDrawableRect;
    TRect iNewMapWorldPosition;
    TRect iOldMapWorldPosition;
    TRect iVisibleArea;//���ڴ˶�����˵���ɼ���Χ
    TMotionDirection iMotionDirection;
    TInt iDetal;//�ƶ��ٶ�,��ֵΪ��ֵ
    TBool iIsNewMapNeedDraw;
    TBool iIsOldMapNeedDraw;
    TInt iHalfHeight;
    TInt iHalfWidth;
};

#endif /* MOTIONELEMENT_H_ */
