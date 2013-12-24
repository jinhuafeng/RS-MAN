/*
 * WorldObject.cpp
 *
 *  Created on: 2010-6-29
 *      Author: Administrator
 */
#include "WorldObject.h"

#include <e32std.h>
#include <e32base.h>
#include <e32math.h>
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include "Macro.h"

//#define X_AXIS_MIN     65
//#define X_AXIS_SPAN   230

//#define SCROLL_SPEED       4
//#define SCROLL_SPEED_SLOW  2
//#define Y_AXIS_MAX_LIMIT   530
//#define Y_AXIS_MIN_LIMIT   70

#define FULL_LIFE_VALUE  6
#define UNIT_LIFE_VALUE  2
#define MARBLE_FRAME_COUNTS  6
#define CONVEY_FRAME_COUNTS  4
#define SPRING_FRAME_COUNTS  7
#define TICKS_FREQUENCY 2

//������Boards��Man��Ҫ��д�������
void TWorldObject::Quantum(TInt aVelocity)
{
    iCenter.iY -= aVelocity;
    FrameChange();
    iYOld = iYNew;
    CalcDrawableRect();
    iYNew = iWorldPosition.iTl.iY;
}

//
//��ʼ���ö���ʱʹ��
void TWorldObject::SetWorldCenter(TPoint aPoint)
{
    iCenter.SetXY(aPoint.iX, aPoint.iY);
}

//������λͼ�Ĵ�Сȷ��������Ļ��λ��
void TWorldObject::UpdateWorldPosition()
{
    TInt offsetX = (iDrawableBitMapRect.iBr.iX - iDrawableBitMapRect.iTl.iX) / 2;
    TInt offsetY = (iDrawableBitMapRect.iBr.iY - iDrawableBitMapRect.iTl.iY) / 2;
    iWorldPosition.SetRect(iCenter.iX - offsetX, iCenter.iY - offsetY, iCenter.iX + offsetX, iCenter.iY + offsetY);
}

//������ �� ������ʱʹ��
void TWorldObject::Reset()
{
    iCurrentFrame = 0;
    iIsActive = EFalse;
    iCenter.iX = (Math::Random() % X_AXIS_SPAN) + X_AXIS_MIN;
    iWorldPosition.SetRect(0, 0, 0, 0);
    iYOld = iYNew = Y_AXIS_REPLACE_POSITION + CENTER_SPAN_AXIS_Y;
}

//����֡�ı�
void TWorldObject::FrameChange()
{
    return;
}
//�ú���ֻ����Quantum(),GetBitMapRect()�������ù�����ܱ�����
//��������µ�λ�ÿ��Ի�������Ļ�ϵĲ��� 
//�ú����п��ܻ�ı�iWorldPosition ��iDrawableBitMapRect��ֵ
void TWorldObject::CalcDrawableRect()
{
    //�����iWorldPoint �� iDrawableBitMapRect
    GetBitMapRect();
    UpdateWorldPosition();
    iIsNeedDraw = ETrue;
    if (iWorldPosition.iTl.iY < Y_AXIS_MIN_LIMIT)
    {
        if (iWorldPosition.iBr.iY < Y_AXIS_MIN_LIMIT)
        {
            //��ʱ��ʾ�ö����λ���Ѿ���������Ҫ���Ƶķ�Χ
            iIsNeedDraw = EFalse;
            //iWorldPosition.SetRect(0, 0, 0, 0);
            //iDrawableBitMapRect.SetRect(0, 0, 0, 0);
            return;
        }
        TInt offset = Y_AXIS_MIN_LIMIT - iWorldPosition.iTl.iY;
        iDrawableBitMapRect.iTl.iY += offset;
        iWorldPosition.iTl.iY += offset;
        return;
    }
    if (iWorldPosition.iBr.iY > Y_AXIS_MAX_LIMIT)
    {
        if (iWorldPosition.iTl.iY > Y_AXIS_MAX_LIMIT)
        {
            //��ʱ����ռ������ ��û�е������ʾ������
            //������ʾ���� ����Ϊ0
            iIsNeedDraw = EFalse;
            //iWorldPosition.SetRect(0, 0, 0, 0);
            //iDrawableBitMapRect.SetRect(0, 0, 0, 0);
            return;
        }
        else
        {
            TInt offset = iWorldPosition.iBr.iY - Y_AXIS_MAX_LIMIT;
            iDrawableBitMapRect.iBr.iY -= offset;
            iWorldPosition.iBr.iY -= offset;
        }
    }
}

void TWorldObject::Draw(CWsBitmap* aBackUpBitmap, CWsBitmap* aResourceBitmap)
{
    //if (iWorldPosition.iBr.iX - iWorldPosition.iTl.iX == 0)
    //{
    //    return;
    //}
    if (!iIsNeedDraw)
    {
        return;
    }
    //
    TBitmapUtil objectUtil(aResourceBitmap);
    TBitmapUtil backUpUtil(aBackUpBitmap);
    //
    objectUtil.Begin(TPoint(0, 0));
    backUpUtil.Begin(TPoint(0, 0));
    R8G8B8* addr1 = (R8G8B8*) aResourceBitmap->DataAddress();// ����
    R8G8B8* addr2 = (R8G8B8*) aBackUpBitmap->DataAddress();// ����
    TSize NewSize = TSize(iDrawableBitMapRect.iBr.iX - iDrawableBitMapRect.iTl.iX+1, iDrawableBitMapRect.iBr.iY
        - iDrawableBitMapRect.iTl.iY+1);
    TSize srcSize = aResourceBitmap->SizeInPixels();
    TSize desSize = aBackUpBitmap->SizeInPixels();

    R8G8B8* addr22;
    R8G8B8* addr11;
    //ÿ������
    TInt objectWidth = iDrawableBitMapRect.iBr.iX - iDrawableBitMapRect.iTl.iX+1;
    TInt iWidthSpan = srcSize.iWidth - objectWidth;
    TInt iScreenWidthSpan = desSize.iWidth - objectWidth;
    addr22 = addr2 + iWorldPosition.iTl.iY* desSize.iWidth + iWorldPosition.iTl.iX;
    addr11 = addr1 + iDrawableBitMapRect.iTl.iY* srcSize.iWidth + iDrawableBitMapRect.iTl.iX;
    for (TInt32 j = 0; j < NewSize.iHeight; j++)
    {
        for (TInt32 i = 0; i < NewSize.iWidth; i++)
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
        addr22 = addr22 + iScreenWidthSpan;
    }
    backUpUtil.End();
    objectUtil.End();
}
TBool TWorldObject::Intersects(TRect aManRect)
{
    return iWorldPosition.Intersects(aManRect);
}

//��ö�������ı��е�����Ļ�ϵ�λ��
TPoint TWorldObject::GetMidPointofTop()
{
    TPoint point;
    point.SetXY(iCenter.iX, iWorldPosition.iTl.iY);
    return point;
}

TWoodBoard::TWoodBoard()
{
    //iCurrentFrame is always 0. 
    iCurrentFrame = 0;
    iBoardName = WoodBoard;
    iIsActive = EFalse;
    //iDeltaY = SCROLL_SPEED;
    iIsUsed = EFalse;
    iWorldPosition.SetRect(0, 0, 0, 0);
}

//��ȡλͼ�ڴ�ͼ�е�λ�� ������λͼ�Ĵ�Сȷ��������Ļ��λ��
TRect TWoodBoard::GetBitMapRect()
{
    iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::WoodBoard, iCurrentFrame);
    return iDrawableBitMapRect;
}

TMarbleBoard::TMarbleBoard()
{
    iCurrentFrame = 0;
    //iFrequency = TICKS_FREQUENCY + 2;
    iFrequency = TICKS_FREQUENCY + 1;
    iFrameCount = MARBLE_FRAME_COUNTS;
    iBoardName = MarbleBoard;
    iIsActive = EFalse;
    //iDeltaY = SCROLL_SPEED;
    iIsUsed = EFalse;
    iWorldPosition.SetRect(0, 0, 0, 0);
}

TRect TMarbleBoard::GetBitMapRect()
{
    iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::MarbleBoard, iCurrentFrame);
    return iDrawableBitMapRect;
}

void TMarbleBoard::Reset()
{
    iCurrentFrame = 0;
    iIsActive = EFalse;
    iCenter.iX = (Math::Random() % X_AXIS_SPAN) + X_AXIS_MIN;
    iWorldPosition.SetRect(0, 0, 0, 0);
    //addition
    iTicks = 0;
    iYOld = iYNew = Y_AXIS_REPLACE_POSITION + CENTER_SPAN_AXIS_Y;
}
void TMarbleBoard::SetActive()
{
    iIsActive = ETrue;
    iCurrentFrame = 0;
    iTicks = 0;
}
void TMarbleBoard::FrameChange()
{
    //���̣��ӵ�һ�������������������� ��ص�һ֡
    if (!iIsActive)
    {
        return;
    }
    iTicks++;
    if (iTicks % iFrequency != 0)
    {
        return;
    }
    if (iCurrentFrame == iFrameCount - 1)
    {
        iIsActive = EFalse;
        iCurrentFrame = 0;
        iTicks = 0;
        return;
    }
    else
    {
        iCurrentFrame++;
    }
}

TConveyBoard::TConveyBoard()
{
    iCurrentFrame = 0;
    //iFrequency = TICKS_FREQUENCY;
    iFrequency = TICKS_FREQUENCY - 1;
    iFrameCount = CONVEY_FRAME_COUNTS;
    iBoardName = ConveyBoard;
    iIsActive = EFalse;
    //iDeltaY = SCROLL_SPEED;
    iIsUsed = EFalse;
    iWorldPosition.SetRect(0, 0, 0, 0);
}

void TConveyBoard::Reset()
{
    iCurrentFrame = 0;
    iIsActive = EFalse;
    iCenter.iX = (Math::Random() % X_AXIS_SPAN) + X_AXIS_MIN;
    iWorldPosition.SetRect(0, 0, 0, 0);
    //addition
    if (Math::Random() % 2 == 1)
    {
        iVelociry = EConveyLeft;
    }
    else
    {
        iVelociry = EConveyRight;
    };
    //
    iTicks = 0;
    iYOld = iYNew = Y_AXIS_REPLACE_POSITION + CENTER_SPAN_AXIS_Y;
}

void TConveyBoard::FrameChange()
{
    //���̣��ӵ�һ�鿪ʼ����ͣ�ĸı�֡
    iTicks++;
    if (iTicks % iFrequency == 0)
    {
        iCurrentFrame = (iCurrentFrame + 1) % iFrameCount;
    }
}
TRect TConveyBoard::GetBitMapRect()
{
    if (iVelociry == TConveyBoard::EConveyRight)
    {
        iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::ConveyBoardRight, iCurrentFrame);
    }
    else
    {
        iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::ConveyBoardLeft, iCurrentFrame);
    }
    return iDrawableBitMapRect;
}

void TConveyBoard::SetVelocity(Velocity aVelocity)
{
    iVelociry = aVelocity;
}

TSpringBoard::TSpringBoard()
{
    iCurrentFrame = SPRING_FRAME_COUNTS - 1;
    iFrameCount = SPRING_FRAME_COUNTS;
    //iFrequency = TICKS_FREQUENCY - 1;
    iFrequency = TICKS_FREQUENCY - 1;
    iBoardName = SpringBoard;
    iIsActive = EFalse;
    //iDeltaY = SCROLL_SPEED;
    iIsUsed = EFalse;
    iWorldPosition.SetRect(0, 0, 0, 0);
}
void TSpringBoard::SetActive()
{
    iCurrentFrame = 4;
    iIsActive = ETrue;
    iTicks = 0;
}
void TSpringBoard::Reset()
{
    //��ʼ״̬�ǵ��Ŀ�
    iCurrentFrame = 4;
    iIsActive = EFalse;
    iCenter.iX = (Math::Random() % X_AXIS_SPAN) + X_AXIS_MIN;
    iWorldPosition.SetRect(0, 0, 0, 0);
    //addition
    iTicks = 0;
    GetBitMapRect();
    //iYOld=
    iStaticHeight = (iDrawableBitMapRect.iBr.iY - iDrawableBitMapRect.iTl.iY) / 2;
    //
    iYOld = iYNew = Y_AXIS_REPLACE_POSITION + CENTER_SPAN_AXIS_Y;
}
void TSpringBoard::FrameChange()
{
    //���̣��ӵ��Ŀ鿪ʼ��һֱ�� ����ٴε�����Ŀ�
    if (!iIsActive)
    {
        return;
    }
    iTicks++;
    if (iTicks % iFrequency != 0)
    {
        return;
    }
    if (iCurrentFrame % SPRING_FRAME_COUNTS == 3)
    {
        iIsActive = EFalse;
        iCurrentFrame = 4;
        iTicks = 0;
        return;
    }
    else
    {
        iCurrentFrame = (iCurrentFrame + 1) % SPRING_FRAME_COUNTS;
    }
}
TRect TSpringBoard::GetBitMapRect()
{
    iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::SpringBoard, iCurrentFrame);
    return iDrawableBitMapRect;
}

void TSpringBoard::UpdateWorldPosition()
{
    TInt offsetX = (iDrawableBitMapRect.iBr.iX - iDrawableBitMapRect.iTl.iX) / 2;
    TInt offsetY = iDrawableBitMapRect.iBr.iY - iDrawableBitMapRect.iTl.iY;
    iWorldPosition.SetRect(iCenter.iX - offsetX, iCenter.iY + iStaticHeight - offsetY, iCenter.iX + offsetX, iCenter.iY
        + iStaticHeight);
}
TStabBoard::TStabBoard()
{
    iCurrentFrame = 0;
    iFrameCount = 1;
    iBoardName = StabBoard;
    iIsActive = EFalse;
    //iDeltaY = SCROLL_SPEED;
    iIsUsed = EFalse;
    iWorldPosition.SetRect(0, 0, 0, 0);
}

TRect TStabBoard::GetBitMapRect()
{
    iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::StabBoard, iCurrentFrame);
    return iDrawableBitMapRect;
}

void TStabBoard::Quantum(TInt aVelocity)
{
    iCenter.iY -= aVelocity;
    //FrameChange();
    iYOld = iYNew;
    CalcDrawableRect();
    iYNew = iCenter.iY;
}
void TStabBoard::Reset()
{
    iCurrentFrame = 0;
    iIsActive = EFalse;
    iCenter.iX = (Math::Random() % X_AXIS_SPAN) + X_AXIS_MIN;
    iWorldPosition.SetRect(0, 0, 0, 0);
    iYOld = iYNew = Y_AXIS_REPLACE_POSITION + CENTER_SPAN_AXIS_Y;
}

TMan::TMan()
{
    iBoardName = Man;
    iIsUsed = ETrue;
    iLifeValue = FULL_LIFE_VALUE;
    //iScore = 0;
    iTicksLife = 0;
    iTicksFrame = 0;
    iIsNeedDraw = ETrue;
}

void TMan::LifeAdd()
{
    if (iLifeValue > 0 && iLifeValue < FULL_LIFE_VALUE)
    {
        iLifeValue += 1;// UNIT_LIFE_VALUE;
    }
}

void TMan::LifeDescend()
{
    if (iLifeValue > 1)
    {
        iLifeValue -= UNIT_LIFE_VALUE;
    }
    else
    {
        iLifeValue = 0;
    }
}
TBool TMan::IsDeath()
{
    if (iLifeValue > 0)
    {
        return EFalse;
    }
    else
    {
        return ETrue;
    }
}
void TMan::SetHurting()
{
    iIsHurting = ETrue;
    iTicksHurting = 0;
    iCurrentFrame = 0;
    LifeDescend();
}

//aPoint Ϊĳ���ռ��������һ���ߵ��е�����
//Ҳ�ǵ�ǰMan�ĵױ��е�
//Reset �����к��� ��������Man�д󲿷ֺ���ǰ����
void TMan::Reset(TPoint aPoint, TInt aScroll)
{
    iManActionState = TEnum::EStand;
    iFrameCount = GetFramesCountByActionState(iManActionState);
    iDeltaX = 0;
    iDeltaY = aScroll * (-1);
    iIsHurting = EFalse;
    iIsUsed = ETrue;
    iCollisionState = TEnum::ECollisionWood;
    iLifeValue = FULL_LIFE_VALUE;
    iCurrentFrame = 0;
    //ÿ��֡����һ��λͼ
    iFrequency = 2;
    iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::Stand, 0);
    iManHalfHeight = (iDrawableBitMapRect.iBr.iY - iDrawableBitMapRect.iTl.iY) / 2;
    iManHalfWidth = (iDrawableBitMapRect.iBr.iX - iDrawableBitMapRect.iTl.iX) / 2;
    iCenter.iX = aPoint.iX;
    iCenter.iY = aPoint.iY - iManHalfHeight;
    iYOld = aPoint.iY;
    iYNew = aPoint.iY;
    //iTicks = 0;
    iTicksFrame = 0;
    iTicksLife = 0;
}
void TMan::SetBitMapPosition(TBitMapPosition* apBitMapPosition)
{
    ipBitMapPosition = apBitMapPosition;
}
void TMan::HandleTicker()
{
    //����TicksHurting
    if (iIsHurting)
    {
        iTicksHurting++;
        if (iTicksHurting % TICKS_SPAN_OF_HURTING == 0)
        {
            iTicksHurting = 0;
            iIsHurting = EFalse;
        }
    }
    //��������ֵ��ԭ���
    if (iLifeValue > 0 && iLifeValue < FULL_LIFE_VALUE)
    {
        iTicksLife++;
        if (iTicksLife % TICKS_LIFE_RECOVERY == 0)
        {
            LifeAdd();
            iTicksLife = 0;
        }
    }
    //����TicksFrame
    iTicksFrame++;
}
TInt TMan::GetFramesCountByActionState(TEnum::TManActionState aManActionState)
{
    if (aManActionState == TEnum::EStand)
    {
        return 1;
    }
    else
    {
        return 4;
    }
}

TRect TMan::GetBitMapRect()
{
    switch (iManActionState)
    {
        case TEnum::ELeft:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::Left, iCurrentFrame);
            break;
        }
        case TEnum::ERight:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::Right, iCurrentFrame);
            break;
        }
        case TEnum::EStand:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::Stand, iCurrentFrame);
            break;
        }
        case TEnum::ELeftJump:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::LeftJump, iCurrentFrame);
            break;
        }
        case TEnum::ERightJump:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::RightJump, iCurrentFrame);
            break;
        }
        case TEnum::EJump:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::Jump, iCurrentFrame);
            break;
        }
        case TEnum::ELeftRed:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::LeftRed, iCurrentFrame);
            break;
        }
        case TEnum::ERightRed:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::RightRed, iCurrentFrame);
            break;
        }
        case TEnum::EStandRed:
        {
            if (iTicksFrame % (iFrequency * 2) == 0)
            {
                iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::Stand, iCurrentFrame);
            }
            else
            {
                iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::StandRed, iCurrentFrame);
            }
            break;
        }
        case TEnum::ELeftJumpRed:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::LeftJumpRed, iCurrentFrame);
            break;
        }
        case TEnum::ERightJumpRed:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::RightJumpRed, iCurrentFrame);
            break;
        }
        case TEnum::EJumpRed:
        {
            iDrawableBitMapRect = ipBitMapPosition->GetPosition(TBitMapPosition::JumpRed, iCurrentFrame);
            break;
        }
    }
    //iDrawableBitMapRect
    //   = ipBitMapPosition->GetPosition(, iCurrentFrame);
    return iDrawableBitMapRect;
}

//������һѭ�������λ�ã�����Man�ĵ�ǰӦ��λ�ã�������iYOld,iYNew��ֵ
void TMan::Quentum()
{
    iYOld = iYNew;
    iCenter.iX += iDeltaX;
    iCenter.iY += iDeltaY;
    if (iCenter.iX - iManHalfWidth < 0)
    {
        iCenter.iX = iManHalfWidth;
    }
    else if (iCenter.iX + iManHalfWidth > 359)
    {
        iCenter.iX = 359 - iManHalfWidth;
    }
    iWorldPosition.SetRect(iCenter.iX - iManHalfWidth, iCenter.iY - iManHalfHeight, iCenter.iX + iManHalfWidth,
        iCenter.iY + iManHalfHeight);
    iYNew = iCenter.iY + iManHalfHeight;
    //����Ticks
    HandleTicker();
}

//iTicks����һ������
//1��ͨ��iFrequency�����������֡�ı仯�ٶ�
//2����״̬ΪEStandRedʱ��iTicks % iFrequency == 0ʱ���ҲŻ���Man�������Ż�����˸Ч��
//3
void TMan::FrameChange()
{
    //iTicks++;
    if (iManActionState == TEnum::EStand || iManActionState == TEnum::EStandRed)
    {
        iCurrentFrame = 0;
    }
    else
    {
        if (iTicksFrame % iFrequency != 0)
        {
            return;
        }
        iCurrentFrame = (iCurrentFrame + 1) % 4;
    }

}
