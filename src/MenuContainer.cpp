/*
 RS-ManControlView.cpp
 Author   : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Application view implementation
 */

// INCLUDE FILES
#include <coemain.h>
#include "MenuContainer.h"
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

void CMenuContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

void CMenuContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
}

void CMenuContainer::SizeChanged()
{
    DrawNow();
}

void CMenuContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
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
            HandleButtonDown(aPointerEvent.iPosition);
            break;
        }
        case TPointerEvent::EButton1Up:
        {
            HandleButtonUp(aPointerEvent.iPosition);
            break;
        }
        default:
        {
            break;
        }
    }
}

CMenuContainer::~CMenuContainer()
{

    delete iBackupBitmap;
    delete iGfxTimer;
    delete iBitmapDevice;
    delete iBitmapGc;
    delete iBackGroundSheep;
}

void CMenuContainer::ConstructL(const TRect& aRect)
{
    CreateWindowL();
    SetBlank();
    SetRect(aRect);
    //CAknAppUiBase::SetOrientationL(EAppUiOrientationPortrait);
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
    TRAPD(err2, iBackGroundSheep= iEikonEnv->CreateBitmapL(_L("\\resource\\apps\\RS_Man.mbm"),EMbmRs_manSheepbg));
    ActivateL();
}

void CMenuContainer::GfxTimerFiredL(TInt /*aId*/)
{
    Quantum();
    DrawView();
    DrawNow();
}

void CMenuContainer::DrawView()
{
    iBitmapGc->Clear();
    iData->iDrawer->DrawWholeBackground(iBackupBitmap, iBackGroundSheep);
    iStart.Draw(iBackupBitmap, iData->iResourceMap);
    iAward.Draw(iBackupBitmap, iData->iResourceMap);
    iOption.Draw(iBackupBitmap, iData->iResourceMap);
    iHelp.Draw(iBackupBitmap, iData->iResourceMap);
    iAbout.Draw(iBackupBitmap, iData->iResourceMap);
    iExit.Draw(iBackupBitmap, iData->iResourceMap);
}

void CMenuContainer::FocusChanged(TDrawNow aDrawNow)
{
    SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void CMenuContainer::SetPaused(TBool aState)
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

TInt CMenuContainer::CountComponentControls() const
{
    return 0;
}

void CMenuContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);

    }
}

CCoeControl* CMenuContainer::ComponentControl(TInt /*aIndex*/) const
{
    return NULL;
}

TKeyResponse CMenuContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{

    return EKeyWasNotConsumed;
}

void CMenuContainer::SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent)
{
}

void CMenuContainer::ClearKeyDown(const TEnum::TGameKey& aKey)
{
}

TBool CMenuContainer::KeyDown(const TEnum::TGameKey& aKey)
{
    return ETrue;
}

void CMenuContainer::UpdateFromKeyStates()
{
}

TBool CMenuContainer::IsKeyPressed()
{
    return EFalse;
}

void CMenuContainer::SetGameState()
{
    //iData->iGameState = TEnum::EControlMainMenu;
    //设置MainMenu下的对象初始状态
    TRect iLeftTopRect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::HighlightEdge, 0);
    TPoint point;
    point.SetXY(FIRST_MENU_POSITION, FIRST_MENU_HEIGHT);
    //1
    iStart.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontStart, 0));
    iStart.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iStart.ReSet();
    iStart.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
    //2
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iAward.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontAward, 0));
    iAward.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iAward.ReSet();
    iAward.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
    //3
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iOption.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontOption, 0));
    iOption.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iOption.ReSet();
    iOption.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
    //4
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iHelp.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontHelp, 0));
    iHelp.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iHelp.ReSet();
    iHelp.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
    //5
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iAbout.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontAbout, 0));
    iAbout.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iAbout.ReSet();
    iAbout.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
    //6
    point.iX += MENU_WIGTH_SPAN;
    point.iY = 610;
    iLeftTopRect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::HighlightReturnEdge, 0);
    iExit.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontExit, 0));
    iExit.SetStartAndEndPoint(point, TPoint(270, point.iY));
    iExit.ReSet();
    iExit.SetHighLightRect(iLeftTopRect, TRect(180, 610 - 27, 359, 610 + 27));

}

void CMenuContainer::Quantum()
{
    iStart.Quantum();
    iAward.Quantum();
    iOption.Quantum();
    iHelp.Quantum();
    iAbout.Quantum();
    iExit.Quantum();
}

TBool CMenuContainer::IsButtonNormalDisplay()
{
    //当所有按钮为正常显示状态时返回ETrue;
    if (iStart.iActionType == TEnum::EButtonNormalDisplay && iAward.iActionType == TEnum::EButtonNormalDisplay
        && iOption.iActionType == TEnum::EButtonNormalDisplay && iHelp.iActionType == TEnum::EButtonNormalDisplay
        && iExit.iActionType == TEnum::EButtonNormalDisplay && iAbout.iActionType == TEnum::EButtonNormalDisplay)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}

void CMenuContainer::HandleButtonDown(TPoint aPoint)
{
    iStart.iIsButtonDown = EFalse;
    iAward.iIsButtonDown = EFalse;
    iOption.iIsButtonDown = EFalse;
    iHelp.iIsButtonDown = EFalse;
    iAbout.iIsButtonDown = EFalse;
    iExit.iIsButtonDown = EFalse;
    if (iStart.iWorldPosition.Contains(aPoint))
    {
        iStart.iIsButtonDown = ETrue;
        return;
    }
    if (iAward.iWorldPosition.Contains(aPoint))
    {
        iAward.iIsButtonDown = ETrue;
        return;
    }
    if (iOption.iWorldPosition.Contains(aPoint))
    {
        iOption.iIsButtonDown = ETrue;
        return;
    }
    if (iHelp.iWorldPosition.Contains(aPoint))
    {
        iHelp.iIsButtonDown = ETrue;
        return;
    }
    if (iAbout.iWorldPosition.Contains(aPoint))
    {
        iAbout.iIsButtonDown = ETrue;
        return;
    }
    if (iExit.iWorldPosition.Contains(aPoint))
    {
        iExit.iIsButtonDown = ETrue;
        return;
    }
}

void CMenuContainer::HandleButtonUp(TPoint aPoint)
{
    //只有当抬起时所在的按钮正是处于ButtonDown的情况时，才能触发相应的事件
    if (iStart.iIsButtonDown)
    {
        if (iStart.iWorldPosition.Contains(aPoint))
        {
            iGfxTimer->Pause();
            iData->iGameState = TEnum::EWaitingStart;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    //
    if (iAward.iIsButtonDown)
    {
        if (iAward.iWorldPosition.Contains(aPoint))
        {
            iGfxTimer->Pause();
            iData->iPreviousState = TEnum::EControlMainMenu;
            iData->iGameState = TEnum::EControlAward;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iOption.iIsButtonDown)
    {
        if (iOption.iWorldPosition.Contains(aPoint))
        {
            iGfxTimer->Pause();
            iData->iPreviousState = TEnum::EControlMainMenu;
            iData->iGameState = TEnum::EControlOption;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iHelp.iIsButtonDown)
    {
        if (iHelp.iWorldPosition.Contains(aPoint))
        {
            iGfxTimer->Pause();
            iData->iPreviousState = TEnum::EControlMainMenu;
            iData->iGameState = TEnum::EControlHelp;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iAbout.iIsButtonDown)
    {
        if (iAbout.iWorldPosition.Contains(aPoint))
        {
            iGfxTimer->Pause();
            iData->iPreviousState = TEnum::EControlMainMenu;
            iData->iGameState = TEnum::EControlAbout;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iExit.iIsButtonDown)
    {
        if (iExit.iWorldPosition.Contains(aPoint))
        {
            iGfxTimer->Pause();
            iData->iGameState = TEnum::EControlExit;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    iStart.iIsButtonDown = EFalse;
    iAward.iIsButtonDown = EFalse;
    iOption.iIsButtonDown = EFalse;
    iHelp.iIsButtonDown = EFalse;
    iAbout.iIsButtonDown=EFalse;
    iExit.iIsButtonDown = EFalse;
}
// End of File


