/*
 ============================================================================
 Name		: RS_Man.cpp
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Main application class
 ============================================================================
 */

// INCLUDE FILES
#include <eikstart.h>
#include "RS_ManApplication.h"

LOCAL_C CApaApplication* NewApplication()
{
    return new CRS_ManApplication;
}

GLDEF_C TInt E32Main()
{
    return EikStart::RunApplication(NewApplication);
}

