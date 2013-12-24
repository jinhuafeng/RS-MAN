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
    TPoint iStartPoint;//���
    TPoint iEndPoint;//�յ�
    TRect iBitMapRect;//ͼ������Դ�е�λ��
    TRect iHighLightRect;
    TRect iHighLightLeftTopRect;
    //Button�ĵ�ǰ�˶�����
    TEnum::TButtonState iActionType;
    TPoint iCenter;//���ĵ�
    TRect iWorldPosition;//����Ļ�ϵ�λ��
    TRect iDrawableBitMapRect;//ͼ����Դͼ�п��Ա�����λ��
    TInt iDetalX;//��ǰ�ٶ�
    TInt iTicks;
    TBool iIsNeedDraw;
    TBool iIsButtonDown;
    TInt iHalfHeight;
    TInt iHalfWidth;
    TBool iIsNeedHighLight;
};

#endif /* BUTTONELEMENT_H_ */
