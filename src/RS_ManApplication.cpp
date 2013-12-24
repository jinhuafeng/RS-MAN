/*
 ============================================================================
 Name		: RS_ManApplication.cpp
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include "RS_Man.hrh"
#include "RS_ManDocument.h"
#include "RS_ManApplication.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CRS_ManApplication::CreateDocumentL()
// Creates CApaDocument object
// -----------------------------------------------------------------------------
//
CApaDocument* CRS_ManApplication::CreateDocumentL()
{
    // Create an RS_Man document, and return a pointer to it
    return CRS_ManDocument::NewL(*this);
}

// -----------------------------------------------------------------------------
// CRS_ManApplication::AppDllUid()
// Returns application UID
// -----------------------------------------------------------------------------
//
TUid CRS_ManApplication::AppDllUid() const
{
    // Return the UID for the RS_Man application
    return KUidRS_ManApp;
}

// End of File
