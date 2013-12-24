/*
 * HelpContainer.h
 *
 *  Created on: 2010-9-8
 *      Author: Administrator
 */

#ifndef HELPCONTAINER_H_
#define HELPCONTAINER_H_

// INCLUDES
#include <coecntrl.h>
#include <coeccntx.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <e32math.h>
#include <AknUtils.h> 

//#include <badesca.h>  // CDesCArrayFlat
//#include <gdi.h>  // CGraphicsDevice
//#include <gulutil.h>  // FontUtils
//
#include "Macro.h"
#include "WorldObject.h"
#include "CGfxTimer.h"
#include "BitMapPosition.h"
#include "Enum.h"
#include "Drawer.h"
#include "ActionAnalyst.h"
#include "ButtonElement.h"
#include "TextDisplayer.h"
#include "Data.h"
//CLASS DECLARATION

class CHelpContainer: public CCoeControl, public MGfxTimerCallBack
{
public:
    void GetDataObject(CData* aData);
    void ConstructL(const TRect& aRect);
    ~CHelpContainer();
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
    void InitHelpText();
    void DrawHelpText();
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
    CWsBitmap* iBackupBitmap;//»æÍ¼»º´æ
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    CWsBitmap* iBackGroundSheep;//±³¾°
    
    TButtonElement iReturn;
    TButtonElement iNavHelp;
    TButtonElement iLogo;
    //TBuf<500>* iHelpText;//°ïÖúÎÄ±¾µÄÄÚÈÝ
    //CArrayFix<TPtrC> * iHelpTextArray;
    CTextDisplayer iTextDisplayer;
    TRect iDragRect;
    TPoint iDragPriorPoint;
    TBool iIsDrag;
};


#endif /* HELPCONTAINER_H_ */
