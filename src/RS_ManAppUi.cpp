/*
 ============================================================================
 Name		: RS_ManAppUi.cpp
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : CRS_ManAppUi implementation
 ============================================================================
 */
// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <hlplch.h>
#include <akndef.h>
#include <RS_Man_0xE2A1DCB7.rsg>
#include "RS_Man_0xE2A1DCB7.hlp.hrh"
#include "RS_Man.hrh"
#include "RS_Man.pan"
#include "RS_ManApplication.h"
#include "RS_ManAppUi.h"
#include "RS_ManContainer.h"
#include <RS_Man.mbg>
_LIT( KFileName, "C:\\private\\E2A1DCB7\\RS_Man.txt" );
_LIT( KText, "RS-Man 1.0");

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CRS_ManAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CRS_ManAppUi::ConstructL()
{
    CAknAppUiBase::SetFullScreenApp(ETrue);
    BaseConstructL();
    //EAppOrientationPortrait
    //CAknAppUiBase::SetOrientation(EAppOrientationPortrait);
    CAknAppUiBase::SetOrientationL(EAppUiOrientationPortrait);
    //BaseConstructL( EAknEnableSkin  | EAknTouchCompatible | EAppOrientationPortrait);
    iData.ConstructL();
    TRAPD(err1, iData.iResourceMap=iEikonEnv->CreateBitmapL(_L("\\resource\\apps\\RS_Man.mbm"),EMbmRs_manResourcemap));
    iMenuContainer = new (ELeave) CMenuContainer();
    iMenuContainer->ConstructL(ApplicationRect());
    iMenuContainer->GetDataObject(&iData);
    iMenuContainer->SetMopParent(this);
    iMenuContainer->SetObserver(this);
    iMenuContainer->MakeVisible(ETrue);
    iMenuContainer->SetGameState();
    //先将主目录入栈
    AddToStackL(iMenuContainer);
    //
    iData.SetFilePathNameL();
    //-"!:\resource\apps\RS_Man\Sounds\Wood.wav"
    //iData.iFileName= Application()->AppFullName();
}
// -----------------------------------------------------------------------------
// CRS_ManAppUi::CRS_ManAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CRS_ManAppUi::CRS_ManAppUi()
{
    // No implementation required
}

// -----------------------------------------------------------------------------
// CRS_ManAppUi::~CRS_ManAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CRS_ManAppUi::~CRS_ManAppUi()
{
    RemoveFlagDeleteObjectFromStack();
    delete iData.iResourceMap;
}

// -----------------------------------------------------------------------------
// CRS_ManAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CRS_ManAppUi::HandleCommandL(TInt aCommand)
{
    switch (aCommand)
    {
        case ECommand1:
        {
            iEikonEnv->InfoWinL(_L("-=RS_Man=-"), _L("wellpoint@yeah.net"));
            break;
        }
        case EEikCmdExit:
        {
            Exit();
            break;
        }
        case EAknSoftkeyExit:
        {
            Exit();
            break;
        }
        default:
        {
            //          Panic(0);
            break;
        }
    }
}
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CRS_ManAppUi::HandleStatusPaneSizeChange()
{
    //iAppContainer->SetRect(ClientRect());
}
void CRS_ManAppUi::SwitchContainer(TEnum::TGameState aGameState)
{
    SetFalgDelete();
    switch (aGameState)
    {
        //游戏暂停后的状态 //游戏结束后的状态
        case TEnum::EControlPaused:
        {
            iPausedContainer = new (ELeave) CPausedContainer();
            iPausedContainer->ConstructL(ApplicationRect());
            iPausedContainer->GetDataObject(&iData);
            iPausedContainer->SetMopParent(this);
            iPausedContainer->SetObserver(this);
            iPausedContainer->MakeVisible(ETrue);
            iPausedContainer->SetGameState();
            AddToStackL(iPausedContainer);
            break;
        }
        case TEnum::EControlAward:
        {
            iAwardContainer = new (ELeave) CAwardContainer();
            iAwardContainer->ConstructL(ApplicationRect());
            iAwardContainer->GetDataObject(&iData);
            iAwardContainer->SetMopParent(this);
            iAwardContainer->SetObserver(this);
            iAwardContainer->MakeVisible(ETrue);
            iAwardContainer->SetGameState();
            AddToStackL(iAwardContainer);
            break;
        }
        case TEnum::EControlMainMenu:
        {
            iMenuContainer = new (ELeave) CMenuContainer();
            iMenuContainer->ConstructL(ApplicationRect());
            iMenuContainer->GetDataObject(&iData);
            iMenuContainer->SetMopParent(this);
            iMenuContainer->SetObserver(this);
            iMenuContainer->MakeVisible(ETrue);
            iMenuContainer->SetGameState();
            AddToStackL(iMenuContainer);
            break;
        }
            //开始游戏或重新游戏后的状态 //返回游戏后的状态
        case TEnum::EWaitingStart:
        case TEnum::EPlaying:
        {
            iAppContainer = new (ELeave) CRS_ManContainer();
            iAppContainer->ConstructL(ApplicationRect(), &iData);
            //iAppContainer->GetDataObject(&iData);
            iAppContainer->SetMopParent(this);
            iAppContainer->SetObserver(this);
            iAppContainer->MakeVisible(ETrue);
            iAppContainer->SetGameState();
            //iAppContainer->ActiveTimer();
            AddToStackL(iAppContainer);
            break;
        }
        case TEnum::EControlOption:
        {
            iOptionContainer = new (ELeave) COptionContainer();
            iOptionContainer->ConstructL(ApplicationRect(), &iData);
            //iOptionContainer->GetDataObject(&iData);
            iOptionContainer->SetMopParent(this);
            iOptionContainer->SetObserver(this);
            iOptionContainer->MakeVisible(ETrue);
            iOptionContainer->SetGameState();
            AddToStackL(iOptionContainer);
            break;
        }
        case TEnum::EControlHelp:
        {
            iHelpContainer = new (ELeave) CHelpContainer();
            iHelpContainer->ConstructL(ApplicationRect());
            iHelpContainer->GetDataObject(&iData);
            iHelpContainer->SetMopParent(this);
            iHelpContainer->SetObserver(this);
            iHelpContainer->MakeVisible(ETrue);
            iHelpContainer->SetGameState();
            AddToStackL(iHelpContainer);
            break;
        }
        case TEnum::EControlAbout:
        {
            iAboutContainer = new (ELeave) CAboutContainer();
            iAboutContainer->ConstructL(ApplicationRect());
            iAboutContainer->GetDataObject(&iData);
            iAboutContainer->SetMopParent(this);
            iAboutContainer->SetObserver(this);
            iAboutContainer->MakeVisible(ETrue);
            iAboutContainer->SetGameState();
            AddToStackL(iAboutContainer);
            break;
        }
        case TEnum::EControlExit:
        {
            HandleCommandL(EEikCmdExit);
        }
        default:
        {
            break;
        }
    }
    RemoveFlagDeleteObjectFromStack();
}

void CRS_ManAppUi::HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType)
{
    switch (aEventType)
    {
        case EEventStateChanged:
        {
            SwitchContainer(iData.iGameState);
            break;
        }
        default:
        {
            break;
        }
    }
}
void CRS_ManAppUi::HandleWsEventL(const TWsEvent &aEvent, CCoeControl *aDestination)
{

    switch (aEvent.Type())
    {
        case KAknUidValueEndKeyCloseEvent:
        {
            // 按下挂机键以后的操作
            //如果正在游戏，则暂停
            if (iAppContainer)
            {
                iAppContainer->iGfxTimer->Pause();
                iData.iGameState = TEnum::EControlPaused;
                SwitchContainer(iData.iGameState);
            }
            break;
        }
        default:
        {
            CAknAppUi::HandleWsEventL(aEvent, aDestination);
        }
    }

}
void CRS_ManAppUi::SetFalgDelete()
{
    if (iMenuContainer)
    {
        iMenuContainer->iIsFlagDelete = ETrue;
        return;
    }
    if (iAppContainer)
    {
        iAppContainer->iIsFlagDelete = ETrue;
        return;
    }
    if (iOptionContainer)
    {
        iOptionContainer->iIsFlagDelete = ETrue;
        return;
    }
    if (iHelpContainer)
    {
        iHelpContainer->iIsFlagDelete = ETrue;
        return;
    }
    if (iAboutContainer)
    {
        iAboutContainer->iIsFlagDelete = ETrue;
        return;
    }
    if (iAwardContainer)
    {
        iAwardContainer->iIsFlagDelete = ETrue;
        return;
    }
    if (iPausedContainer)
    {
        iPausedContainer->iIsFlagDelete = ETrue;
        return;
    }
}
void CRS_ManAppUi::RemoveFlagDeleteObjectFromStack()
{
    if (iMenuContainer)
    {
        if (iMenuContainer->iIsFlagDelete)
        {
            RemoveFromStack(iMenuContainer);
            delete iMenuContainer;
            iMenuContainer = NULL;
            return;
        }
    }
    if (iAppContainer)
    {
        if (iAppContainer->iIsFlagDelete)
        {
            RemoveFromStack(iAppContainer);
            delete iAppContainer;
            iAppContainer = NULL;
            return;
        }
    }
    if (iOptionContainer)
    {
        if (iOptionContainer->iIsFlagDelete)
        {
            RemoveFromStack(iOptionContainer);
            delete iOptionContainer;
            iOptionContainer = NULL;
            return;
        }
    }
    if (iHelpContainer)
    {
        if (iHelpContainer->iIsFlagDelete)
        {
            RemoveFromStack(iHelpContainer);
            delete iHelpContainer;
            iHelpContainer = NULL;
            return;
        }
    }
    if (iAboutContainer)
    {
        if (iAboutContainer->iIsFlagDelete)
        {
            RemoveFromStack(iAboutContainer);
            delete iAboutContainer;
            iAboutContainer = NULL;
            return;
        }
    }
    if (iAwardContainer)
    {
        if (iAwardContainer->iIsFlagDelete)
        {
            RemoveFromStack(iAwardContainer);
            delete iAwardContainer;
            iAwardContainer = NULL;
            return;
        }
    }
    if (iPausedContainer)
    {
        if (iPausedContainer->iIsFlagDelete)
        {
            RemoveFromStack(iPausedContainer);
            delete iPausedContainer;
            iPausedContainer = NULL;
            return;
        }
    }
}

// End of File
