/*
 * BitMapPosition.cpp
 *
 *  Created on: 2010-6-29
 *      Author: Administrator
 */

#include"BitMapPosition.h"

TRect TBitMapPosition::GetPosition(TInt aIndex, TInt aFrame)
{
    TInt offset = aIndex + aFrame;
    TRect rect;
    //rect.SetRect(0,0,0,0);
    if (offset > -1 && offset < 130)
    {
        rect = iPositionArray[offset];
    }
    return rect;
}
;

TBitMapPosition::TBitMapPosition()
{
    //set position
    //Left
    iPositionArray[0].SetRect(1, 112, 37, 150);
    iPositionArray[1].SetRect(44, 112, 70, 150);
    iPositionArray[2].SetRect(80, 112, 116, 150);
    iPositionArray[3].SetRect(124, 112, 150, 150);
    //LeftRed
    iPositionArray[4].SetRect(156, 112, 195, 150);
    iPositionArray[5].SetRect(198, 112, 228, 150);
    iPositionArray[6].SetRect(237, 112, 276, 150);
    iPositionArray[7].SetRect(481, 96, 514, 134);
    //Right
    iPositionArray[8].SetRect(5, 152, 31, 190);
    iPositionArray[9].SetRect(39, 152, 75, 190);
    iPositionArray[10].SetRect(85, 152, 111, 190);
    iPositionArray[11].SetRect(118, 152, 154, 190);
    //RightRed
    iPositionArray[12].SetRect(157, 152, 194, 190);
    iPositionArray[13].SetRect(203, 152, 232, 190);
    iPositionArray[14].SetRect(237, 152, 276, 190);
    iPositionArray[15].SetRect(481, 136, 514, 174);
    //LeftJump
    iPositionArray[16].SetRect(2, 192, 32, 230);
    iPositionArray[17].SetRect(41, 192, 72, 230);
    iPositionArray[18].SetRect(82, 192, 112, 230);
    iPositionArray[19].SetRect(124, 192, 153, 230);
    //LeftJumpRed
    iPositionArray[20].SetRect(159, 192, 191, 230);
    iPositionArray[21].SetRect(197, 192, 231, 230);
    iPositionArray[22].SetRect(239, 192, 271, 230);
    iPositionArray[23].SetRect(481, 176, 514, 214);
    //Jump
    iPositionArray[24].SetRect(0, 232, 37, 270);
    iPositionArray[25].SetRect(40, 232, 77, 270);
    iPositionArray[26].SetRect(80, 232, 116, 270);
    iPositionArray[27].SetRect(122, 232, 154, 270);
    //JumpRed
    iPositionArray[28].SetRect(158, 232, 194, 270);
    iPositionArray[29].SetRect(198, 232, 234, 270);
    iPositionArray[30].SetRect(238, 232, 275, 270);
    iPositionArray[31].SetRect(481, 216, 514, 254);
    //RightJump
    iPositionArray[32].SetRect(5, 272, 35, 310);
    iPositionArray[33].SetRect(45, 272, 76, 310);
    iPositionArray[34].SetRect(85, 272, 115, 310);
    iPositionArray[35].SetRect(125, 272, 154, 310);
    //RightJumpRed
    iPositionArray[36].SetRect(161, 272, 193, 310);
    iPositionArray[37].SetRect(201, 272, 235, 310);
    iPositionArray[38].SetRect(242, 272, 273, 310);
    iPositionArray[39].SetRect(481, 256, 514, 293);
    //Stand
    iPositionArray[40].SetRect(519, 97, 556, 133);
    //StandRed
    iPositionArray[41].SetRect(518, 136, 556, 174);
    //UpLimit
    iPositionArray[42].SetRect(12, 368, 371, 383);
    //WoodBoard
    iPositionArray[43].SetRect(288, 0, 383, 15);
    //ConveyBelt
    iPositionArray[44].SetRect(288, 16, 383, 31);
    iPositionArray[45].SetRect(288, 32, 383, 47);
    iPositionArray[46].SetRect(288, 48, 383, 63);
    iPositionArray[47].SetRect(288, 64, 383, 79);
    iPositionArray[48].SetRect(288, 80, 383, 95);
    iPositionArray[49].SetRect(288, 96, 383, 111);
    iPositionArray[50].SetRect(288, 112, 383, 127);
    iPositionArray[51].SetRect(288, 128, 383, 143);
    //MarbleBoard
    iPositionArray[52].SetRect(288, 154, 383, 169);
    iPositionArray[53].SetRect(288, 183, 383, 212);
    iPositionArray[54].SetRect(288, 216, 383, 251);
    iPositionArray[55].SetRect(288, 254, 383, 285);
    iPositionArray[56].SetRect(288, 288, 383, 323);
    iPositionArray[57].SetRect(288, 327, 383, 356);
    //SpringBoard
    iPositionArray[58].SetRect(384, 208, 479, 230);
    iPositionArray[59].SetRect(384, 233, 479, 254);
    iPositionArray[60].SetRect(384, 259, 479, 278);
    iPositionArray[61].SetRect(384, 285, 479, 302);
    iPositionArray[62].SetRect(384, 311, 479, 326);
    iPositionArray[63].SetRect(384, 337, 479, 351);
    iPositionArray[64].SetRect(384, 352, 479, 363);
    //Wall
    iPositionArray[65].SetRect(512, 0, 527, 383);
    iPositionArray[66].SetRect(0, 0, 1, 1);
    //StabBoard
    iPositionArray[67].SetRect(384, 369, 479, 399);
    //方向键
    //左箭头
    iPositionArray[68].SetRect(0, 0, 124, 108);
    //左箭头按下
    iPositionArray[69].SetRect(125, 0, 249, 108);
    //暂停键边缘竖线
    iPositionArray[70].SetRect(250, 0, 250, 108);
    //暂停键中间
    iPositionArray[71].SetRect(251, 0, 251, 108);
    //暂停键按下时中间
    iPositionArray[72].SetRect(253, 0, 253, 108);
    //FontStart=73,
    iPositionArray[73].SetRect(0, 401, 119, 440);
    //FontResume=74,
    iPositionArray[74].SetRect(121, 401, 280, 440);
    //FontSound=75,
    iPositionArray[75].SetRect(0, 524, 99, 553);
    //FontHelp=76,
    iPositionArray[76].SetRect(282, 401, 361, 440);
    //FontAward=77,
    iPositionArray[77].SetRect(0, 442, 108, 481);
    //FontNewGame=78,
    iPositionArray[78].SetRect(128, 442, 327, 481);
    //FontVibra=79,
    iPositionArray[79].SetRect(365, 524, 445, 553);
    //FontExit=80,
    iPositionArray[80].SetRect(329, 442, 416, 481);
    //FontMainMenu=81,
    iPositionArray[81].SetRect(0, 483, 223, 522);
    //FontAbout=82,
    iPositionArray[82].SetRect(225, 483, 349, 522);
    //FontReturn=83,
    iPositionArray[83].SetRect(351, 483, 498, 522);
    //FontOption=84,
    iPositionArray[84].SetRect(418, 442, 549, 481);
    //FontDifficulty=85
    iPositionArray[85].SetRect(447, 524, 527, 553);
    //HighlightEdge
    iPositionArray[86].SetRect(480, 0, 519, 54);
    //HighlightReturnEdge
    iPositionArray[87].SetRect(520, 0, 559, 54);

    //FontEasy = 88,
    iPositionArray[88].SetRect(301, 524, 363, 553);
    //FontNormal = 89,
    iPositionArray[89].SetRect(195, 524, 299, 553);
    //FontHard = 90,
    iPositionArray[90].SetRect(220, 555, 289, 584);
    //FontLeftArrow = 91,
    iPositionArray[91].SetRect(481, 55, 519, 94);
    //FontRightArrow = 92,
    iPositionArray[92].SetRect(521, 55, 559, 94);
    //FontLayout = 93,
    iPositionArray[93].SetRect(101, 524, 193, 553);
    //FontLayoutSingleHand = 94,
    iPositionArray[94].SetRect(363, 401, 444, 426);
    //FontLayoutDoubleHand = 95,
    iPositionArray[95].SetRect(446, 401, 527, 426);
    //FontNum0-9 = 96
    iPositionArray[96].SetRect(0, 555, 20, 584);
    iPositionArray[97].SetRect(22, 555, 42, 584);
    iPositionArray[98].SetRect(44, 555, 64, 584);
    iPositionArray[99].SetRect(66, 555, 86, 584);
    iPositionArray[100].SetRect(88, 555, 108, 584);
    iPositionArray[101].SetRect(110, 555, 130, 584);
    iPositionArray[102].SetRect(132, 555, 152, 584);
    iPositionArray[103].SetRect(154, 555, 174, 584);
    iPositionArray[104].SetRect(176, 555, 196, 584);
    iPositionArray[105].SetRect(198, 555, 218, 584);
    iPositionArray[106].SetRect(291, 555, 345, 584);
    iPositionArray[107].SetRect(347, 555, 412, 584);
    iPositionArray[108].SetRect(414, 555, 453, 584);
    iPositionArray[109].SetRect(455, 559, 536, 584);
    //
    iPositionArray[110].SetRect(386, 93, 464, 147);
    iPositionArray[111].SetRect(386, 148, 464, 202);
    //
    iPositionArray[112].SetRect(0, 586, 359, 645);
    //Title 0-9
    iPositionArray[113].SetRect(0, 320, 20, 349);
    iPositionArray[114].SetRect(22, 320, 42, 349);
    iPositionArray[115].SetRect(44, 320, 64, 349);
    iPositionArray[116].SetRect(66, 320, 86, 349);
    iPositionArray[117].SetRect(88, 320, 108, 349);
    iPositionArray[118].SetRect(110, 320, 130, 349);
    iPositionArray[119].SetRect(132, 320, 152, 349);
    iPositionArray[120].SetRect(154, 320, 174, 349);
    iPositionArray[121].SetRect(176, 320, 196, 349);
    iPositionArray[122].SetRect(198, 320, 218, 349);
    //
    iPositionArray[123].SetRect(384, 0, 398, 21);
    iPositionArray[124].SetRect(400, 0, 429, 21);
    iPositionArray[125].SetRect(431, 0, 476, 21);
    iPositionArray[126].SetRect(384, 23, 444, 44);
    iPositionArray[127].SetRect(384, 46, 460, 67);
    iPositionArray[128].SetRect(384, 69, 475, 90);
}

