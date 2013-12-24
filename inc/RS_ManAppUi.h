/*
 ============================================================================
 Name		: RS_ManAppUi.h
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Declares UI class for application.
 ============================================================================
 */

#ifndef __RS_MANAPPUI_h__
#define __RS_MANAPPUI_h__

// INCLUDES
#include <aknappui.h>
#include "RS_ManContainer.h"
#include "MenuContainer.h"
#include "AwardContainer.h"
#include "HelpContainer.h"
#include "PausedContainer.h"
#include "OptionContainer.h"
#include "AboutContainer.h"
#include "Data.h"

// CLASS DECLARATION
/**
 * CRS_ManAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CRS_ManAppUi: public CAknAppUi,MCoeControlObserver
{
public:
    // Constructors and destructor

    /**
     * ConstructL.
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CRS_ManAppUi.
     * C++ default constructor. This needs to be public due to
     * the way the framework constructs the AppUi
     */
    CRS_ManAppUi();

    /**
     * ~CRS_ManAppUi.
     * Virtual Destructor.
     */
    virtual ~CRS_ManAppUi();
    //
    void SwitchContainer(TEnum::TGameState aGameState);
    void RemoveFlagDeleteObjectFromStack();
    void SetFalgDelete();
    virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
    virtual void HandleWsEventL( const TWsEvent &aEvent, CCoeControl *aDestination );
private:
    // Functions from base classes

    /**
     * From CEikAppUi, HandleCommandL.
     * Takes care of command handling.
     * @param aCommand Command to be handled.
     */
    void HandleCommandL(TInt aCommand);

    /**
     *  HandleStatusPaneSizeChange.
     *  Called by the framework when the application status pane
     *  size is changed.
     */
    void HandleStatusPaneSizeChange();

    /**
     *  From CCoeAppUi, HelpContextL.
     *  Provides help context for the application.
     *  size is changed.
     */
private:
    // Data

    /**
     * The application view
     * Owned by CRS_ManAppUi
     */
    CRS_ManContainer* iAppContainer;
    CMenuContainer* iMenuContainer;
    COptionContainer* iOptionContainer;
    CHelpContainer* iHelpContainer;
    CAwardContainer* iAwardContainer;
    CPausedContainer* iPausedContainer;
    CAboutContainer* iAboutContainer;
    CData iData;
};

#endif // __RS_MANAPPUI_h__
// End of File
