/*
 * PausedContainer.cpp
 *
 *  Created on: 2010-9-8
 *      Author: jinhuafeng
 */

#include <coemain.h>
#include "PausedContainer.h"
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

void CPausedContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

CPausedContainer::~CPausedContainer()
{

    delete iBackupBitmap;
    delete iGfxTimer;
    delete iBitmapDevice;
    delete iBitmapGc;
    delete iBackGroundSheep;
    //delete iResourceControl;
    //delete ipBitMapPosition;
    // No implementation required
}

void CPausedContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
}

void CPausedContainer::SizeChanged()
{
    DrawNow();
}

void CPausedContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
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

void CPausedContainer::ConstructL(const TRect& aRect)
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
    TRAPD(err2, iBackGroundSheep= iEikonEnv->CreateBitmapL(_L("\\resource\\apps\\RS_Man.mbm"),EMbmRs_manSheepbg));
    ActivateL();
}

void CPausedContainer::GfxTimerFiredL(TInt /*aId*/)
{
    Quantum();
    DrawView();
    DrawNow();
}

void CPausedContainer::DrawView()
{
    iBitmapGc->Clear();
    iData->iDrawer->DrawWholeBackground(iBackupBitmap, iBackGroundSheep);
    iResume.Draw(iBackupBitmap, iData->iResourceMap);
    iNewGame.Draw(iBackupBitmap, iData->iResourceMap);
    iOption.Draw(iBackupBitmap, iData->iResourceMap);
    iHelp.Draw(iBackupBitmap, iData->iResourceMap);
    iReturn.Draw(iBackupBitmap, iData->iResourceMap);
}

void CPausedContainer::FocusChanged(TDrawNow aDrawNow)
{
    SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void CPausedContainer::SetPaused(TBool aState)
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

TInt CPausedContainer::CountComponentControls() const
{
    return 0;
}

void CPausedContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);

    }
}

CCoeControl* CPausedContainer::ComponentControl(TInt /*aIndex*/) const
{
    return NULL;
}

TKeyResponse CPausedContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{

    return EKeyWasNotConsumed;
}

void CPausedContainer::SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent)
{
}

void CPausedContainer::ClearKeyDown(const TEnum::TGameKey& aKey)
{
}

TBool CPausedContainer::KeyDown(const TEnum::TGameKey& aKey)
{
    return ETrue;
}

void CPausedContainer::UpdateFromKeyStates()
{
}

TBool CPausedContainer::IsKeyPressed()
{
    return EFalse;
}

void CPausedContainer::SetGameState()
{
    //iData->iGameState = TEnum::EControlMainMenu;
    //设置MainMenu下的对象初始状态
    TRect iLeftTopRect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::HighlightEdge, 0);
    TPoint point;
    point.SetXY(FIRST_MENU_POSITION, FIRST_MENU_HEIGHT);
    //1
    iResume.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontResume, 0));
    iResume.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iResume.ReSet();
    iResume.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
    //2
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iNewGame.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontNewGame, 0));
    iNewGame.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iNewGame.ReSet();
    iNewGame.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));
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
    iReturn.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontMainMenu, 0));
    iReturn.SetStartAndEndPoint(point, TPoint(180, point.iY));
    iReturn.ReSet();
    iReturn.SetHighLightRect(iLeftTopRect, TRect(0, point.iY - 27, SCREEN_WIDTH - 1, point.iY + 27));

}

void CPausedContainer::Quantum()
{
    iResume.Quantum();
    iNewGame.Quantum();
    iOption.Quantum();
    iHelp.Quantum();
    iReturn.Quantum();
}

TBool CPausedContainer::IsButtonNormalDisplay()
{
    //当所有按钮为正常显示状态时返回ETrue;
    if (iResume.iActionType == TEnum::EButtonNormalDisplay && iNewGame.iActionType == TEnum::EButtonNormalDisplay
        && iOption.iActionType == TEnum::EButtonNormalDisplay && iHelp.iActionType == TEnum::EButtonNormalDisplay
        && iReturn.iActionType == TEnum::EButtonNormalDisplay)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}

void CPausedContainer::HandleButtonDown(TPoint aPoint)
{
    iResume.iIsButtonDown = EFalse;
    iNewGame.iIsButtonDown = EFalse;
    iOption.iIsButtonDown = EFalse;
    iHelp.iIsButtonDown = EFalse;
    iReturn.iIsButtonDown = EFalse;
    if (iResume.iWorldPosition.Contains(aPoint))
    {
        iResume.iIsButtonDown = ETrue;
        return;
    }
    if (iNewGame.iWorldPosition.Contains(aPoint))
    {
        iNewGame.iIsButtonDown = ETrue;
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
    if (iReturn.iWorldPosition.Contains(aPoint))
    {
        iReturn.iIsButtonDown = ETrue;
        return;
    }
}

void CPausedContainer::HandleButtonUp(TPoint aPoint)
{
    //只有当抬起时所在的按钮正是处于ButtonDown的情况时，才能触发相应的事件
    if (iResume.iIsButtonDown)
    {
        if (iResume.iWorldPosition.Contains(aPoint))
        {
            iData->iGameState = TEnum::EPlaying;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    //
    if (iNewGame.iIsButtonDown)
    {
        if (iNewGame.iWorldPosition.Contains(aPoint))
        {
            iData->iGameState = TEnum::EWaitingStart;
            //iData数据重置
            iData->ResetDataForNewGame();
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iOption.iIsButtonDown)
    {
        if (iOption.iWorldPosition.Contains(aPoint))
        {
            iData->iPreviousState = TEnum::EControlPaused;
            iData->iGameState = TEnum::EControlOption;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iHelp.iIsButtonDown)
    {
        if (iHelp.iWorldPosition.Contains(aPoint))
        {
            iData->iPreviousState = TEnum::EControlPaused;
            iData->iGameState = TEnum::EControlHelp;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iReturn.iIsButtonDown)
    {
        if (iReturn.iWorldPosition.Contains(aPoint))
        {
            iData->iGameState = TEnum::EControlMainMenu;
            //返回主界面 意味着放弃当前Man的所有信息
            //iData数据重置
            iData->ResetDataForNewGame();
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    iResume.iIsButtonDown = EFalse;
    iNewGame.iIsButtonDown = EFalse;
    iOption.iIsButtonDown = EFalse;
    iHelp.iIsButtonDown = EFalse;
    iReturn.iIsButtonDown = EFalse;
}

// End of File
