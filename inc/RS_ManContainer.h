/*
 ============================================================================
 Name		: RS_ManAppView.h
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Declares view class for application.
 ============================================================================
 */

#ifndef __RS_MANAPPVIEW_h__
#define __RS_MANAPPVIEW_h__

// INCLUDES
#include <coecntrl.h>

#include <coeccntx.h>

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include "WorldObject.h"
#include "CGfxTimer.h"
#include <e32math.h>
#include <e32event.h>
#include <aknnotewrappers.h>
#include "BitMapPosition.h"
#include "WorldPoint.h"
#include "BoardQueue.h"
#include "BoardPool.h"
#include "ProbabilityTable.h"
#include "Enum.h"
#include "Drawer.h"
#include "ActionAnalyst.h"
#include "Macro.h"
#include "Data.h"
#include "AudioPlayer.h"
#include "BitmapNum.h"
#include "CallsMonitor.h"



typedef CObjectPool<TWoodBoard, 8> CWoodBoardPool;

typedef CObjectPool<TMarbleBoard, 8> CMarbleBoardPool;

typedef CObjectPool<TConveyBoard, 8> CConveyBoardPool;

typedef CObjectPool<TStabBoard, 8> CStabBoardPool;

typedef CObjectPool<TSpringBoard, 8> CSpringBoardPool;


// CLASS DECLARATION
class CRS_ManContainer: public CCoeControl, public MGfxTimerCallBack, public MCallCallBack
{

public:
    void ConstructL(const TRect& aRect,CData* aData);
    void GetDataObject(CData* aData);
    ~CRS_ManContainer();
    // Game control
    void FocusChanged(TDrawNow aDrawNow);
    void SetPaused(TBool aState);
    void ResetGame();

    // from CCoeControl
    void SizeChanged();
    void HandleResourceChange(TInt aType);
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
    virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
    virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    void SetGameState();

private:
    //Game functions
    virtual void GfxTimerFiredL(TInt /*aId*/); // World timer fired
    // MCallCallBack
    void CallStatusChangedL(CTelephony::TCallStatus& aStatus, TInt aError);

private:
    void Draw(const TRect& aRect) const;
    void DrawGame();
    void DrawIndicator();
    void DrawReturnArrow();
    void HandleDebugGameKey();
    // Motion update functions
    void UpdateBoards();
    //
    void AddFrame();
    void DescFrame();
    //Man 相关
    void HandleManMain();
    //更新Man
    void UpdateMan();
    //计算碰撞
    void CalculateCollisions();
    //处理不同类型的Board碰撞
    void CollisionOccur(TWorldObject* pBoard);
    //根据先前的计算及方向键情况计算Man的ActionState和相应的帧数
    void CalcActionState();
    void StopAllAudioPlayer();
    void Congratulation();
    TInt iTicks;
public:
    CGfxTimer* iGfxTimer;
    TBool iIsFlagDelete;
private:
    CWsBitmap* iBackupBitmap;//绘图缓存
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    CWsBitmap* iBackGround;//背景
    CWsBitmap* iResourceMap;//资源
    
    TBitmapNum* iBitmapNum;
    // World objects 
    TMan* iMan;
    CWoodBoardPool* iWoodBoardPool;
    CMarbleBoardPool* iMarbleBoardPool;
    CConveyBoardPool* iConveyBoardPool;
    CStabBoardPool* iStabBoardPool;
    CSpringBoardPool* iSpringBoardPool;
    CData* iData;
    CAudioPlayer* iWoodPlayer;
    CAudioPlayer* iStabPlayer;
    CAudioPlayer* iMarblePlayer;
    CAudioPlayer* iConveyPlayer;
    CAudioPlayer* iNormalDeadPlayer;
    CAudioPlayer* iDropDeadPlayer;
    CAudioPlayer* iSpringPlayer;
    CAudioPlayer* iSpringPlayer2;
    CAudioPlayer* iCongratulationPlayer;
    TBool iSpringSoundSwitch;
    TEnum::TGameKey iGameKey;
    TActionAnalyst iActionAnalyst;
    CCallMonitor* iCallMonitor;
    HBufC* iTelephoneState;
    CTelephony::TCallStatus iCallStatus;
};

#endif // __RS_MANAPPVIEW_h__
// End of File
