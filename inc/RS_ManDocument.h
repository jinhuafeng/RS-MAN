/*
 ============================================================================
 Name		: RS_ManDocument.h
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Declares document class for application.
 ============================================================================
 */

#ifndef __RS_MANDOCUMENT_h__
#define __RS_MANDOCUMENT_h__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CRS_ManAppUi;
class CEikApplication;

// CLASS DECLARATION

/**
 * CRS_ManDocument application class.
 * An instance of class CRS_ManDocument is the Document part of the
 * AVKON application framework for the RS_Man example application.
 */
class CRS_ManDocument: public CAknDocument
{
public:
    // Constructors and destructor

    /**
     * NewL.
     * Two-phased constructor.
     * Construct a CRS_ManDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CRS_ManDocument.
     */
    static CRS_ManDocument* NewL(CEikApplication& aApp);

    /**
     * NewLC.
     * Two-phased constructor.
     * Construct a CRS_ManDocument for the AVKON application aApp
     * using two phase construction, and return a pointer
     * to the created object.
     * @param aApp Application creating this document.
     * @return A pointer to the created instance of CRS_ManDocument.
     */
    static CRS_ManDocument* NewLC(CEikApplication& aApp);

    /**
     * ~CRS_ManDocument
     * Virtual Destructor.
     */
    virtual ~CRS_ManDocument();

public:
    // Functions from base classes

    /**
     * CreateAppUiL
     * From CEikDocument, CreateAppUiL.
     * Create a CRS_ManAppUi object and return a pointer to it.
     * The object returned is owned by the Uikon framework.
     * @return Pointer to created instance of AppUi.
     */
    CEikAppUi* CreateAppUiL();

private:
    // Constructors

    /**
     * ConstructL
     * 2nd phase constructor.
     */
    void ConstructL();

    /**
     * CRS_ManDocument.
     * C++ default constructor.
     * @param aApp Application creating this document.
     */
    CRS_ManDocument(CEikApplication& aApp);

};

#endif // __RS_MANDOCUMENT_h__
// End of File
