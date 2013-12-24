/*
 * OptionContainer.cpp
 *
 *  Created on: 2010-9-8
 *      Author: jinhuafeng
 */

// INCLUDE FILES
#include <coemain.h>
#include "OptionContainer.h"
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
#define LAYOUT_LEFT_CENTER   63
#define LAYOUT_LEFT_ARROW_CENTER    161
#define LAYOUT_RIGHT_ARROW_CENTER   314
#define EXTEND_WIDTH 10
#define EXTEND_HEIGHT 7
void COptionContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

COptionContainer::~COptionContainer()
{

    delete iBackupBitmap;
    delete iGfxTimer;
    delete iBitmapDevice;
    delete iBitmapGc;
    delete iBackGroundSheep;
    delete iPlayer;
    // No implementation required
}

void COptionContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
}

void COptionContainer::SizeChanged()
{
    DrawNow();
}

void COptionContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
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

void COptionContainer::ConstructL(const TRect& aRect, CData* aData)
{
    iData = aData;
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
    iPlayer = CAudioPlayer::NewL(*iData->iFilePathWood, iData->iSoundDegree);

    ActivateL();
}

void COptionContainer::GfxTimerFiredL(TInt /*aId*/)
{
    Quantum();
    DrawView();
    DrawNow();
}

void COptionContainer::DrawView()
{
    //iBitmapGc->Reset();
    //iBitmapGc->SetBrushColor(KRgbBlack);
    iBitmapGc->Clear();
    iData->iDrawer->DrawWholeBackground(iBackupBitmap, iBackGroundSheep);
    iNavOption.Draw(iBackupBitmap, iData->iResourceMap);
    iSound.Draw(iBackupBitmap, iData->iResourceMap);
    iVibra.Draw(iBackupBitmap, iData->iResourceMap);
    iLevel.Draw(iBackupBitmap, iData->iResourceMap);
    iReturn.Draw(iBackupBitmap, iData->iResourceMap);
    iLayout.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowLeft1.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowLeft2.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowLeft3.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowLeft4.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowRight1.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowRight2.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowRight3.Draw(iBackupBitmap, iData->iResourceMap);
    iArrowRight4.Draw(iBackupBitmap, iData->iResourceMap);
    //
    iData->iDrawer->DrawLine(iBackupBitmap, TPoint(0, 153));
    if (IsButtonNormalDisplay())
    {
        iMotionSound.Draw(iBackupBitmap, iData->iResourceMap);
        iMotionVibra.Draw(iBackupBitmap, iData->iResourceMap);
        iMotionLevel.Draw(iBackupBitmap, iData->iResourceMap);
        iMotionLayout.Draw(iBackupBitmap, iData->iResourceMap);
    }
}

void COptionContainer::FocusChanged(TDrawNow aDrawNow)
{
    SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void COptionContainer::SetPaused(TBool aState)
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

TInt COptionContainer::CountComponentControls() const
{
    return 0;
}

void COptionContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);

    }
}

CCoeControl* COptionContainer::ComponentControl(TInt /*aIndex*/) const
{
    return NULL;
}

TKeyResponse COptionContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{

    return EKeyWasNotConsumed;
}

void COptionContainer::SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent)
{
}

void COptionContainer::ClearKeyDown(const TEnum::TGameKey& aKey)
{
}

TBool COptionContainer::KeyDown(const TEnum::TGameKey& aKey)
{
    return ETrue;
}

void COptionContainer::UpdateFromKeyStates()
{
}

TBool COptionContainer::IsKeyPressed()
{
    return EFalse;
}

void COptionContainer::SetGameState()
{
    //iData->iGameState = TEnum::EControlMainMenu;
    //设置MainMenu下的对象初始状态
    TPoint point;
    point.SetXY(FIRST_MENU_POSITION, FIRST_MENU_HEIGHT);
    //Sound
    iSound.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontSound, 0));
    iSound.SetStartAndEndPoint(point, TPoint(LAYOUT_LEFT_CENTER, point.iY));
    iSound.ReSet();
    SetArrowPosition(&iArrowLeft1, point, ETrue);
    SetArrowPosition(&iArrowRight1, point, EFalse);
    iMotionSound.SetVisibleArea(GetVisibleByArrow(&iArrowLeft1, &iArrowRight1));
    iMotionSound.iMotionDirection = TMotionElement::EEastToWest;
    //Vibra
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iVibra.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontVibra, 0));
    iVibra.SetStartAndEndPoint(point, TPoint(LAYOUT_LEFT_CENTER, point.iY));
    iVibra.ReSet();
    SetArrowPosition(&iArrowLeft2, point, ETrue);
    SetArrowPosition(&iArrowRight2, point, EFalse);
    iMotionVibra.SetVisibleArea(GetVisibleByArrow(&iArrowLeft2, &iArrowRight2));
    iMotionVibra.iMotionDirection = TMotionElement::EEastToWest;
    //Level
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iLevel.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontLevel, 0));
    iLevel.SetStartAndEndPoint(point, TPoint(LAYOUT_LEFT_CENTER, point.iY));
    iLevel.ReSet();
    SetArrowPosition(&iArrowLeft3, point, ETrue);
    SetArrowPosition(&iArrowRight3, point, EFalse);
    iMotionLevel.SetVisibleArea(GetVisibleByArrow(&iArrowLeft3, &iArrowRight3));
    iMotionLevel.iMotionDirection = TMotionElement::EEastToWest;
    //
    point.iX += MENU_WIGTH_SPAN;
    point.iY += MENU_HEIGHT_SPAN;
    iLayout.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontLayout, 0));
    iLayout.SetStartAndEndPoint(point, TPoint(LAYOUT_LEFT_CENTER, point.iY));
    iLayout.ReSet();
    SetArrowPosition(&iArrowLeft4, point, ETrue);
    SetArrowPosition(&iArrowRight4, point, EFalse);
    iMotionLayout.SetVisibleArea(GetVisibleByArrow(&iArrowLeft4, &iArrowRight4));
    iMotionLayout.iMotionDirection = TMotionElement::EEastToWest;
    //4
    point.iX += MENU_WIGTH_SPAN;
    point.iY = 610;
    TRect iLeftTopRect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::HighlightReturnEdge, 0);
    iReturn.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontReturn, 0));
    iReturn.SetStartAndEndPoint(point, TPoint(270, point.iY));
    iReturn.ReSet();
    iReturn.SetHighLightRect(iLeftTopRect, TRect(190, 610 - 27, 329, 610 + 27));
    //
    point.SetXY(180, 60);
    iNavOption.SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontOption, 0));
    iNavOption.SetStartAndEndPoint(point, point);
    iNavOption.ReSet();
    iNavOption.UpdateObjectByCenter();
    SetMotionElementState();
    SetAllArrowNotHihtlight();
}

void COptionContainer::Quantum()
{
    iSound.Quantum();
    iVibra.Quantum();
    iLevel.Quantum();
    iReturn.Quantum();
    iLayout.Quantum();
    //
    iArrowLeft1.Quantum();
    iArrowLeft2.Quantum();
    iArrowLeft3.Quantum();
    iArrowLeft4.Quantum();
    iArrowRight1.Quantum();
    iArrowRight2.Quantum();
    iArrowRight3.Quantum();
    iArrowRight4.Quantum();
    if (IsButtonNormalDisplay())
    {
        iMotionSound.Quantum();
        iMotionVibra.Quantum();
        iMotionLevel.Quantum();
        iMotionLayout.Quantum();
    }
}

TBool COptionContainer::IsButtonNormalDisplay()
{
    //当所有按钮为正常显示状态时返回ETrue;
    if (iArrowRight4.iActionType == TEnum::EButtonNormalDisplay && iReturn.iActionType == TEnum::EButtonNormalDisplay)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}

void COptionContainer::SetArrowPosition(TButtonElement* aArrow, TPoint aCurPoint, TBool aIsLeftArrow)
{
    TPoint point2;
    point2 = aCurPoint;
    if (aIsLeftArrow)
    {
        point2.iX = aCurPoint.iX + (LAYOUT_LEFT_ARROW_CENTER - LAYOUT_LEFT_CENTER);
        aArrow->SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontLeftArrow, 0));
        aArrow->SetStartAndEndPoint(point2, TPoint(LAYOUT_LEFT_ARROW_CENTER, aCurPoint.iY));
        aArrow->ReSet();
    }
    else
    {
        point2.iX = aCurPoint.iX + (LAYOUT_RIGHT_ARROW_CENTER - LAYOUT_LEFT_CENTER);
        aArrow->SetBitMapRect(iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontRightArrow, 0));
        aArrow->SetStartAndEndPoint(point2, TPoint(LAYOUT_RIGHT_ARROW_CENTER, aCurPoint.iY));
        aArrow->ReSet();
    }
}

//根据箭头的文章设置Motion对象的可见域
TRect COptionContainer::GetVisibleByArrow(TButtonElement* aLArrow, TButtonElement* aRArrow)
{
    TRect rect;
    rect.SetRect(aLArrow->iEndPoint.iX + aLArrow->iHalfWidth + 5, aLArrow->iEndPoint.iY - aLArrow->iHalfHeight,
        aRArrow->iEndPoint.iX - aRArrow->iHalfWidth - 5, aRArrow->iEndPoint.iY + aRArrow->iHalfHeight);
    return rect;
}

void COptionContainer::SetMotionElementState()
{
    //Sound
    iMotionSound.SetNewAndOldMapRect(iData->GetMotionRectByNum(iData->iSoundDegree), iData->GetMotionRectByNum(
        iData->iSoundDegree));
    //Vibra
    iMotionVibra.SetNewAndOldMapRect(iData->GetMOtionRectByBool(iData->iVibraEnable), iData->GetMOtionRectByBool(
        iData->iVibraEnable));
    //Level
    iMotionLevel.SetNewAndOldMapRect(iData->GetMotionRectByLevel(iData->iGameLevel), iData->GetMotionRectByLevel(
        iData->iGameLevel));
    //Layout
    iMotionLayout.SetNewAndOldMapRect(iData->GetMotionRectByLayout(iData->iLayoutType), iData->GetMotionRectByLayout(
        iData->iLayoutType));
}

void COptionContainer::SetAllArrowNotHihtlight()
{
    //
    iArrowLeft1.iIsNeedHighLight = EFalse;
    iArrowLeft2.iIsNeedHighLight = EFalse;
    iArrowLeft3.iIsNeedHighLight = EFalse;
    iArrowLeft4.iIsNeedHighLight = EFalse;
    //
    iArrowRight1.iIsNeedHighLight = EFalse;
    iArrowRight2.iIsNeedHighLight = EFalse;
    iArrowRight3.iIsNeedHighLight = EFalse;
    iArrowRight4.iIsNeedHighLight = EFalse;
}
void COptionContainer::SetAllArrowButtonDownFalse()
{
    iArrowLeft1.iIsButtonDown = EFalse;
    iArrowLeft2.iIsButtonDown = EFalse;
    iArrowLeft3.iIsButtonDown = EFalse;
    iArrowLeft4.iIsButtonDown = EFalse;
    iArrowRight1.iIsButtonDown = EFalse;
    iArrowRight2.iIsButtonDown = EFalse;
    iArrowRight3.iIsButtonDown = EFalse;
    iArrowRight4.iIsButtonDown = EFalse;
}
void COptionContainer::HandleButtonDown(TPoint aPoint)
{
    iReturn.iIsButtonDown = EFalse;
    SetAllArrowButtonDownFalse();
    if (iReturn.iWorldPosition.Contains(aPoint))
    {
        iReturn.iIsButtonDown = ETrue;
        return;
    }
    TRect extendRect;
    TRect rect;
    rect = iArrowLeft1.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowLeft1.iIsButtonDown = ETrue;
    }
    rect = iArrowLeft2.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowLeft2.iIsButtonDown = ETrue;
    }
    rect = iArrowLeft3.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowLeft3.iIsButtonDown = ETrue;
    }
    rect = iArrowLeft4.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowLeft4.iIsButtonDown = ETrue;
    }
    rect = iArrowRight1.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowRight1.iIsButtonDown = ETrue;
    }
    rect = iArrowRight2.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowRight2.iIsButtonDown = ETrue;
    }
    rect = iArrowRight3.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowRight3.iIsButtonDown = ETrue;
    }
    rect = iArrowRight4.iWorldPosition;
    extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH, rect.iBr.iY
        + EXTEND_HEIGHT);
    if (extendRect.Contains(aPoint))
    {
        iArrowRight4.iIsButtonDown = ETrue;
    }
}

void COptionContainer::HandleButtonUp(TPoint aPoint)
{
    TRect extendRect;
    TRect rect;
    if (iReturn.iIsButtonDown)
    {
        if (iReturn.iWorldPosition.Contains(aPoint))
        {
            iData->SetOptionValue();
            iData->iGameState = iData->iPreviousState;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            return;
        }
    }
    if (iArrowLeft1.iIsButtonDown)
    {
        //sound
        rect = iArrowLeft1.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TInt oldValue = iData->iSoundDegree;
            iData->iSoundDegree--;
            if (iData->iSoundDegree < 0)
            {
                iData->iSoundDegree = 10;
            }
            //播放声音
            if (iPlayer)
            {
                iPlayer->SetSoundDegree(iData->iSoundDegree);
                iPlayer->Play();
            }
            iMotionSound.iMotionDirection = TMotionElement::EEastToWest;
            iMotionSound.SetNewAndOldMapRect(iData->GetMotionRectByNum(iData->iSoundDegree), iData->GetMotionRectByNum(
                oldValue));
        }
    }
    if (iArrowRight1.iIsButtonDown)
    {
        rect = iArrowRight1.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TInt oldValue = iData->iSoundDegree;
            iData->iSoundDegree++;
            if (iData->iSoundDegree > 10)
            {
                iData->iSoundDegree = 0;
            }
            //播放声音
            if (iPlayer)
            {
                iPlayer->SetSoundDegree(iData->iSoundDegree);
                iPlayer->Play();
            }
            iMotionSound.iMotionDirection = TMotionElement::EWestToEast;
            iMotionSound.SetNewAndOldMapRect(iData->GetMotionRectByNum(iData->iSoundDegree), iData->GetMotionRectByNum(
                oldValue));
        }
    }
    //Vibra
    if (iArrowLeft2.iIsButtonDown)
    {
        rect = iArrowLeft2.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TBool state = iData->iVibraEnable;
            iData->iVibraEnable = !iData->iVibraEnable;
            iMotionVibra.iMotionDirection = TMotionElement::EEastToWest;
            iMotionVibra.SetNewAndOldMapRect(iData->GetMOtionRectByBool(iData->iVibraEnable),
                iData->GetMOtionRectByBool(state));
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
        }
    }
    if (iArrowRight2.iIsButtonDown)
    {
        rect = iArrowRight2.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TBool state = iData->iVibraEnable;
            iData->iVibraEnable = !iData->iVibraEnable;
            iMotionVibra.iMotionDirection = TMotionElement::EWestToEast;
            iMotionVibra.SetNewAndOldMapRect(iData->GetMOtionRectByBool(iData->iVibraEnable),
                iData->GetMOtionRectByBool(state));
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
        }
    }
    //Level
    if (iArrowLeft3.iIsButtonDown)
    {
        rect = iArrowLeft3.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TEnum::TGameLevel gameLevel = iData->iGameLevel;
            switch (iData->iGameLevel)
            {
                case TEnum::EEasy:
                {
                    iData->iGameLevel = TEnum::ENormal;
                    iData->iScroll++;
                    break;
                }
                case TEnum::ENormal:
                {
                    iData->iGameLevel = TEnum::EHard;
                    iData->iScroll++;
                    break;
                }
                case TEnum::EHard:
                {
                    iData->iGameLevel=TEnum::EEasy;
                    iData->iScroll=iData->iScroll-2;
                    break;
                }
            }
            iMotionLevel.iMotionDirection = TMotionElement::EEastToWest;
            iMotionLevel.SetNewAndOldMapRect(iData->GetMotionRectByLevel(iData->iGameLevel),
                iData->GetMotionRectByLevel(gameLevel));
        }
    }
    if (iArrowRight3.iIsButtonDown)
    {
        rect = iArrowRight3.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TEnum::TGameLevel gameLevel = iData->iGameLevel;
            switch (iData->iGameLevel)
            {
                case TEnum::EHard:
                {
                    iData->iGameLevel = TEnum::ENormal;
                    iData->iScroll--;
                    break;
                }
                case TEnum::ENormal:
                {
                    iData->iGameLevel = TEnum::EEasy;
                    iData->iScroll--;
                    break;
                }
                case TEnum::EEasy:
                {
                    iData->iGameLevel = TEnum::EHard;
                    iData->iScroll=iData->iScroll+2;
                    break;
                }
            }
            iMotionLevel.iMotionDirection = TMotionElement::EWestToEast;
            iMotionLevel.SetNewAndOldMapRect(iData->GetMotionRectByLevel(iData->iGameLevel),
                iData->GetMotionRectByLevel(gameLevel));
        }
    }
    //Layout
    if (iArrowLeft4.iIsButtonDown)
    {
        rect = iArrowLeft4.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TEnum::TLayoutType layoutType = iData->iLayoutType;
            switch (iData->iLayoutType)
            {
                case TEnum::ELeftHand:
                {
                    iData->iLayoutType = TEnum::ERightHand;
                    break;
                }
                case TEnum::EHands:
                {
                    iData->iLayoutType = TEnum::ELeftHand;
                    break;
                }
                case TEnum::ERightHand:
                {
                    iData->iLayoutType = TEnum::EHands;
                    break;
                }
            }
            iMotionLayout.iMotionDirection = TMotionElement::EEastToWest;
            iMotionLayout.SetNewAndOldMapRect(iData->GetMotionRectByLayout(iData->iLayoutType),
                iData->GetMotionRectByLayout(layoutType));
        }
    }
    if (iArrowRight4.iIsButtonDown)
    {
        rect = iArrowRight4.iWorldPosition;
        extendRect.SetRect(rect.iTl.iX - EXTEND_WIDTH, rect.iTl.iY - EXTEND_HEIGHT, rect.iBr.iX + EXTEND_WIDTH,
            rect.iBr.iY + EXTEND_HEIGHT);
        if (extendRect.Contains(aPoint))
        {
            TEnum::TLayoutType layoutType = iData->iLayoutType;
            switch (iData->iLayoutType)
            {
                case TEnum::ERightHand:
                {
                    iData->iLayoutType = TEnum::ELeftHand;
                    break;
                }
                case TEnum::EHands:
                {
                    iData->iLayoutType = TEnum::ERightHand;
                    break;
                }
                case TEnum::ELeftHand:
                {
                    iData->iLayoutType =TEnum::EHands;
                    break;
                }
            }
            iMotionLayout.iMotionDirection = TMotionElement::EWestToEast;
            iMotionLayout.SetNewAndOldMapRect(iData->GetMotionRectByLayout(iData->iLayoutType),
                iData->GetMotionRectByLayout(layoutType));
        }
    }
    iReturn.iIsButtonDown = EFalse;
    SetAllArrowButtonDownFalse();
}
// End of File


