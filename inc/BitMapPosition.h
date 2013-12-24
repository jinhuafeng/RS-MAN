/*
 * BitMapPosition.h
 *
 *  Created on: 2010-6-29
 *      Author: Administrator
 */

#ifndef BITMAPPOSITION_H_
#define BITMAPPOSITION_H_
#include <e32std.h>
#include <e32base.h>

class TBitMapPosition
{
public:
    enum BitMapName
    {
        Left = 0,
        LeftRed = 4,
        Right = 8,
        RightRed = 12,
        LeftJump = 16,
        LeftJumpRed = 20,
        Jump = 24,
        JumpRed = 28,
        RightJump = 32,
        RightJumpRed = 36,
        Stand = 40,
        StandRed = 41,
        UpLimit = 42,
        WoodBoard = 43,
        ConveyBoardRight = 44,
        ConveyBoardLeft = 48,
        MarbleBoard = 52,
        SpringBoard = 58,
        Wall = 65,
        StabBoard = 67,
        TouchLeft = 68,
        TouchLeftDown = 69,
        TouchCenterBorder = 70,
        TouchCenterInner = 71,
        TouchCenterInnerDown = 72,
        //Font
        FontStart = 73,
        FontResume = 74,
        FontSound = 75,
        FontHelp = 76,
        FontAward = 77,
        FontNewGame = 78,
        FontVibra = 79,
        FontExit = 80,
        FontMainMenu = 81,
        FontAbout = 82,
        FontReturn = 83,
        FontOption = 84,
        FontLevel = 85,
        //
        HighlightEdge = 86,
        HighlightReturnEdge = 87,

        FontEasy = 88,
        FontNormal = 89,
        FontHard = 90,
        FontLeftArrow = 91,
        FontRightArrow = 92,
        FontLayout = 93,
        FontLayoutLeftHand = 94,
        FontLayoutHands = 95,
        FontNum0 = 96,
        FontOFF=106,
        FontMAX=107,
        FontON=108,
        FontLayoutRightHand=109,
        FontReturnUp=110,
        FontReturnDown=111,
        EGameTitle=112,
        EFontTitleNum0=113,
        ELifeValue=123
    };
    //BitMapName iBitMapName;
public:
    TBitMapPosition();
    TRect GetPosition(TInt aIndex, TInt aFrame);
private:
    TFixedArray<TRect, 130> iPositionArray;
};
#endif /* BITMAPPOSITION_H_ */
