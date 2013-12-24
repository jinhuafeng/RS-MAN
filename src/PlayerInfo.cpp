/*
 * PlayerInfoOperator.cpp
 *
 *  Created on: 2010-9-20
 *      Author: Administrator
 */

#include "PlayerInfo.h"
#include "Macro.h"

void TPlayer::SetScoreAndName(TInt32 aScore, TDesC& aName)
{
    iIsNewPlayer=EFalse;
    iScore = aScore;
    iName = aName.Alloc();
}

TPlayer::~TPlayer()
{
    if (iName)
    {
        delete iName;
    }
    iName = NULL;
}

void TPlayer::ExternalizeL(RWriteStream& aStream)
{
    aStream.WriteInt32L(iNo);
    aStream.WriteInt32L(iName->Des().MaxLength());
    aStream << *iName;
    aStream.WriteInt32L(iScore);
}

void TPlayer::InternalizeL(RReadStream& aStream)
{
    if (iName != NULL)
    {
        delete iName;
        iName = NULL;
    }
    iNo = aStream.ReadInt32L();
    TInt32 max;
    max = aStream.ReadInt32L();
    iName = HBufC::NewL(aStream, max);
    iScore = aStream.ReadInt32L();
}
void TPlayerInfo::ConstructL(TDesC& aFileName)
{
    iFileName = aFileName.Alloc();
    InitPlayerInfo();
    //读取存档
    ReadPlayerInfo();
    //排序
    OrderByDesc();
}
//读取存档
void TPlayerInfo::ReadPlayerInfo()
{

    RFs oFs;
    if (oFs.Connect())
    {
        return;
    };
    RFileReadStream oReadStream;
    //如果打开失败 将返回一个非0值，则返回
    if (oReadStream.Open(oFs, *iFileName, EFileRead))
    {
        oFs.Close();
        return;
    }
    //
    oReadStream.PushL();
    TInt32 playerCount;
    oReadStream >> playerCount;
    for (TInt i = 0; i < playerCount; i++)
    {
        if (i < AWARD_PLAYER_COUNT)
        {
            //iPlayerArray[i].InternalizeL(oReadStream);
            iPlayerList[i]->InternalizeL(oReadStream);
        }
    }
    oReadStream.Pop();
    oReadStream.Release();
    oFs.Close();
}

//存档
void TPlayerInfo::WriterPlayerInfo()
{
    RFs oFs;
    if (oFs.Connect())
    {
        return;
    };
    RFileWriteStream oWriteStream;
    if (oWriteStream.Replace(oFs, *iFileName, EFileWrite))
    {
        oFs.Close();
        return;
    };
    oWriteStream.PushL();
    TInt32 playerCount = AWARD_PLAYER_COUNT;
    oWriteStream << playerCount;
    for (TInt i = 0; i < playerCount; i++)
    {
        if (i < AWARD_PLAYER_COUNT)
        {
            //iPlayerArray[i].ExternalizeL(oWriteStream);
            iPlayerList[i]->ExternalizeL(oWriteStream);
        }
    }
    oWriteStream.CommitL();
    oWriteStream.Pop();
    oWriteStream.Release();
    oFs.Close();
}
void TPlayerInfo::InitPlayerInfo()
{
    _LIT(KName0,"Options");
    _LIT(KName1,"Peter");
    _LIT(KName2,"Ellen");
    _LIT(KName3,"Franklin");//Hank Harry Kevin Matthew Peter Ailsa Carrie Ellen Hellen Juliana Mary Winnie
    _LIT(KName4,"Juliana");
    _LIT(KName5,"Harry");
    _LIT(KName6,"Winnie");
    _LIT(KName7,"Hank");
    _LIT(KName8,"Aaron");
    _LIT(KName9,"Kevin");
    _LIT(KName10,"Hellen");

    TBuf<MAX_NAME_LENGTH> Name0(KName0);
    TBuf<MAX_NAME_LENGTH> Name1(KName1);
    TBuf<MAX_NAME_LENGTH> Name2(KName2);
    TBuf<MAX_NAME_LENGTH> Name3(KName3);
    TBuf<MAX_NAME_LENGTH> Name4(KName4);
    TBuf<MAX_NAME_LENGTH> Name5(KName5);
    TBuf<MAX_NAME_LENGTH> Name6(KName6);
    TBuf<MAX_NAME_LENGTH> Name7(KName7);
    TBuf<MAX_NAME_LENGTH> Name8(KName8);
    TBuf<MAX_NAME_LENGTH> Name9(KName9);
    TBuf<MAX_NAME_LENGTH> Name10(KName10);
    for (TInt i = 0; i < AWARD_PLAYER_COUNT; i++)
    {
        iPlayerList[i] = new (ELeave) TPlayer;
    }
    //iPlayerList[0]->iScore=0;
    iPlayerList[0]->SetScoreAndName(DEFAULT_OPTION_VALUE, Name0);
    iPlayerList[1]->SetScoreAndName(91, Name1);
    iPlayerList[2]->SetScoreAndName(86, Name2);
    iPlayerList[3]->SetScoreAndName(64, Name3);
    iPlayerList[4]->SetScoreAndName(56, Name4);
    iPlayerList[5]->SetScoreAndName(43, Name5);
    iPlayerList[6]->SetScoreAndName(32, Name6);
    iPlayerList[7]->SetScoreAndName(26, Name7);
    iPlayerList[8]->SetScoreAndName(15, Name8);
    iPlayerList[9]->SetScoreAndName(9, Name9);
    iPlayerList[10]->SetScoreAndName(8, Name10);
}

TInt32 TPlayerInfo::GetOptionInfo()
{
    //return iPlayerArray[0].iScore;
    return iPlayerList[0]->iScore;
}
void TPlayerInfo::SetOptionInfo(TInt32 aNewOption)
{
    //iPlayerArray[0].iScore=aNewOption;
    iPlayerList[0]->iScore = aNewOption;
    WriterPlayerInfo();
}
void TPlayerInfo::OrderByDesc()
{
    TPlayer* player;
    for (TInt i = 1; i < AWARD_PLAYER_COUNT; i++)
    {
        for (TInt j = AWARD_PLAYER_COUNT - 1; j > i; j--)
        {
            if (iPlayerList[j - 1]->iScore < iPlayerList[j]->iScore)
            {
                //交换
                player = iPlayerList[j - 1];
                iPlayerList[j - 1] = iPlayerList[j];
                iPlayerList[j] = player;
            }
        }
        //
        iPlayerList[i]->iNo = i;
    }
    player = NULL;
}
//此分数是否打破纪录，如果打破纪录，需要输入姓名
TBool TPlayerInfo::IsBrokeAwardRecord(TInt aFloor)
{
    if(aFloor>iPlayerList[AWARD_PLAYER_COUNT-1]->iScore)
    {
        return ETrue;
    }
    else
    {
        return EFalse;
    }
}

//此时有人打破纪录，将新纪录加入排行榜，并重新排序
void TPlayerInfo::UpdatePlayerList(TInt iScore,TDesC& aNewName)
{
    TPlayer* player=new (ELeave) TPlayer;
    player->SetScoreAndName(iScore,aNewName);
    player->iIsNewPlayer=ETrue;
    //删除最后一名
    if(iPlayerList[AWARD_PLAYER_COUNT-1])
    {
        delete iPlayerList[AWARD_PLAYER_COUNT-1];
    }
    //
    iPlayerList[AWARD_PLAYER_COUNT-1]=player;
    OrderByDesc();
}

TPlayerInfo::~TPlayerInfo()
{
    for (TInt i = 0; i < AWARD_PLAYER_COUNT; i++)
    {
        if (iPlayerList[i])
        {
            delete iPlayerList[i];
            iPlayerList[i] = NULL;
        }
    }
    if (iFileName)
    {
        delete iFileName;
    }
    iFileName = NULL;
}
