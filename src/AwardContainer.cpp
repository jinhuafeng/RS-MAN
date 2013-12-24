/*
 RS-ManControlView.cpp
 Author   : jinhuafeng

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Application view implementation
 */

// INCLUDE FILES
#include <coemain.h>
#include "AwardContainer.h"
#include "RS_ManAppUi.h"
#include <AknAppUi.h> 
#include <eiklabel.h>  // for example label control
#include <e32keys.h>
#include <akndef.h> //for KEikDynamicLayoutVariantSwitch
#include <AknUtils.h> //for layoututils
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include <E32MATH.h>
#include "CGfxTimer.h"
#include <RS_Man.mbg>
#include  "Macro.h"

#define  HIGHTLIGHT_COLOR   0x00FFFF
#define  NORMAL_COLOR       0x000000
#define  MAX_TICKS          60
void CAwardContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

CAwardContainer::~CAwardContainer()
{

    delete iBackupBitmap;
    delete iGfxTimer;
    delete iBitmapDevice;
    delete iBitmapGc;
    delete iBackGroundSheep;
}

void CAwardContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
}

void CAwardContainer::SizeChanged()
{
    DrawNow();
}

void CAwardContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
{
    CCoeControl::HandlePointerEventL(aPointerEvent);
    // 检查按钮是否都处于正常显示状态
    if (!IsButtonNormalDisplay())
    {
        return;
    }
    switch (aPointerEvent.iType)
    {
        case TPointerEvent::EButton1Down:
        {
            if (iReturn.iWorldPosition.Contains(aPointerEvent.iPosition))
            {
                iReturn.iIsButtonDown = ETrue;
                return;
            }
            break;
        }
        case TPointerEvent::EButton1Up:
        {
            if (iReturn.iIsButtonDown)
            {
                if (iReturn.iWorldPosition.Contains(aPointerEvent.iPosition))
                {
                    iGfxTimer->Pause();
                    iData->iPlayerInfo.WriterPlayerInfo();
                    iData->iGameState = TEnum::EControlMainMenu;
                    iData->ResetDataForNewGame();
                    ReportEventL(MCoeControlObserver::EEventStateChanged);
                    return;
                }
                else
                {
                    iReturn.iIsButtonDown = EFalse;
                }
            }
        }
        default:
        {
            break;
        }
    }
}

void CAwardContainer::ConstructL(const TRect& aRect)
{
    CreateWindowL();
    SetBlank();
    SetRect(aRect);

    //初始化BitMap变量
    iBackupBitmap = new (ELeave) CWsBitmap(iCoeEnv->WsSession());
    iBackupBitmap->Create(Rect().Size(), EColor16M);
    iBitmapDevice = CFbsBitmapDevice::NewL(iBackupBitmap);
    User::LeaveIfError(iBitmapDevice->CreateContext(iBitmapGc));
    //初始化心跳包
    iGfxTimer = new (ELeave) CGfxTimer(*this, NULL);
    iGfxTimer->ConstructL();
    iGfxTimer->StartPulse(KONE_SECOND_IN_MICRO_SECONDS / KFRAMES_PER_SECOND);
    iIsFlagDelete = EFalse;
    iTicks = 0;
    TRAPD(err2, iBackGroundSheep= iEikonEnv->CreateBitmapL(_L("\\resource\\apps\\RS_Man.mbm"),EMbmRs_manSheepbg));
    ActivateL();
}

void CAwardContainer::GfxTimerFiredL(TInt /*aId*/)
{
    if (iTicks < MAX_TICKS)
    {
        iTicks++;
    }
    Quantum();
    DrawView();
    DrawNow();
}

void CAwardContainer::DrawView()
{
    iBitmapGc->Clear();
    iData->iDrawer->DrawWholeBackground(iBackupBitmap, iBackGroundSheep);
    iNavAward.Draw(iBackupBitmap, iData->iResourceMap);
    DrawPlayerList();
    iReturn.Draw(iBackupBitmap, iData->iResourceMap);
}

void CAwardContainer::FocusChanged(TDrawNow aDrawNow)
{
    SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void CAwardContainer::SetPaused(TBool aState)
{
    if (aState)
    {
        iGfxTimer->Pause();
    }
    else
    {
        iGfxTimer->ReStart();
    }
}

TInt CAwardContainer::CountComponentControls() const
{
    return 0;
}

void CAwardContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);

    }
}

CCoeControl* CAwardContainer::ComponentControl(TInt /*aIndex*/) const
{
    return NULL;
}

TKeyResponse CAwardContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{

    return EKeyWasNotConsumed;
}

void CAwardContainer::SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent)
{
}

void CAwardContainer::ClearKeyDown(const TEnum::TGameKey& aKey)
{
}

TBool CAwardContainer::KeyDown(const TEnum::TGameKey& aKey)
{
    return ETrue;
}

void CAwardContainer::UpdateFromKeyStates()
{
}

TBool CAwardContainer::IsKeyPressed()
{
    return EFalse;
}

void CAwardContainer::SetGameState()
{
    //iData->iGameState = TEnum::EControlMainMenu;
    //设置MainMenu下的对象初始状态 
    TRect iLeftTopRect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::HighlightReturnEdge, 0);
    TPoint point;
    point.SetXY(FIRST_MENU_POSITION, FIRST_MENU_HEIGHT);
    point.iY = 610;
    iReturn.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontReturn, 0));
    iReturn.SetStartAndEndPoint(point, TPoint(270, point.iY));
    iReturn.SetHighLightRect(iLeftTopRect, TRect(180, 610 - 27, 359, 610 + 27));
    iReturn.ReSet();

    point.SetXY(180, 60);
    iNavAward.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontAward, 0));
    iNavAward.SetStartAndEndPoint(point, point);
    iNavAward.ReSet();
    iNavAward.UpdateObjectByCenter();
}

void CAwardContainer::Quantum()
{
    iReturn.Quantum();
}
void CAwardContainer::DrawPlayerList()
{
    iBitmapGc ->UseFont(iEikonEnv->NormalFont());
    //D9D919 
    TRgb iFontNormalColor;
    TRgb iFontHighColor;
    iFontNormalColor = NORMAL_COLOR;
    iFontHighColor = HIGHTLIGHT_COLOR;
    //iFontColour.iValue=0xD9D919;
    //iBitmapGc->SetPenColor(0xffff00);
    //iBitmapGc->DrawText(text, TPoint(1, 69));
    TPoint point1;
    TPoint point2;
    TPoint point3;
    point1.SetXY(20, 180);
    point2.SetXY(100, 180);
    point3.SetXY(270, 180);
    if (iTicks % 5 == 0)
    {
        iIsHighLight = !iIsHighLight;
    }
    TBool iIsDisplay;
    iIsDisplay=ETrue;
    for (TInt i = 1; i < AWARD_PLAYER_COUNT; i++)
    {
        TBuf<10> text;
        text.Num(i);
        if (iTicks < MAX_TICKS && iIsHighLight && iIsDisplay && iData->iPlayerInfo.iPlayerList[i]->iIsNewPlayer)
        {
            iIsDisplay=EFalse;
            iBitmapGc->SetPenColor(iFontHighColor);
            iBitmapGc->DrawText(text, point1);
            iBitmapGc->DrawText(*iData->iPlayerInfo.iPlayerList[i]->iName, point2);
            text.Num(iData->iPlayerInfo.iPlayerList[i]->iScore);
            iBitmapGc->DrawText(text, point3);
            point1.iY += 30;
            point2.iY += 30;
            point3.iY += 30;

        }
        else
        {
            if(iTicks >= MAX_TICKS && iData->iPlayerInfo.iPlayerList[i]->iIsNewPlayer)
            {
                iData->iPlayerInfo.iPlayerList[i]->iIsNewPlayer=EFalse;
            }
            iBitmapGc->SetPenColor(iFontNormalColor);
            iBitmapGc->DrawText(text, point1);
            iBitmapGc->DrawText(*iData->iPlayerInfo.iPlayerList[i]->iName, point2);
            text.Num(iData->iPlayerInfo.iPlayerList[i]->iScore);
            iBitmapGc->DrawText(text, point3);
            point1.iY += 30;
            point2.iY += 30;
            point3.iY += 30;
        }
    }
    iBitmapGc->DiscardFont();
}

TBool CAwardContainer::IsButtonNormalDisplay()
{
    //当所有按钮为正常显示状态时返回ETrue;
    if (iReturn.iActionType == TEnum::EButtonNormalDisplay)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}
// End of File
