/*
 * MotionElement.cpp
 *
 *  Created on: 2010-9-15
 *      Author: jinhuafeng
 */
#include "MotionElement.h"

#include <e32std.h>
#include <e32base.h>
#include <e32math.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include "Macro.h"
#include "WorldObject.h"

void TMotionElement::Quantum()
{
    if (iMotionDistance <= iCurrMotionDistance)
    {
        return;
    }
    //
    TInt offset = 0;
    iCurrMotionDistance += iDetal;
    switch (iMotionDirection)
    {
        case EEastToWest:
        {
            if (iCurrMotionDistance > iMotionDistance)
            {
                offset = iDetal - (iCurrMotionDistance - iMotionDistance);
                iNewMapCenter.iX -= offset;
                iOldMapCenter.iX -= offset;
            }
            else
            {
                iNewMapCenter.iX -= iDetal;
                iOldMapCenter.iX -= iDetal;
            }
            break;
        }
        case EWestToEast:
        {
            if (iCurrMotionDistance > iMotionDistance)
            {
                offset = iDetal - (iCurrMotionDistance - iMotionDistance);
                iNewMapCenter.iX += offset;
                iOldMapCenter.iX += offset;
            }
            else
            {
                iNewMapCenter.iX += iDetal;
                iOldMapCenter.iX += iDetal;
            }
            break;
        }
        case ENorthToSouth:
        {
            if (iCurrMotionDistance > iMotionDistance)
            {
                offset = iDetal - (iCurrMotionDistance - iMotionDistance);
                iNewMapCenter.iY += offset;
                iOldMapCenter.iY += offset;
            }
            else
            {
                iNewMapCenter.iY += iDetal;
                iOldMapCenter.iY += iDetal;
            }
            break;
        }
        case ESouthToNorth:
        {
            if (iCurrMotionDistance > iMotionDistance)
            {
                offset = iDetal - (iCurrMotionDistance - iMotionDistance);
                iNewMapCenter.iY -= offset;
                iOldMapCenter.iY -= offset;
            }
            else
            {
                iNewMapCenter.iY -= iDetal;
                iOldMapCenter.iY -= iDetal;
            }
            break;
        }
    }
    CalcDrawableRect();
}

void TMotionElement::SetVisibleArea(TRect aVisibleArea)
{
    iVisibleArea = aVisibleArea;
}
void TMotionElement::SetNewAndOldMapRect(TRect aNewMapRect, TRect aOldMapRect)
{
    iNewBitMapRect=aNewMapRect;
    iOldBitMapRect=aOldMapRect;
    UpdateObjectData();
    UpdateWorldPosition();
}
void TMotionElement::GetBitMapRect()
{
    iNewMapDrawableRect = iNewBitMapRect;
    iOldMapDrawableRect = iOldBitMapRect;
}
void TMotionElement::UpdateWorldPosition()
{
    GetBitMapRect();
    //NewMap
    TInt offsetX = (iNewMapDrawableRect.iBr.iX - iNewMapDrawableRect.iTl.iX) / 2;
    TInt offsetY = (iNewMapDrawableRect.iBr.iY - iNewMapDrawableRect.iTl.iY) / 2;
    iNewMapWorldPosition.SetRect(iNewMapCenter.iX - offsetX, iNewMapCenter.iY - offsetY, iNewMapCenter.iX + offsetX, iNewMapCenter.iY
        + offsetY);
    //OldMap
    offsetX = (iOldMapDrawableRect.iBr.iX - iOldMapDrawableRect.iTl.iX) / 2;
    offsetY = (iOldMapDrawableRect.iBr.iY - iOldMapDrawableRect.iTl.iY) / 2;
    iOldMapWorldPosition.SetRect(iOldMapCenter.iX - offsetX, iOldMapCenter.iY - offsetY, iOldMapCenter.iX + offsetX, iOldMapCenter.iY
        + offsetY);
}
void TMotionElement::Draw(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// 对象
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// 背景
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize desSize = aBackUpBitmap->SizeInPixels();
    R8G8B8* addr22;
    R8G8B8* addr11;
    if (iIsNewMapNeedDraw)
    {
        //Draw New
        TSize NewSize = iNewMapDrawableRect.Size();
        for (TInt32 j = 0; j < NewSize.iHeight; j++)
        {
            addr22 = addr2 + (iNewMapWorldPosition.iTl.iY + j) * desSize.iWidth + iNewMapWorldPosition.iTl.iX;
            addr11 = addr1 + (j + iNewMapDrawableRect.iTl.iY) * srcSize.iWidth + iNewMapDrawableRect.iTl.iX;
            for (TInt32 i = 0; i < NewSize.iWidth; i++)
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
    }
    if (iIsOldMapNeedDraw)
    {
        //Draw Old
        TSize NewSize = iOldMapDrawableRect.Size();
        for (TInt32 j = 0; j < NewSize.iHeight; j++)
        {
            addr22 = addr2 + (iOldMapWorldPosition.iTl.iY + j) * desSize.iWidth + iOldMapWorldPosition.iTl.iX;
            addr11 = addr1 + (j + iOldMapDrawableRect.iTl.iY) * srcSize.iWidth + iOldMapDrawableRect.iTl.iX;
            for (TInt32 i = 0; i < NewSize.iWidth; i++)
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
    }
    backUpUtil.End();
    objectUtil.End();
    //


}

void TMotionElement::UpdateObjectData()
{
    GetBitMapRect();
    iHalfHeight = (iVisibleArea.iBr.iY - iVisibleArea.iTl.iY) / 2;
    iHalfWidth = (iVisibleArea.iBr.iX - iVisibleArea.iTl.iX) / 2;
    TInt newMapHalfHeight = (iNewMapDrawableRect.iBr.iY - iNewMapDrawableRect.iTl.iY) / 2;
    TInt newMapHalfWidth = (iNewMapDrawableRect.iBr.iX - iNewMapDrawableRect.iTl.iX) / 2;
    iOldMapCenter.SetXY(iVisibleArea.iTl.iX + iHalfWidth, iVisibleArea.iTl.iY + iHalfHeight);
    iCurrMotionDistance = 0;
    //
    switch (iMotionDirection)
    {
        case EEastToWest:
        {
            iNewMapCenter.SetXY(iVisibleArea.iBr.iX + newMapHalfWidth+MOTION_EASTWEST_SPAN, iVisibleArea.iTl.iY + iHalfHeight);
            iMotionDistance = newMapHalfWidth + iHalfWidth+MOTION_EASTWEST_SPAN;
            iDetal = MOTION_EASTWEST_RECOVERY;
            break;
        }
        case EWestToEast:
        {
            iNewMapCenter.SetXY(iVisibleArea.iTl.iX - newMapHalfWidth-MOTION_EASTWEST_SPAN, iVisibleArea.iTl.iY + iHalfHeight);
            iMotionDistance = newMapHalfWidth + iHalfWidth+MOTION_EASTWEST_SPAN;
            iDetal = MOTION_EASTWEST_RECOVERY;
            break;
        }
        case ENorthToSouth:
        {
            iNewMapCenter.SetXY(iVisibleArea.iTl.iX + iHalfWidth, iVisibleArea.iTl.iY - newMapHalfHeight-MOTION_SOUTHNORTH_SPAN);
            iMotionDistance = newMapHalfHeight + iHalfHeight+MOTION_SOUTHNORTH_SPAN;
            iDetal = MOTION_SOUTHNORTH_RECONVERY;
            break;
        }
        case ESouthToNorth:
        {
            iNewMapCenter.SetXY(iVisibleArea.iTl.iX + iHalfWidth, iVisibleArea.iBr.iY + newMapHalfHeight+MOTION_SOUTHNORTH_SPAN);
            iMotionDistance = newMapHalfHeight + iHalfHeight+MOTION_SOUTHNORTH_SPAN;
            iDetal = MOTION_SOUTHNORTH_RECONVERY;
            break;
        }
        default:
        {
            break;
        }
    }
}
void TMotionElement::CalcDrawableRect()
{
    UpdateWorldPosition();
    iIsOldMapNeedDraw = ETrue;
    iIsNewMapNeedDraw = ETrue;
    switch (iMotionDirection)
    {
        case EEastToWest:
        case EWestToEast:
        {
            //只需要判断X轴
            //Old
            if (iOldMapWorldPosition.iTl.iX < iVisibleArea.iTl.iX)
            {
                if (iOldMapWorldPosition.iBr.iX < iVisibleArea.iTl.iX)
                {
                    iIsOldMapNeedDraw = EFalse;
                }
                TInt offset = iVisibleArea.iTl.iX - iOldMapWorldPosition.iTl.iX;
                iOldMapDrawableRect.iTl.iX += offset;
                iOldMapWorldPosition.iTl.iX += offset;
            }
            if (iOldMapWorldPosition.iBr.iX > iVisibleArea.iBr.iX)
            {
                if (iOldMapWorldPosition.iTl.iX > iVisibleArea.iBr.iX)
                {
                    iIsOldMapNeedDraw = EFalse;
                }
                else
                {
                    TInt offset = iOldMapWorldPosition.iBr.iX - iVisibleArea.iBr.iX;
                    iOldMapDrawableRect.iBr.iX -= offset;
                    iOldMapWorldPosition.iBr.iX -= offset;
                }
            }
            //New
            if (iNewMapWorldPosition.iTl.iX < iVisibleArea.iTl.iX)
            {
                if (iNewMapWorldPosition.iBr.iX < iVisibleArea.iTl.iX)
                {
                    iIsNewMapNeedDraw = EFalse;
                }
                TInt offset = iVisibleArea.iTl.iX - iNewMapWorldPosition.iTl.iX;
                iNewMapDrawableRect.iTl.iX += offset;
                iNewMapWorldPosition.iTl.iX += offset;
            }
            if (iNewMapWorldPosition.iBr.iX > iVisibleArea.iBr.iX)
            {
                if (iNewMapWorldPosition.iTl.iX > iVisibleArea.iBr.iX)
                {
                    iIsNewMapNeedDraw = EFalse;
                }
                else
                {
                    TInt offset = iNewMapWorldPosition.iBr.iX - iVisibleArea.iBr.iX;
                    iNewMapDrawableRect.iBr.iX -= offset;
                    iNewMapWorldPosition.iBr.iX -= offset;
                }
            }
            break;
        }
        case ENorthToSouth:
        case ESouthToNorth:
        {
            //只需要判断Y轴
            //Old
            if (iOldMapWorldPosition.iTl.iY < iVisibleArea.iTl.iY)
            {
                if (iOldMapWorldPosition.iBr.iY < iVisibleArea.iTl.iY)
                {
                    iIsOldMapNeedDraw = EFalse;
                }
                TInt offset = iVisibleArea.iTl.iY - iOldMapWorldPosition.iTl.iY;
                iOldMapDrawableRect.iTl.iY += offset;
                iOldMapWorldPosition.iTl.iY += offset;
            }
            if (iOldMapWorldPosition.iBr.iY > iVisibleArea.iBr.iY)
            {
                if (iOldMapWorldPosition.iTl.iY > iVisibleArea.iBr.iY)
                {
                    iIsOldMapNeedDraw = EFalse;
                }
                else
                {
                    TInt offset = iOldMapWorldPosition.iBr.iY - iVisibleArea.iBr.iY;
                    iOldMapDrawableRect.iBr.iY -= offset;
                    iOldMapWorldPosition.iBr.iY -= offset;
                }
            }
            //New
            if (iNewMapWorldPosition.iTl.iY < iVisibleArea.iTl.iY)
            {
                if (iNewMapWorldPosition.iBr.iY < iVisibleArea.iTl.iY)
                {
                    iIsNewMapNeedDraw = EFalse;
                }
                TInt offset = iVisibleArea.iTl.iY - iNewMapWorldPosition.iTl.iY;
                iNewMapDrawableRect.iTl.iY += offset;
                iNewMapWorldPosition.iTl.iY += offset;
                return;
            }
            if (iNewMapWorldPosition.iBr.iY > iVisibleArea.iBr.iY)
            {
                if (iNewMapWorldPosition.iTl.iY > iVisibleArea.iBr.iY)
                {
                    iIsNewMapNeedDraw = EFalse;
                }
                else
                {
                    TInt offset = iNewMapWorldPosition.iBr.iY - iVisibleArea.iBr.iY;
                    iNewMapDrawableRect.iBr.iY -= offset;
                    iNewMapWorldPosition.iBr.iY -= offset;
                }
            }
            break;
        }
    }
}

