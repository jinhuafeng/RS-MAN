/*
 * ActionAnalyst.cpp
 *
 *  Created on: 2010-8-10
 *      Author: panda
 */

#include "ActionAnalyst.h"

TActionAnalyst::TActionAnalyst()
{
    //iLeftNav.SetRect(0, 531, 124, 639);
    //iRightNav.SetRect(125, 531, 249, 639);
    //iPauseNav.SetRect(250, 531, 359, 639);
    //iPauseNav.SetRect(125, 531, 234, 639);
    //iRightNav.SetRect(235, 531, 359, 639);
    //
    iFramesAdd.SetRect(0, 70, 179, 399);
    iFramesDesc.SetRect(0, 400, 179, 530);
    iScrollAdd.SetRect(180, 70, 359, 399);
    iScrollDesc.SetRect(180, 400, 359, 530);

}
void TActionAnalyst::SetActionAnalystByLayoutType(TEnum::TLayoutType iLayoutType)
{
    switch (iLayoutType)
    {
        case TEnum::ELeftHand:
        {
            iLeftNav.SetRect(0, 531, 124, 639);
            iRightNav.SetRect(125, 531, 250, 639);
            iPauseNav.SetRect(251, 531, 359, 639);
            break;
        }
        case TEnum::EHands:
        {
            iLeftNav.SetRect(0, 531, 124, 639);
            iPauseNav.SetRect(125, 531, 233, 639);
            iRightNav.SetRect(234, 531, 359, 639);
            break;
        }
        case TEnum::ERightHand:
        {
            iPauseNav.SetRect(0, 531,107, 639);
            iLeftNav.SetRect(108, 531, 233, 639);
            iRightNav.SetRect(234, 531, 349, 639);
            break;
        }
    }
}

TEnum::TGameKey TActionAnalyst::GetGameKey(TPoint aPoint)
{
    if (iLeftNav.Contains(aPoint))
    {
        return TEnum::EKeyLeft;
    }
    if (iRightNav.Contains(aPoint))
    {
        return TEnum::EKeyRight;
    }
    if (iPauseNav.Contains(aPoint))
    {
        return TEnum::EKeyPause;
    }
    if (iFramesAdd.Contains(aPoint))
    {
        return TEnum::EFramesAdd;
    }
    if (iFramesDesc.Contains(aPoint))
    {
        return TEnum::EFramesDesc;
    }
    if (iScrollAdd.Contains(aPoint))
    {
        return TEnum::EScrollAdd;
    }
    if (iScrollDesc.Contains(aPoint))
    {
        return TEnum::EScrollDesc;
    }
    return TEnum::EKeyNone;
}
