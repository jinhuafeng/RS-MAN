/*
 * Drawer.cpp
 *
 *  Created on: 2010-8-10
 *      Author: panda
 */

#include "Drawer.h"
#include <e32std.h>
#include <e32base.h>
#include <e32math.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include "WorldObject.h"
#include "Macro.h"

//#define Y_AXIS_MIN_LIMIT 70
//#define Y_AXIS_MAX_LIMIT 530
#define X_WIDTH  360
#define Y_HEIGHT  109
#define X_CENTER_WIDTH 108
#define CENTER_COLOR  0x8FA3BA
#define SPLIT_LINE_COLOR  0xB3E1F3

//生命值 起点
#define LIFE_BEGIN_X    70
#define LIFE_BEGIN_Y    19

void TDrawer::SetBitmapPositon(TBitMapPosition* apBitMapPositon)
{
    ipBitMapPosition = apBitMapPositon;
}
TDrawer::TDrawer()
{

}

void TDrawer::GetBitMapRect()
{
    iTouchLeftRect = ipBitMapPosition->GetPosition(TBitMapPosition::TouchLeft, 0);
    iTouchLeftDownRect = ipBitMapPosition->GetPosition(TBitMapPosition::TouchLeftDown, 0);
    iTouchCenterInnerRect = ipBitMapPosition->GetPosition(TBitMapPosition::TouchCenterInner, 0);
    iTouchCenterInnerDownRect = ipBitMapPosition->GetPosition(TBitMapPosition::TouchCenterInnerDown, 0);
    //
    iUpLimitRect = ipBitMapPosition->GetPosition(TBitMapPosition::UpLimit, 0);
    //
    iBackgorundRect.SetRect(0, Y_AXIS_MIN_LIMIT, 359, Y_AXIS_MAX_LIMIT);
}

void TDrawer::DrawBackground(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    TInt iCounts = 360 * (iBackgorundRect.iBr.iY - iBackgorundRect.iTl.iY + 1);
    addr22 = addr2 + iBackgorundRect.iTl.iY * desSize.iWidth;
    addr11 = addr1;
    for (TInt i = 0; i < iCounts; i++)
    {
        *addr22++ = *addr11++;
    }
    backUpUtil.End();
    objectUtil.End();
}
void TDrawer::DrawWholeBackground(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    TInt iCounts = desSize.iHeight * desSize.iWidth;
    addr22 = addr2;
    addr11 = addr1;
    for (TInt i = 0; i < iCounts; i++)
    {
        *addr22++ = *addr11++;
    }
    backUpUtil.End();
    objectUtil.End();
}
void TDrawer::Draw(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey,
    TEnum::TLayoutType aLayoutType)
{
    switch (aLayoutType)
    {
        case TEnum::ELeftHand:
        {
            DrawControlByLeftHand(aBackUpBitmap, aResourceBitmap, aGameKey);
            break;
        }
        case TEnum::EHands:
        {
            DrawControlByHands(aBackUpBitmap, aResourceBitmap, aGameKey);
            break;
        }
        case TEnum::ERightHand:
        {
            DrawControlByRightHand(aBackUpBitmap, aResourceBitmap, aGameKey);
            break;
        }
    }
}

void TDrawer::DrawControlByLeftHand(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize NewSize = TSize(X_WIDTH, Y_HEIGHT);
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    //
    TRect oLeftRect;
    TRect oReturnRect;
    TRect oRightRect;
    switch (aGameKey)
    {
        case TEnum::EKeyLeft:
        {
            oLeftRect = iTouchLeftDownRect;
            oReturnRect = iTouchCenterInnerRect;
            //右键头需要通过反转获得
            oRightRect = iTouchLeftRect;
            break;
        }
        case TEnum::EKeyPause:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerDownRect;
            oRightRect = iTouchLeftRect;
            break;
        }
        case TEnum::EKeyRight:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerRect;
            oRightRect = iTouchLeftDownRect;
            break;
        }
        case TEnum::EKeyNone:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerRect;
            oRightRect = iTouchLeftRect;
            break;
        }
        default:
        {
            return;
        }
    }

    //中间色
    R8G8B8 oCenterColor = CENTER_COLOR;
    //
    for (TInt j = 0; j < NewSize.iHeight; j++)
    {
        //画左键头
        addr22 = addr2 + (Y_AXIS_MAX_LIMIT + 1 + j) * desSize.iWidth;
        addr11 = addr1 + (oLeftRect.iTl.iY + j) * srcSize.iWidth + oLeftRect.iTl.iX;
        TInt iCounts = oLeftRect.iBr.iX - oLeftRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        //画中间线
        *addr22 = oCenterColor;
        addr22++;
        //画右键头
        addr11 = addr1 + (oRightRect.iTl.iY + j) * srcSize.iWidth + oRightRect.iBr.iX;
        iCounts = oRightRect.iBr.iX - oRightRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11--;
        }

        //画中间线
        *addr22 = oCenterColor;
        addr22++;
        //重复暂停键中间部分
        addr11 = addr1 + (oReturnRect.iTl.iY + j) * srcSize.iWidth + oReturnRect.iTl.iX;
        iCounts = oReturnRect.iBr.iX - oReturnRect.iTl.iX + 1;
        for (TInt i = 0; i < X_CENTER_WIDTH; i++)
        {
            *addr22 = *addr11;
            addr22++;
        }
    }
    backUpUtil.End();
    objectUtil.End();
}

void TDrawer::DrawControlByHands(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize NewSize = TSize(X_WIDTH, Y_HEIGHT);
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    //
    TRect oLeftRect;
    TRect oReturnRect;
    TRect oRightRect;
    switch (aGameKey)
    {
        case TEnum::EKeyLeft:
        {
            oLeftRect = iTouchLeftDownRect;
            oReturnRect = iTouchCenterInnerRect;
            //右键头需要通过反转获得
            oRightRect = iTouchLeftRect;
            break;
        }
        case TEnum::EKeyPause:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerDownRect;
            oRightRect = iTouchLeftRect;
            break;
        }
        case TEnum::EKeyRight:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerRect;
            oRightRect = iTouchLeftDownRect;
            break;
        }
        case TEnum::EKeyNone:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerRect;
            oRightRect = iTouchLeftRect;
            break;
        }
        default:
        {
            return;
        }
    }

    //中间色
    R8G8B8 oCenterColor = CENTER_COLOR;
    //
    for (TInt j = 0; j < NewSize.iHeight; j++)
    {
        //画左键头
        addr22 = addr2 + (Y_AXIS_MAX_LIMIT + 1 + j) * desSize.iWidth;
        addr11 = addr1 + (oLeftRect.iTl.iY + j) * srcSize.iWidth + oLeftRect.iTl.iX;
        TInt iCounts = oLeftRect.iBr.iX - oLeftRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        //画中间线
        *addr22 = oCenterColor;
        addr22++;
        //重复暂停键中间部分
        addr11 = addr1 + (oReturnRect.iTl.iY + j) * srcSize.iWidth + oReturnRect.iTl.iX;
        iCounts = oReturnRect.iBr.iX - oReturnRect.iTl.iX + 1;
        for (TInt i = 0; i < X_CENTER_WIDTH; i++)
        {
            *addr22 = *addr11;
            addr22++;
        }

        //画中间线
        *addr22 = oCenterColor;
        addr22++;
        //画右键头
        addr11 = addr1 + (oRightRect.iTl.iY + j) * srcSize.iWidth + oRightRect.iBr.iX;
        iCounts = oRightRect.iBr.iX - oRightRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11--;
        }
    }
    backUpUtil.End();
    objectUtil.End();
}
void TDrawer::DrawControlByRightHand(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TEnum::TGameKey aGameKey)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize NewSize = TSize(X_WIDTH, Y_HEIGHT);
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    //
    TRect oLeftRect;
    TRect oReturnRect;
    TRect oRightRect;
    switch (aGameKey)
    {
        case TEnum::EKeyLeft:
        {
            oLeftRect = iTouchLeftDownRect;
            oReturnRect = iTouchCenterInnerRect;
            //右键头需要通过反转获得
            oRightRect = iTouchLeftRect;
            break;
        }
        case TEnum::EKeyPause:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerDownRect;
            oRightRect = iTouchLeftRect;
            break;
        }
        case TEnum::EKeyRight:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerRect;
            oRightRect = iTouchLeftDownRect;
            break;
        }
        case TEnum::EKeyNone:
        {
            oLeftRect = iTouchLeftRect;
            oReturnRect = iTouchCenterInnerRect;
            oRightRect = iTouchLeftRect;
            break;
        }
        default:
        {
            return;
        }
    }

    //中间色
    R8G8B8 oCenterColor = CENTER_COLOR;
    //
    for (TInt j = 0; j < NewSize.iHeight; j++)
    {
        TInt iCounts;
        addr22 = addr2 + (Y_AXIS_MAX_LIMIT + 1 + j) * desSize.iWidth;
        //重复暂停键中间部分
        addr11 = addr1 + (oReturnRect.iTl.iY + j) * srcSize.iWidth + oReturnRect.iTl.iX;
        iCounts = oReturnRect.iBr.iX - oReturnRect.iTl.iX + 1;
        for (TInt i = 0; i < X_CENTER_WIDTH; i++)
        {
            *addr22 = *addr11;
            addr22++;
        }
        //画中间线
        *addr22 = oCenterColor;
        addr22++;
        //画左键头
        addr11 = addr1 + (oLeftRect.iTl.iY + j) * srcSize.iWidth + oLeftRect.iTl.iX;
        iCounts = oLeftRect.iBr.iX - oLeftRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        //画中间线
        *addr22 = oCenterColor;
        addr22++;
        //画右键头
        addr11 = addr1 + (oRightRect.iTl.iY + j) * srcSize.iWidth + oRightRect.iBr.iX;
        iCounts = oRightRect.iBr.iX - oRightRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11--;
        }
    }
    backUpUtil.End();
    objectUtil.End();
}
void TDrawer::DrawUpLimitStab(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    TSize srcSize = aResourceBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    addr22 = addr2 + (Y_AXIS_MIN_LIMIT - 1) * desSize.iWidth;
    TInt iStabWidth = iUpLimitRect.iBr.iX - iUpLimitRect.iTl.iX + 1;
    TInt iStabHight = iUpLimitRect.iBr.iY - iUpLimitRect.iTl.iY + 1;
    addr11 = addr1 + iUpLimitRect.iTl.iY * srcSize.iWidth + iUpLimitRect.iTl.iX;
    //每画完一行，arrd11要前进的距离
    TInt iWidthSpan = srcSize.iWidth - iStabWidth;
    for (TInt j = 0; j < iStabHight; j++)
    {
        for (TInt i = 0; i < iStabWidth; i++)
        {
            if (addr11->B == 255 && addr11->G == 0)
            {
            }
            else
            {
                *addr22 = *addr11;
            }
            addr22++;
            addr11++;
        }
        addr11 = addr11 + iWidthSpan;
    }
    backUpUtil.End();
    objectUtil.End();
}
void TDrawer::DrawReturnArrow(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TRect aWorldPointRect,
    TRect aBitMapRect)
{
    //根据WorldPointRect大小 和 aBitMapRect的大小 设置新的returnRect的大小
    TPoint center;
    center.SetXY((aWorldPointRect.iBr.iX + aWorldPointRect.iTl.iX) / 2, (aWorldPointRect.iBr.iY
        + aWorldPointRect.iTl.iY) / 2);
    TInt iHalfHigh = (aBitMapRect.iBr.iY - aBitMapRect.iTl.iY) / 2;
    TInt iHalfWidth = (aBitMapRect.iBr.iX - aBitMapRect.iTl.iX) / 2;
    TRect centerRect;
    centerRect.SetRect(center.iX - iHalfWidth, center.iY - iHalfHigh, center.iX + iHalfWidth, center.iY + iHalfHigh);

    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    TSize srcSize = aResourceBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    addr22 = addr2 + (centerRect.iTl.iY - 1) * desSize.iWidth + centerRect.iTl.iX;
    TSize newSize = centerRect.Size();
    addr11 = addr1 + aBitMapRect.iTl.iY * srcSize.iWidth + aBitMapRect.iTl.iX;
    //每画完一行，arrd11要前进的距离
    TInt iWidthSpan = srcSize.iWidth - newSize.iWidth;
    TInt iScreenWidthSpan = desSize.iWidth - newSize.iWidth;
    for (TInt j = 0; j < newSize.iHeight; j++)
    {
        for (TInt i = 0; i < newSize.iWidth; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        addr11 = addr11 + iWidthSpan;
        addr22 = addr22 + iScreenWidthSpan;
    }
    backUpUtil.End();
    objectUtil.End();
}
void TDrawer::DrawLine(CWsBitmap* aBackUpBitmap, TPoint aStartPoint)
{
    TBitmapUtil backUpUtil(aBackUpBitmap);
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8 oCenterColor = SPLIT_LINE_COLOR;
    TInt iCounts = desSize.iWidth * 2;
    for (TInt j = 0; j < 5; j++)
    {
        addr22 = addr2 + (aStartPoint.iY + j * 55) * desSize.iWidth + aStartPoint.iX;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22++ = oCenterColor;
        }
    }
    backUpUtil.End();
}

void TDrawer::DrawLifeValue(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TInt aLifeValue)
{
    if (aLifeValue < 1)
    {
        return;
    }
    //
    TRect srcRect = ipBitMapPosition->GetPosition(TBitMapPosition::ELifeValue, aLifeValue - 1);
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize elementSize;
    elementSize.SetSize(srcRect.iBr.iX - srcRect.iTl.iX + 1, srcRect.iBr.iY - srcRect.iTl.iY + 1);
    R8G8B8* addr22;
    R8G8B8* addr11;
    //TInt iCounts = desSize.iWidth * sourceSize.iWidth;
    TInt iWidthSpanSrc = srcSize.iWidth - elementSize.iWidth;
    TInt iWidthSpanDes = desSize.iWidth - elementSize.iWidth;
    addr22 = addr2 + desSize.iWidth * LIFE_BEGIN_Y + LIFE_BEGIN_X;
    addr11 = addr1 + srcRect.iTl.iY * srcSize.iWidth + srcRect.iTl.iX;
    for (TInt j = 0; j < elementSize.iHeight; j++)
    {
        for (TInt i = 0; i < elementSize.iWidth; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        addr11 = addr11 + iWidthSpanSrc;
        addr22 = addr22 + iWidthSpanDes;
    }
    backUpUtil.End();
    objectUtil.End();
}

void TDrawer::DrawTitleBackground(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    TRect resourceRect = ipBitMapPosition->GetPosition(TBitMapPosition::EGameTitle, 0);
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    TSize sourceSize;
    sourceSize.SetSize(resourceRect.iBr.iX - resourceRect.iTl.iX + 1, resourceRect.iBr.iY - resourceRect.iTl.iY + 1);
    TSize srcSize = aResourceBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    //TInt iCounts = desSize.iWidth * sourceSize.iWidth;
    TInt iWidthSpan = srcSize.iWidth - sourceSize.iWidth;
    addr22 = addr2;
    addr11 = addr1 + resourceRect.iTl.iY * srcSize.iWidth + resourceRect.iTl.iX;
    for (TInt j = 0; j < sourceSize.iHeight; j++)
    {
        for (TInt i = 0; i < desSize.iWidth; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        addr11 = addr11 + iWidthSpan;
    }
    backUpUtil.End();
    objectUtil.End();
}

//根据Y坐标，画背景的一部分
void TDrawer::DrawBackgoundClip(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap, TInt aStartY, TInt aEndY)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize desSize = aBackUpBitmap->SizeInPixels();
    TSize srcSize = aResourceBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    addr22 = addr2+aStartY*desSize.iWidth;
    addr11 = addr1 + aStartY*srcSize.iWidth;
    TInt counts=(aEndY-aStartY+1)*srcSize.iWidth;
    for (TInt i= 0; i < counts; i++)
    {
        *addr22++=*addr11++;
    }
    backUpUtil.End();
    objectUtil.End();
}
