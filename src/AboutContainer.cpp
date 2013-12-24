/*
 AboutContainer.cpp
 Created on: 2010-9-26
 Author   : jinhuafeng
 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 */

#include <coemain.h>
#include "AboutContainer.h"
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

void CAboutContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

CAboutContainer::~CAboutContainer()
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

void CAboutContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
}

void CAboutContainer::SizeChanged()
{
    DrawNow();
}

void CAboutContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
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
            if (iIsDrag)
            {
                iIsDrag = EFalse;
            }
            break;
        }
        case TPointerEvent::EDrag:
        {
            if (iIsDrag && iDragRect.Contains(aPointerEvent.iPosition))
            {
                TInt distance = aPointerEvent.iPosition.iY - iDragPriorPoint.iY;
                iDragPriorPoint = aPointerEvent.iPosition;
                if (distance > 0)
                {
                    iTextDisplayer.DescStartIndex(distance);
                }
                else
                {
                    iTextDisplayer.AddStartIndex(distance * (-1));
                }
            }
            else
            {
                iIsDrag = EFalse;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void CAboutContainer::ConstructL(const TRect& aRect)
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

void CAboutContainer::GfxTimerFiredL(TInt /*aId*/)
{
    //在所以button都显示正常后，这心跳包可以暂停

    Quantum();
    DrawView();
    DrawNow();
}

void CAboutContainer::DrawView()
{
    //iBitmapGc->Clear();
    //iData->iDrawer->DrawWholeBackground(iBackupBitmap, iBackGroundSheep);
    iData->iDrawer->DrawBackgoundClip(iBackupBitmap, iBackGroundSheep, TEXT_DISPLAY_MIN_Y, TEXT_DISPLAY_MAX_Y);
    DrawHelpText();
    iData->iDrawer->DrawBackgoundClip(iBackupBitmap, iBackGroundSheep, 0, TEXT_DISPLAY_MIN_Y - 1);
    iData->iDrawer->DrawBackgoundClip(iBackupBitmap, iBackGroundSheep, TEXT_DISPLAY_MAX_Y + 1, SCREEN_HEIGHT - 1);
    iNavHelp.Draw(iBackupBitmap, iData->iResourceMap);
    iReturn.Draw(iBackupBitmap, iData->iResourceMap);
}

void CAboutContainer::FocusChanged(TDrawNow aDrawNow)
{
    SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void CAboutContainer::SetPaused(TBool aState)
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

TInt CAboutContainer::CountComponentControls() const
{
    return 0;
}

void CAboutContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);

    }
}

CCoeControl* CAboutContainer::ComponentControl(TInt /*aIndex*/) const
{
    return NULL;
}

TKeyResponse CAboutContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{

    return EKeyWasNotConsumed;
}

void CAboutContainer::SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent)
{
}

void CAboutContainer::ClearKeyDown(const TEnum::TGameKey& aKey)
{
}

TBool CAboutContainer::KeyDown(const TEnum::TGameKey& aKey)
{
    return ETrue;
}

void CAboutContainer::UpdateFromKeyStates()
{
}

TBool CAboutContainer::IsKeyPressed()
{
    return EFalse;
}

void CAboutContainer::SetGameState()
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
    iNavHelp.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontAbout, 0));
    iNavHelp.SetStartAndEndPoint(point, point);
    iNavHelp.ReSet();
    iNavHelp.UpdateObjectByCenter();
}

void CAboutContainer::Quantum()
{
    iReturn.Quantum();
}

TBool CAboutContainer::IsButtonNormalDisplay()
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

void CAboutContainer::InitHelpText()
{
    iTextDisplayer.ConstructL(iEikonEnv->DenseFont());
    //text
    _LIT(KHelpText," \nVersion: RS_MAN V1.0(EN)\n \nWarning");
    _LIT(KHelpText1,"\nThis software is protected by COPYRIGHT LAW OF THE PEOPLE'S REPUBLIC OF CHINA,related Judicial Interpretations by Supreme People's Court and Internation");
    _LIT(KHelpText2,"Conventions.The copyright of this software progrom belongs to HUA-JIN in accordance with the above-mentioned laws and conventions.");
    _LIT(KHelpText3,"Any unauthorized copy,spread,reverse compling or engineering of this software program in whole or in part,will be treated as an infringement to HUA-JIN,");
    _LIT(KHelpText4,"which will results in a severe civil prosecution,or even a criminal prosecution.");
    _LIT(KHelpText5,"\nFor known offender, HUA-JIN will take action to conduct a comprehensive legal sanctions according to the  above laws and international conventions \n \nEnd");
    iTextDisplayer.iBufText->Append(KHelpText);
    iTextDisplayer.iBufText->Append(KHelpText1);
    iTextDisplayer.iBufText->Append(KHelpText2);
    iTextDisplayer.iBufText->Append(KHelpText3);
    iTextDisplayer.iBufText->Append(KHelpText4);
    iTextDisplayer.iBufText->Append(KHelpText5);
    iTextDisplayer.FillArrayText();
    //iTextDisplayer.FillArrayLength();
}

void CAboutContainer::DrawHelpText()
{
    iTextDisplayer.DrawArrayText(iBitmapGc);
   
}
