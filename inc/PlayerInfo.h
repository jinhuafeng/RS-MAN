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
    TInt32 iNo;//����
    HBufC* iName;//����
    TInt32 iScore;
    //������¼ӵĶ��󣬵�һ����Top10����ʾʱ ����˸
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
    //��1-AWARD_PLAYER_COUNT ��No ���� ����
    void OrderByDesc();
    //�˷����Ƿ���Ƽ�¼��������Ƽ�¼����Ҫ��������
    TBool IsBrokeAwardRecord(TInt aFloor);
    void UpdatePlayerList(TInt iScore,TDesC& aNewName);
    ~TPlayerInfo();
private:
    void InitPlayerInfo();
    //void SwitchPlayerInfo(TPlayer)
public:
    //iPlayerList�е�0��Ԫ�ص�iScore�����Options��ֵ 1-8�����ǰ8��ѡ�ֵ�ֵ
    //TPlayer iPlayerArray[AWARD_PLAYER_COUNT];
    TPlayer* iPlayerList[AWARD_PLAYER_COUNT];
    HBufC* iFileName;
};
#endif /* PLAYERINFOOPRATOR_H_ */
