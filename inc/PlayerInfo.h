/*
 * PlayerInfoOprator.h
 *
 *  Created on: 2010-9-20
 *      Author: Administrator
 */

#ifndef PLAYERINFOOPRATOR_H_
#define PLAYERINFOOPRATOR_H_

#include <s32file.h>
#include <s32stor.h>
#include <s32std.h>
#include "Macro.h"

class TPlayer
{
public:
    void SetScoreAndName(TInt32 aScore,TDesC& aName);
    void ExternalizeL(RWriteStream& aStream);
    void InternalizeL(RReadStream& aStream);
    ~TPlayer();
public:
    TInt32 iNo;//排名
    HBufC* iName;//姓名
    TInt32 iScore;
    //如果是新加的对象，第一次在Top10中显示时 会闪烁
    TBool iIsNewPlayer;
};

class TPlayerInfo
{
public:
    void ConstructL(TDesC& aFileName);
    void ReadPlayerInfo();
    void WriterPlayerInfo();
    TInt32 GetOptionInfo();
    void SetOptionInfo(TInt32 aNewOption);
    //从1-AWARD_PLAYER_COUNT 按No 降序 排序
    void OrderByDesc();
    //此分数是否打破纪录，如果打破纪录，需要输入姓名
    TBool IsBrokeAwardRecord(TInt aFloor);
    void UpdatePlayerList(TInt iScore,TDesC& aNewName);
    ~TPlayerInfo();
private:
    void InitPlayerInfo();
    //void SwitchPlayerInfo(TPlayer)
public:
    //iPlayerList中第0个元素的iScore存的是Options的值 1-8存的是前8名选手的值
    //TPlayer iPlayerArray[AWARD_PLAYER_COUNT];
    TPlayer* iPlayerList[AWARD_PLAYER_COUNT];
    HBufC* iFileName;
};
#endif /* PLAYERINFOOPRATOR_H_ */
