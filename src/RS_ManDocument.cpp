/*
 ============================================================================
 Name		: RS_ManDocument.cpp
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : CRS_ManDocument implementation
 ============================================================================
 */

// INCLUDE FILES
#include "RS_ManAppUi.h"
#include "RS_ManDocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CRS_ManDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CRS_ManDocument* CRS_ManDocument::NewL(CEikApplication& aApp)
{
    CRS_ManDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
}

// -----------------------------------------------------------------------------
// CRS_ManDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CRS_ManDocument* CRS_ManDocument::NewLC(CEikApplication& aApp)
{
    CRS_ManDocument* self = new (ELeave) CRS_ManDocument(aApp);

    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
}

// -----------------------------------------------------------------------------
// CRS_ManDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CRS_ManDocument::ConstructL()
{
    // No implementation required
}

// -----------------------------------------------------------------------------
// CRS_ManDocument::CRS_ManDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CRS_ManDocument::CRS_ManDocument(CEikApplication& aApp) :
    CAknDocument(aApp)
{
    // No implementation required
}

// ---------------------------------------------------------------------------
// CRS_ManDocument::~CRS_ManDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CRS_ManDocument::~CRS_ManDocument()
{
    // No implementation required
}

// ---------------------------------------------------------------------------
// CRS_ManDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CRS_ManDocument::CreateAppUiL()
{
    // Create the application user interface, and return a pointer to it;
    // the framework takes ownership of this object
    return new (ELeave) CRS_ManAppUi;
}

// End of File
