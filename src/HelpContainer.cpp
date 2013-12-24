/*
 HelpContainer.cpp
 Created on: 2010-9-8
 Author   : jinhuafeng
 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Application view implementation
 */

// INCLUDE FILES
#include <coemain.h>
#include "HelpContainer.h"
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

void CHelpContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

CHelpContainer::~CHelpContainer()
{

    delete iBackupBitmap;
    delete iGfxTimer;
    delete iBitmapDevice;
    delete iBitmapGc;
    delete iBackGroundSheep;
    /*
     if (iHelpText)
     {
     delete iHelpText;
     }
     if (iHelpTextArray)
     {
     delete iHelpTextArray;
     }
     */
}

void CHelpContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
}

void CHelpContainer::SizeChanged()
{
    DrawNow();
}

void CHelpContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
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
            //return;
            if (iReturn.iWorldPosition.Contains(aPointerEvent.iPosition))
            {
                iReturn.iIsButtonDown = ETrue;
                return;
            }
            if (iDragRect.Contains(aPointerEvent.iPosition))
            {
                iReturn.iIsButtonDown = EFalse;
                iDragPriorPoint = aPointerEvent.iPosition;
                if (!iIsDrag)
                {
                    iIsDrag = ETrue;
                }
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
                    iData->iGameState = iData->iPreviousState;
                    ReportEventL(MCoeControlObserver::EEventStateChanged);
                    return;
                }
                else
                {
                    iReturn.iIsButtonDown = EFalse;
                }
            }
            if(iIsDrag)
            {
                iIsDrag=EFalse;
            }
            break;
        }
        case TPointerEvent::EDrag:
        {
            if (iIsDrag && iDragRect.Contains(aPointerEvent.iPosition))
            {
                TInt distance= aPointerEvent.iPosition.iY-iDragPriorPoint.iY;
                iDragPriorPoint=aPointerEvent.iPosition;
                if(distance>0)
                {
                    iTextDisplayer.DescStartIndex(distance);
                }
                else
                {
                    iTextDisplayer.AddStartIndex(distance*(-1));
                }
            }
            else
            {
                iIsDrag=EFalse;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void CHelpContainer::ConstructL(const TRect& aRect)
{
    CreateWindowL();
    SetBlank();
    SetRect(aRect);

    //初始化BitMap变量
    iBackupBitmap = new (ELeave) CWsBitmap(iCoeEnv->WsSession());
    iBackupBitmap->Create(Rect().Size(), EColor16M);
    iBitmapDevice = CFbsBitmapDevice::NewL(iBackupBitmap);
    User::LeaveIfError(iBitmapDevice->CreateContext(iBitmapGc));
    InitHelpText();
    //启动拖拽
    EnableDragEvents();
    iIsDrag = EFalse;
    iDragRect.SetRect(0, TEXT_DISPLAY_MIN_Y, 359, TEXT_DISPLAY_MAX_Y);
    //初始化心跳包
    iGfxTimer = new (ELeave) CGfxTimer(*this, NULL);
    iGfxTimer->ConstructL();
    iGfxTimer->StartPulse(KONE_SECOND_IN_MICRO_SECONDS / KFRAMES_PER_SECOND);
    iIsFlagDelete = EFalse;
    TRAPD(err2, iBackGroundSheep= iEikonEnv->CreateBitmapL(_L("\\resource\\apps\\RS_Man.mbm"),EMbmRs_manSheepbg));
    ActivateL();

}

void CHelpContainer::GfxTimerFiredL(TInt /*aId*/)
{
    //在所以button都显示正常后，这心跳包可以暂停

    Quantum();
    DrawView();
    DrawNow();
}

void CHelpContainer::DrawView()
{
    //iBitmapGc->Clear();
    //iData->iDrawer->DrawWholeBackground(iBackupBitmap, iBackGroundSheep);
    iData->iDrawer->DrawBackgoundClip(iBackupBitmap, iBackGroundSheep,TEXT_DISPLAY_MIN_Y,TEXT_DISPLAY_MAX_Y);
    DrawHelpText();
    iData->iDrawer->DrawBackgoundClip(iBackupBitmap, iBackGroundSheep,0,TEXT_DISPLAY_MIN_Y-1);
    iData->iDrawer->DrawBackgoundClip(iBackupBitmap, iBackGroundSheep,TEXT_DISPLAY_MAX_Y+1,SCREEN_HEIGHT-1);
    iNavHelp.Draw(iBackupBitmap, iData->iResourceMap);
    iReturn.Draw(iBackupBitmap, iData->iResourceMap);
}

void CHelpContainer::FocusChanged(TDrawNow aDrawNow)
{
    SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void CHelpContainer::SetPaused(TBool aState)
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

TInt CHelpContainer::CountComponentControls() const
{
    return 0;
}

void CHelpContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);

    }
}

CCoeControl* CHelpContainer::ComponentControl(TInt /*aIndex*/) const
{
    return NULL;
}

TKeyResponse CHelpContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{

    return EKeyWasNotConsumed;
}

void CHelpContainer::SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent)
{
}

void CHelpContainer::ClearKeyDown(const TEnum::TGameKey& aKey)
{
}

TBool CHelpContainer::KeyDown(const TEnum::TGameKey& aKey)
{
    return ETrue;
}

void CHelpContainer::UpdateFromKeyStates()
{
}

TBool CHelpContainer::IsKeyPressed()
{
    return EFalse;
}

void CHelpContainer::SetGameState()
{
    TRect iLeftTopRect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::HighlightReturnEdge, 0);
    TPoint point;
    point.SetXY(FIRST_MENU_POSITION, FIRST_MENU_HEIGHT);
    point.iY = 610;
    iReturn.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontReturn, 0));
    iReturn.SetStartAndEndPoint(point, TPoint(270, point.iY));
    iReturn.SetHighLightRect(iLeftTopRect, TRect(180, 610 - 27, 356, 610 + 27));
    iReturn.ReSet();
    point.SetXY(180, 60);
    iNavHelp.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontHelp, 0));
    iNavHelp.SetStartAndEndPoint(point, point);
    iNavHelp.ReSet();
    iNavHelp.UpdateObjectByCenter();
}

void CHelpContainer::Quantum()
{
    iReturn.Quantum();
}

TBool CHelpContainer::IsButtonNormalDisplay()
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

void CHelpContainer::InitHelpText()
{

    iTextDisplayer.ConstructL(iEikonEnv->DenseFont());
    //text
    _LIT(KHelpText,"Tip: You can drag this screen to read all. Welcome to RS-Man space. Nobody can keep the man still alive in the 100th floor.So... are you the first one?\n\nHow to play?\n");
    _LIT(KHelpText1,"In the game, you have to response quickly to survive longer. \nAt the beginning,");
    _LIT(KHelpText2,"The man has three diamonds of life value which will drop when the man collides with the stab board.If the diamonds are exhausted or the man falls onto nothing, the man will die. In the end, your greatest opportunity is yourself! So just enjoy yourself!");
    //_LIT(KHelpText3,"The IMan will be dead directly. \nYou can easily to control this game, enjoy yourself. Remember your greatest opponent is yourself !");
    _LIT(KHelpText4,"\n\nQuestion\nQuestion1: perhaps vibration does not work. \nThe vibration does not work if you close the 'Touch screen vibration' option in your phone settings. So if you need vibration,please  check your phone settings first.");
    _LIT(KHelpText5,"\nQuestion2: occasionally, the arrow keys do not work when clicking.\nAs your phone may not support multi-touch, it does not work if you press more than one key at the same time.So playing the game with only one finger is the best way.\n \nEnd");
    iTextDisplayer.iBufText->Append(KHelpText);
    iTextDisplayer.iBufText->Append(KHelpText1);
    iTextDisplayer.iBufText->Append(KHelpText2);
    //iTextDisplayer.iBufText->Append(KHelpText3);
    iTextDisplayer.iBufText->Append(KHelpText4);
    iTextDisplayer.iBufText->Append(KHelpText5);
    //iTextDisplayer.iBufText->Append(KHelpText3);
    iTextDisplayer.FillArrayText();
    //iTextDisplayer.FillArrayLength();
}

void CHelpContainer::DrawHelpText()
{
    iTextDisplayer.DrawArrayText(iBitmapGc);
    /*
     if (!iHelpTextArray)
     {
     return;
     }
     TPoint point(0, 160);
     iBitmapGc ->UseFont(iEikonEnv->DenseFont());
     for (TInt i = 0; i < iHelpTextArray->Count(); i++)
     {
     iBitmapGc->DrawText(iHelpTextArray->At(i), point);
     point.iY += 30;
     }
     */

}

