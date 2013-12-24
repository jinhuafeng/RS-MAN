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
    //iLevel��һ���ڲ���������������Ϸ�Ѷȣ�������Ӱ�쵽Level Ȼ�� Level��һ����Ӱ�쵽���ʷֲ���
    //���7����ÿ��5��Board��1�֣�ÿ����10�� Level ��һ��
    //iFloorΪ��Ϸ�еĲ�����ÿ��5��Boards iFloor��һ����iFloor/30==0,��ϷiCroll����1
    TInt iFloor;
    TPlayerInfo iPlayerInfo;
    //�ļ���
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
