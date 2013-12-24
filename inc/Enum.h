/*
 * Enum.h
 *
 *  Created on: 2010-8-10
 *      Author: panda
 */

#ifndef ENUM_H_
#define ENUM_H_

class TEnum
{
public:
    enum TGameKey
    {
        EKeyLeft,
        EKeyRight,
        EKeyPause,
        EKeyNone,
        EFramesAdd,
        EFramesDesc,
        EScrollAdd,
        EScrollDesc,
        EKeyMaxVirtualKey
    };
    enum TGameState
    {
        EPlaying, 
        EWaitingStart,
        EGameOver,
        EControlMainMenu,
        EControlHelp,
        EControlAbout,
        EControlOption,
        EControlAward,
        EControlPaused,
        EControlExit
    };
    enum TManActionState
    {
        ELeft,
        ERight,
        EStand,
        ELeftJump,
        ERightJump,
        EJump,
        ELeftRed,
        ERightRed,
        EStandRed,
        ELeftJumpRed,
        ERightJumpRed,
        EJumpRed
    };
    enum TCollisionState
    {
        ECollisionWood, ECollisionMarble, ECollisionConvey, ECollisionStab, ECollisionSpring, EFree
    };
    enum TButtonState
    {
        EButtonEnterPosition,
        EButtonNormalDisplay
    };
    enum TGameLevel
    {
        EEasy=1,
        ENormal=2,
        EHard=3
    };
    enum TLayoutType
    {
        ELeftHand=1,
        EHands=2,
        ERightHand=3
    };
};

#endif /* ENUM_H_ */
