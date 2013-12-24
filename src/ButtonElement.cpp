/*
 * ButtonElement.cpp
 *
 *  Created on: 2010-8-29
 *      Author: panda
 */

#include "ButtonElement.h"

#include <e32std.h>
#include <e32base.h>
#include <e32math.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include "Macro.h"
#include "WorldObject.h"

#define X_WIDTH  360
#define Y_HEIGHT  55

void TButtonElement::Quantum()
{
    switch (iActionType)
    {
        case TEnum::EButtonEnterPosition:
        {
            iCenter.iX += iDetalX;
            if (iDetalX < 0)
            {
                //目前在向左,iCenter在X轴最多偏离中心40
                if (iCenter.iX < iEndPoint.iX - MENU_LEFT_MAX_OFFSET)
                {
                    iCenter.iX = iEndPoint.iX - MENU_LEFT_MAX_OFFSET;
                    iDetalX = MENU_OPTION_VELOCITY;
                }
            }
            else
            {
                if (IsEnterPositionFinish())
                {
                    iActionType = TEnum::EButtonNormalDisplay;
                    iCenter = iEndPoint;
                }
            }
            UpdateObjectByCenter();
            break;
        }
        case TEnum::EButtonNormalDisplay:
        {
            break;
        }
    }
}

void TButtonElement::Draw(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    if (!iIsNeedDraw)
    {
        return;
    }
    if(iIsButtonDown && iIsNeedHighLight)
    {
        DrawHighLight(aBackUpBitmap,aResourceBitmap);
    }
    //
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize NewSize = TSize(iDrawableBitMapRect.iBr.iX - iDrawableBitMapRect.iTl.iX,
        iDrawableBitMapRect.iBr.iY - iDrawableBitMapRect.iTl.iY);
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize desSize = aBackUpBitmap->SizeInPixels();

    R8G8B8* addr22;
    R8G8B8* addr11;

    for (TInt32 j = 0; j < NewSize.iHeight + 1; j++)
    {
        addr22 = addr2 + (iWorldPosition.iTl.iY + j) * desSize.iWidth + iWorldPosition.iTl.iX;
        addr11 = addr1 + (j + iDrawableBitMapRect.iTl.iY) * srcSize.iWidth
            + iDrawableBitMapRect.iTl.iX;
        for (TInt32 i = 0; i < NewSize.iWidth + 1; i++)
        {
            if (addr11->B == 255 && addr11->G == 0 && addr11->R == 0)
            {
            }
            else
            {
                *addr22 = *addr11;
            }
            addr22++;
            addr11++;
        }
    }
    backUpUtil.End();
    objectUtil.End();
}

TBool TButtonElement::IsEnterPositionFinish()
{
    if (iDetalX > 0 && iCenter.iX >= iEndPoint.iX)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}

TBool TButtonElement::IsButtonLeaveFinish()
{
    if (!iIsNeedDraw)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}
//
void TButtonElement::ReSet()
{
    iCenter.SetXY(iStartPoint.iX, iStartPoint.iY);
    iDetalX = MENU_OPTION_VELOCITY * (-1);
    iActionType = TEnum::EButtonEnterPosition;
    iTicks = 0;
    iIsNeedDraw = EFalse;
    iIsNeedHighLight=ETrue;
    iIsButtonDown = EFalse;
    iHalfWidth = (iBitMapRect.iBr.iX - iBitMapRect.iTl.iX) / 2;
    iHalfHeight = (iBitMapRect.iBr.iY - iBitMapRect.iTl.iY) / 2;
}

void TButtonElement::SetStartAndEndPoint(TPoint aStartPoint, TPoint aEndPoint)
{
    iStartPoint = aStartPoint;
    iEndPoint = aEndPoint;
}
void TButtonElement::SetBitMapRect(TRect aBitMapRect)
{
    iBitMapRect = aBitMapRect;
}

void TButtonElement::UpdateObjectByCenter()
{
    iWorldPosition.SetRect(iCenter.iX - iHalfWidth, iCenter.iY - iHalfHeight, iCenter.iX
        + iHalfWidth, iCenter.iY + iHalfHeight);
    iDrawableBitMapRect = iBitMapRect;
    //
    iIsNeedDraw = ETrue;
    if (iWorldPosition.iBr.iX > SCREEN_WIDTH - 1)
    {
        if (iWorldPosition.iTl.iX > SCREEN_WIDTH - 1)
        {
            //全部不显示
            iIsNeedDraw = EFalse;
            return;
        }
        //部分显示
        TInt offset = iWorldPosition.iBr.iX - SCREEN_WIDTH + 1;
        iWorldPosition.iBr.iX = SCREEN_WIDTH - 1;
        iDrawableBitMapRect.iBr.iX -= offset;
    }
}

void TButtonElement::SetHighLightRect(TRect aLeftTopRect, TRect aRect)
{
    iHighLightRect = aRect;
    iHighLightLeftTopRect = aLeftTopRect;
}

void TButtonElement::DrawHighLight(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    //
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
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
    TRect oLeftRect=iHighLightLeftTopRect;
    TRect oRightRect=iHighLightLeftTopRect;
    
    //
    for (TInt j = 0; j < NewSize.iHeight; j++)
    {
        //画左边
        addr22 = addr2 + (iHighLightRect.iTl.iY + 1 + j) * desSize.iWidth+iHighLightRect.iTl.iX;
        addr11 = addr1 + (oLeftRect.iTl.iY + j) * srcSize.iWidth + oLeftRect.iTl.iX;
        TInt iCounts = oLeftRect.iBr.iX - oLeftRect.iTl.iX + 1;
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
            addr11++;
        }
        
        //重复中间部分
        addr11--;
        //addr11 = addr1 + (oCenterRect.iTl.iY + j) * srcSize.iWidth + oCenterRect.iTl.iX;
        iCounts = iHighLightRect.iBr.iX-iHighLightRect.iTl.iX+1-((oLeftRect.iBr.iX-oLeftRect.iTl.iX+1)*2);
        for (TInt i = 0; i < iCounts; i++)
        {
            *addr22 = *addr11;
            addr22++;
        }
        //画右边
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
