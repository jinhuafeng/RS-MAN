/*
 * RS_ManControlView.h
 *
 *  Created on: 2010-8-28
 *      Author: panda
 */

#ifndef RS_MANCONTROLVIEW_H_
#define RS_MANCONTROLVIEW_H_

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
#include "Data.h"
//CLASS DECLARATION

class CMenuContainer: public CCoeControl, public MGfxTimerCallBack
{
public:
    void GetDataObject(CData* aData);
    void ConstructL(const TRect& aRect);
    ~CMenuContainer();
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
    TBool IsButtonNormalDisplay();
    void SetGameState();
    void HandleButtonDown(TPoint aPoint);
    void HandleButtonUp(TPoint aPoint);
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
    //set game state
    
    void Quantum();
public:
    CGfxTimer* iGfxTimer;
    TBool iIsFlagDelete;
private:
    CData* iData;
    CWsBitmap* iBackupBitmap;//绘图缓存
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    CWsBitmap* iBackGroundSheep;//背景
    //CWsBitmap* iResourceControl;//资源
    //TBitMapPosition* ipBitMapPosition;//资源位置
    // World objects 
    //TDrawer iDrawer;
    
    //Object
    //Main-MENU
    TButtonElement iStart;
    TButtonElement iOption;
    TButtonElement iAward;
    TButtonElement iHelp;
    TButtonElement iAbout;
    TButtonElement iExit;
    TButtonElement iLogo;
};

#endif /* RS_MANCONTROLVIEW_H_ */
