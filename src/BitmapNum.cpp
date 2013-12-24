/*
 * BitmapNum.cpp
 *
 *  Created on: 2010-9-19
 *      Author: Administrator
 */

#include "BitmapNum.h"
#include "Data.h"
#define BEGIN_X    260
#define BEGIN_Y    15
#define NUM_WIDTH  21
#define NUM_HIGHT  30
void TBitmapNum::SetOriginNum(TInt aOriginNum, CData* aData)
{
    iData = aData;
    iOriginNum = aOriginNum;
    iUintNum = aOriginNum % 10;
    aOriginNum = aOriginNum / 10;
    iTenNum = aOriginNum % 10;
    aOriginNum = aOriginNum / 10;
    iHundredNum = aOriginNum % 10;
    aOriginNum = aOriginNum / 10;
    iThousandNum = aOriginNum % 10;
    //设置可见域
    TPoint point;
    point.SetXY(BEGIN_X, BEGIN_Y);
    iMotionThousands.SetVisibleArea(TRect(point.iX, point.iY, point.iX + NUM_WIDTH - 1, point.iY + NUM_HIGHT - 1));
    iMotionThousands.iMotionDirection = TMotionElement::ESouthToNorth;
    point.iX = point.iX + NUM_WIDTH;
    iMotionHundreds.SetVisibleArea(TRect(point.iX, point.iY, point.iX + NUM_WIDTH - 1, point.iY + NUM_HIGHT - 1));
    iMotionHundreds.iMotionDirection = TMotionElement::ESouthToNorth;
    point.iX = point.iX + NUM_WIDTH;
    iMotionTens.SetVisibleArea(TRect(point.iX, point.iY, point.iX + NUM_WIDTH - 1, point.iY + NUM_HIGHT - 1));
    iMotionTens.iMotionDirection = TMotionElement::ESouthToNorth;
    point.iX = point.iX + NUM_WIDTH;
    iMotionUnits.SetVisibleArea(TRect(point.iX, point.iY, point.iX + NUM_WIDTH - 1, point.iY + NUM_HIGHT - 1));
    iMotionUnits.iMotionDirection = TMotionElement::ESouthToNorth;
    //设置初始数字
    iMotionThousands.SetNewAndOldMapRect(GetMotionRectByNum(iThousandNum), GetMotionRectByNum(iThousandNum));
    iMotionHundreds.SetNewAndOldMapRect(GetMotionRectByNum(iHundredNum), GetMotionRectByNum(iHundredNum));
    iMotionTens.SetNewAndOldMapRect(GetMotionRectByNum(iTenNum), GetMotionRectByNum(iTenNum));
    iMotionUnits.SetNewAndOldMapRect(GetMotionRectByNum(iUintNum), GetMotionRectByNum(iUintNum));
}
void TBitmapNum::UpdateNum(TInt aNewNum)
{
    if (iOriginNum == aNewNum || iData->iGameState!=TEnum::EPlaying)
    {
        return;
    }
    //
    iOriginNum = aNewNum;
    TInt num = aNewNum % 10;
    aNewNum = aNewNum / 10;
    if (iUintNum != num)
    {
        iMotionUnits.SetNewAndOldMapRect(GetMotionRectByNum(num), GetMotionRectByNum(iUintNum));
        iUintNum = num;
    }
    num = aNewNum % 10;
    aNewNum = aNewNum / 10;
    if (iTenNum != num)
    {
        iMotionTens.SetNewAndOldMapRect(GetMotionRectByNum(num), GetMotionRectByNum(iUintNum));
        iTenNum = num;
    }
    num = aNewNum % 10;
    aNewNum = aNewNum / 10;
    if (iHundredNum != num)
    {
        iMotionHundreds.SetNewAndOldMapRect(GetMotionRectByNum(num), GetMotionRectByNum(iUintNum));
        iHundredNum = num;
    }
    num = aNewNum % 10;
    aNewNum = aNewNum / 10;
    if (iThousandNum != num)
    {
        iMotionThousands.SetNewAndOldMapRect(GetMotionRectByNum(num), GetMotionRectByNum(iUintNum));
        iThousandNum = num;
    }
}

void TBitmapNum::Quantum()
{
    iMotionTens.Quantum();
    iMotionHundreds.Quantum();
    iMotionThousands.Quantum();
    iMotionUnits.Quantum();
}

void TBitmapNum::Draw(CWsBitmap* aBitmap, CWsBitmap* aResourceBitmap)
{
    iMotionTens.Draw(aBitmap, aResourceBitmap);
    iMotionHundreds.Draw(aBitmap, aResourceBitmap);
    iMotionThousands.Draw(aBitmap, aResourceBitmap);
    iMotionUnits.Draw(aBitmap, aResourceBitmap);
}
TRect TBitmapNum::GetMotionRectByNum(TInt aNum)
{
    TRect rect;
    rect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::EFontTitleNum0, aNum);
    return rect;
}
