/*
 * OptionContainer.h
 *
 *  Created on: 2010-9-8
 *      Author: Administrator
 */

#ifndef OPTIONCONTAINER_H_
#define OPTIONCONTAINER_H_

//这个Container用于刚进入程序时 的主菜单界面

// INCLUDES
#include <coecntrl.h>
#include <coeccntx.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <e32math.h>


#include "Macro.h"
#include "WorldObject.h"
#include "CGfxTimer.h"
#include "BitMapPosition.h"
#include "Enum.h"
#include "Drawer.h"
#include "ActionAnalyst.h"
#include "ButtonElement.h"
#include "MotionElement.h"
#include "Data.h"
#include "AudioPlayer.h"

//CLASS DECLARATION

class COptionContainer: public CCoeControl, public MGfxTimerCallBack
{
public:
    void GetDataObject(CData* aData);
    void ConstructL(const TRect& aRect,CData* aData);
    ~COptionContainer();
    // Game control
    void FocusChanged(TDrawNow aDrawNow);
    void SetPaused(TBool aState);
    //void ResetGame();

    // from CCoeControl
    void SizeChanged();
    void HandleResourceChange(TInt aType);
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    void HandlePointerEventMainMenu(const TPointerEvent& aPointerEvent);
    TBool IsButtonNormalDisplay();
    void SetGameState();
private:
    //Game functions
    virtual void GfxTimerFiredL(TInt /*aId*/); // World timer fired

private:
    void Draw(const TRect& aRect) const;
    void DrawView();
    // KeyBoard Handling
    void SetKeyDown(const TEnum::TGameKey& aKey, const TKeyEvent& aKeyEvent);
    void ClearKeyDown(const TEnum::TGameKey& aKey);
    TBool KeyDown(const TEnum::TGameKey& aKey);
    void UpdateFromKeyStates();
    TBool IsKeyPressed();
    void HandleButtonDown(TPoint aPoint);
    void HandleButtonUp(TPoint aPoint);
    void SetArrowPosition(TButtonElement* aArrow,TPoint aCurPoint, TBool aIsLeftArrow);
    TRect GetVisibleByArrow(TButtonElement* aLArrow, TButtonElement* aRArrow);
    void SetAllArrowNotHihtlight();
    void SetAllArrowButtonDownFalse();
    //set game state

    void Quantum();
    void SetMotionElementState();
public:
    CGfxTimer* iGfxTimer;
    TBool iIsFlagDelete;
private:
    CData* iData;
    CWsBitmap* iBackupBitmap;//绘图缓存
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    CWsBitmap* iBackGroundSheep;//背景
    CAudioPlayer* iPlayer;

    //Object
    //Main-MENU
    TButtonElement iSound;
    TButtonElement iVibra;
    TButtonElement iLevel;
    TButtonElement iReturn;
    TButtonElement iNavOption;
    TButtonElement iLayout;
    //
    TButtonElement iArrowLeft1;
    TButtonElement iArrowLeft2;
    TButtonElement iArrowLeft3;
    TButtonElement iArrowLeft4;
    TButtonElement iArrowRight1;
    TButtonElement iArrowRight2;
    TButtonElement iArrowRight3;
    TButtonElement iArrowRight4;
    //
    TMotionElement iMotionSound;
    TMotionElement iMotionVibra;
    TMotionElement iMotionLevel;
    TMotionElement iMotionLayout;
};

#endif /* OPTIONCONTAINER_H_ */
