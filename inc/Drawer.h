/*
 * Drawer.h
 *
 *  Created on: 2010-8-10
 *      Author: panda
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include <W32STD.H> 
#include "BitMapPosition.h"
#include "Enum.h"

class TDrawer
{
public:
    TDrawer();
    //画箭头按钮部分函数
    void Draw(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey,
        TEnum::TLayoutType aLayoutType);
    void DrawControlByLeftHand(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey);
    void DrawControlByHands(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey);
    void DrawControlByRightHand(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey);
    void DrawReturnArrow(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, 
        TRect aWorldPointRect, TRect aBitMapRect);
    //
    void GetBitMapRect();
    void SetBitmapPositon(TBitMapPosition* apBitMapPositon);
    void DrawBackground(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap);
    //画游戏界面Title
    void DrawTitleBackground(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap);
    //
    void DrawUpLimitStab(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap);
    void DrawWholeBackground(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap);
    //用于Option中画白线之用
    void DrawLine(CWsBitmap* aBackUpBitmap, TPoint aStartPoint);
    //画生命值
    void DrawLifeValue(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap,TInt aLifeValue);
    //根据Y坐标，画背景的一部分
    void DrawBackgoundClip(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap,TInt aStartY,TInt aEndY);
private:
    TRect iTouchLeftRect;
    TRect iTouchLeftDownRect;
    TRect iTouchCenterInnerRect;
    TRect iTouchCenterInnerDownRect;
    //
    TRect iBackgorundRect;
    //
    TRect iUpLimitRect;
    TBitMapPosition* ipBitMapPosition;
};
#endif /* DRAWER_H_ */
