/*
 ============================================================================
 Name		: RS_ManApplication.h
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Declares main application class.
 ============================================================================
 */

#ifndef __RS_MANAPPLICATION_H__
#define __RS_MANAPPLICATION_H__

// INCLUDES
#include <aknapp.h>
#include "RS_Man.hrh"

// UID for the application;
// this should correspond to the uid defined in the mmp file
const TUid KUidRS_ManApp = { _UID3 };

// CLASS DECLARATION

/**
 * CRS_ManApplication application class.
 * Provides factory to create concrete document object.
 * An instance of CRS_ManApplication is the application part of the
 * AVKON application framework for the RS_Man example application.
 */
class CRS_ManApplication: public CAknApplication
{
public:
    // Functions from base classes

    /**
     * From CApaApplication, AppDllUid.
     * @return Application's UID (KUidRS_ManApp).
     */
    TUid AppDllUid() const;

protected:
    // Functions from base classes

    /**
     * From CApaApplication, CreateDocumentL.
     * Creates CRS_ManDocument document object. The returned
     * pointer in not owned by the CRS_ManApplication object.
     * @return A pointer to the created document object.
     */
    CApaDocument* CreateDocumentL();
};

#endif // __RS_MANAPPLICATION_H__
// End of File
