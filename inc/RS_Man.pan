/*
 ============================================================================
 Name		: RS_Man.pan
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : This file contains panic codes.
 ============================================================================
 */

#ifndef __RS_MAN_PAN__
#define __RS_MAN_PAN__

/** RS_Man application panic codes */
enum TRS_ManPanics
{
    ERS_ManUi = 1,
    EBoardPoolExhausted = 2
// add further panics here
};

inline void Panic(TRS_ManPanics aReason)
{
    _LIT(applicationName, "RS_Man");
    User::Panic(applicationName, aReason);
}

#endif // __RS_MAN_PAN__
