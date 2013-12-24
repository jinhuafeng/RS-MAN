/*
 * Data.h
 *
 *  Created on: 2010-9-3
 *      Author: Administrator
 */

#ifndef DATA_H_
#define DATA_H_

#include <W32STD.H> 
#include <aknutils.h>
#include "WorldPoint.h"
#include "BitMapPosition.h"
#include "Enum.h"
#include "Drawer.h"
#include "BoardPool.h"
#include "BoardQueue.h"
#include "ProbabilityTable.h"
#include "MotionElement.h"
#include <touchfeedback.h>
#include <touchlogicalfeedback.h>
#include "PlayerInfo.h"
//#include "hwrmvibra.h"

typedef CObjectPool<TWoodBoard, 8> CWoodBoardPool;
typedef CObjectPool<TMarbleBoard, 8> CMarbleBoardPool;
typedef CObjectPool<TConveyBoard, 8> CConveyBoardPool;
typedef CObjectPool<TStabBoard, 8> CStabBoardPool;
typedef CObjectPool<TSpringBoard, 8> CSpringBoardPool;

class CData
{
public:
    void ConstructL();
    TWorldObject* GetObjectFromPoolNoNull();
    TWorldObject* GetObjectFromPool(TInt aBoradName);
    //
    TRect GetMotionRectByNum(TInt aNum);
    TRect GetMotionRectByLevel(TEnum::TGameLevel aLevel);
    TRect GetMotionRectByLayout(TEnum::TLayoutType);
    TRect GetMOtionRectByBool(TBool aBool);
    void GetOptionValue(TInt32 iFlag);
    void SetOptionValue();
    //
    ~CData();
    void ResetDataForNewGame();
    void SetFilePathNameL();
private:
    void InitQueue();
public:
    TEnum::TGameState iGameState;
    TEnum::TGameState iPreviousState;
    TEnum::TGameLevel iGameLevel;
    TEnum::TLayoutType iLayoutType;
    TBitMapPosition* ipBitMapPosition;
    MTouchFeedback* iTouchFeedBack;
    CWsBitmap* iResourceMap;
    TDrawer* iDrawer;
    TInt iScroll;
    //TInt iScore;
    //TBool iSoundEnable;
    TBool iVibraEnable;
    TInt iSoundDegree;
    //TInt iVibraDegree;
    TMan* iMan;
    CWoodBoardPool* iWoodBoardPool;
    CMarbleBoardPool* iMarbleBoardPool;
    CConveyBoardPool* iConveyBoardPool;
    CStabBoardPool* iStabBoardPool;
    CSpringBoardPool* iSpringBoardPool;
    //
    TProbabilityCreator iProbabilityCreator;
    TBoardQueue* iBoardQueue;
    TInt iFramesPerSecond;
    //TInt iLives;
    //iLevel是一个内部量，用于设置游戏难度，分数会影响到Level 然后 Level进一步会影响到概率分布表
    //最高7级，每过5个Board涨1分，每增加10分 Level 升一级
    //iFloor为游戏中的层数，每过5个Boards iFloor加一。但iFloor/30==0,游戏iCroll将加1
    TInt iFloor;
    TPlayerInfo iPlayerInfo;
    //文件名
    TFileName* iFilePathWood;
    TFileName* iFilePathMarble;
    TFileName* iFilePathConvey;
    TFileName* iFilePathStab;
    TFileName* iFilePathSpring;
    TFileName* iFilePathDropDead;
    TFileName* iFilePathNormalDead;
    TFileName* iFilePathCongratulations;
    /*
     * CWoodBoardPool* iWoodBoardPool;
    CMarbleBoardPool* iMarbleBoardPool;
    CConveyBoardPool* iConveyBoardPool;
    CStabBoardPool* iStabBoardPool;
    CSpringBoardPool* iSpringBoardPool;
    */
};
#endif /* DATA_H_ */
