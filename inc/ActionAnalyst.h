/*
 * ActionAnalyst.h
 *
 *  Created on: 2010-8-10
 *      Author: panda
 */

#ifndef ACTIONANALYST_H_
#define ACTIONANALYST_H_
#include <e32std.h>
#include <e32base.h>
#include "Enum.h"
class TActionAnalyst
{
public:
    TActionAnalyst();
    TEnum::TGameKey GetGameKey(TPoint aPoint);
    void SetActionAnalystByLayoutType(TEnum::TLayoutType);
public:
    //ÐéÄâ·½Ïò¼ü
    TRect iLeftNav;
    TRect iPauseNav;
    TRect iRightNav;
    //
    TRect iFramesAdd;
    TRect iFramesDesc;
    TRect iScrollAdd;
    TRect iScrollDesc;
};
#endif /* ACTIONANALYST_H_ */
