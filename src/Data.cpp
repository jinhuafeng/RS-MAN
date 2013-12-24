/*
 * Data.cpp
 *
 *  Created on: 2010-9-7
 *      Author: Administrator
 */
#include <coemain.h>
#include "RS_ManAppUi.h"
#include <AknAppUi.h> 
#include <eiklabel.h> 
#include <e32keys.h>
#include <akndef.h> 
#include <AknUtils.h> 
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include <E32MATH.h>
#include <RS_Man.mbg>
#include  "Data.h"
#include "Macro.h"

void CData::ConstructL()
{
    //初始化对象池
    iWoodBoardPool = new (ELeave) CWoodBoardPool();
    iMarbleBoardPool = new (ELeave) CMarbleBoardPool();
    iConveyBoardPool = new (ELeave) CConveyBoardPool();
    iStabBoardPool = new (ELeave) CStabBoardPool();
    iSpringBoardPool = new (ELeave) CSpringBoardPool();
    //
    ipBitMapPosition = new (ELeave) TBitMapPosition;
    iDrawer = new (ELeave) TDrawer;
    //根据概率生成空间对象的概率分布选取表,刚开始为0 Level
    //iProbabilityCreator.UpdateProbabilityArray(0);
    //初始化活动对象队列   ,包含九个元素
    iBoardQueue = new (ELeave) TBoardQueue();
    iBoardQueue->CreateQueueL(QUEUE_ELEMENTS_COUNT);
    InitQueue();
    //
    iDrawer->SetBitmapPositon(ipBitMapPosition);
    iDrawer->GetBitMapRect();
    //
    iMan = new (ELeave) TMan;
    iMan->SetBitMapPosition(ipBitMapPosition);
    iTouchFeedBack = MTouchFeedback::Instance();
    iTouchFeedBack->SetFeedbackEnabledForThisApp(ETrue);
    iGameState = TEnum::EControlMainMenu;
    iFloor = 0;
    iScroll = SCROLL_SPEED_HIGH;
    iVibraEnable = ETrue;
    iFramesPerSecond = KFRAMES_PER_SECOND;
    iPreviousState = TEnum::EControlMainMenu;
#ifdef  __WINS__
    _LIT(KFilePath,"c:\\data\\RS_Man\\Data.txt");
    TBuf<40> fileName(KFilePath);
    iPlayerInfo.ConstructL(fileName);
#else
    _LIT(KFilePath,"\\private\\E2A1DCB7\\Data.txt");
    TFileName oFilename(KFilePath);
    User::LeaveIfError(CompleteWithAppPath(oFilename));
    iPlayerInfo.ConstructL(oFilename);
#endif
    //获得属性值
    GetOptionValue(iPlayerInfo.GetOptionInfo());
}

CData::~CData()
{
    delete iWoodBoardPool;
    delete iMarbleBoardPool;
    delete iConveyBoardPool;
    delete iStabBoardPool;
    delete iSpringBoardPool;
    delete iMan;
    delete ipBitMapPosition;
    delete iDrawer;
    delete iBoardQueue;
    delete iFilePathWood;
    delete iFilePathCongratulations;
    delete iFilePathConvey;
    delete iFilePathDropDead;
    delete iFilePathMarble;
    delete iFilePathNormalDead;
    delete iFilePathSpring;
    delete iFilePathStab;
}

//初始化队列
void CData::InitQueue()
{
    SBoardQueue* pQueueHead = iBoardQueue->ipBoardQueue;
    SBoardQueue* pCurQueue;
    //设置第一个对象（最年轻的对象） 
    pQueueHead->pBoardObject = GetObjectFromPool(TWorldObject::WoodBoard);// GetObjectFromPoolNoNull();
    pQueueHead->pBoardObject->Reset();
    pQueueHead->pBoardObject->iIsUsed = ETrue;
    pQueueHead->pBoardObject->iCenter.iY = FIRST_CENTER_AXIS_Y + CENTER_SPAN_AXIS_Y * (QUEUE_ELEMENTS_COUNT - 1);
    //
    pCurQueue = pQueueHead->next;
    TInt iCurAxisY = FIRST_CENTER_AXIS_Y;// + CENTER_SPAN_AXIS_Y * (QUEUE_ELEMENTS_COUNT - 2);
    while (pCurQueue != pQueueHead)
    {
        //获得对象
        pCurQueue->pBoardObject = GetObjectFromPoolNoNull();
        //Reset对象
        pCurQueue->pBoardObject->Reset();
        pCurQueue->pBoardObject->iIsUsed = ETrue;
        pCurQueue->pBoardObject->iCenter.iY = iCurAxisY;
        iCurAxisY = iCurAxisY + CENTER_SPAN_AXIS_Y;
        //获得下一个
        pCurQueue = pCurQueue->next;
    }
}

TWorldObject* CData::GetObjectFromPoolNoNull()
{
    TWorldObject* pObject = NULL;
    while (pObject == NULL)
    {
        pObject = GetObjectFromPool(iProbabilityCreator.GetRadomObject());
    }
    return pObject;
}

TWorldObject* CData::GetObjectFromPool(TInt aBoradName)
{
    TWorldObject* object;
    switch (aBoradName)
    {
        case TWorldObject::WoodBoard:
        {
            object = iWoodBoardPool->GetTheNextAvaliable();
            break;
        }
        case TWorldObject::MarbleBoard:
        {
            object = iMarbleBoardPool->GetTheNextAvaliable();
            break;
        }
        case TWorldObject::StabBoard:
        {
            object = iStabBoardPool->GetTheNextAvaliable();
            break;
        }
        case TWorldObject::ConveyBoard:
        {
            object = iConveyBoardPool->GetTheNextAvaliable();
            break;
        }
        case TWorldObject::SpringBoard:
        {
            object = iSpringBoardPool->GetTheNextAvaliable();
            break;
        }
        default:
        {
            return NULL;
        }
    }
    if (object != NULL)
    {
        object->ipBitMapPosition = ipBitMapPosition;
        return object;
    }
    else
    {
        return NULL;
    }
}

void CData::ResetDataForNewGame()
{
    delete iWoodBoardPool;
    delete iMarbleBoardPool;
    delete iConveyBoardPool;
    delete iStabBoardPool;
    delete iSpringBoardPool;
    delete iMan;
    delete iBoardQueue;

    //初始化对象池
    iWoodBoardPool = new (ELeave) CWoodBoardPool();
    iMarbleBoardPool = new (ELeave) CMarbleBoardPool();
    iConveyBoardPool = new (ELeave) CConveyBoardPool();
    iStabBoardPool = new (ELeave) CStabBoardPool();
    iSpringBoardPool = new (ELeave) CSpringBoardPool();
    iMan = new (ELeave) TMan;
    iMan->SetBitMapPosition(ipBitMapPosition);
    //
    iBoardQueue = new (ELeave) TBoardQueue();
    iBoardQueue->CreateQueueL(QUEUE_ELEMENTS_COUNT);
    //根据概率生成空间对象的概率分布选取表,刚开始为0 Floor
    iProbabilityCreator.ResetAllFields();
    //重新初始化活动对象队列  
    InitQueue();
    iFloor = 0;
    iPreviousState = TEnum::EControlMainMenu;
    switch (iGameLevel)
    {
        case TEnum::EEasy:
        {
            iScroll = SCROLL_SPEED_HIGH - 1;
            break;
        }
        case TEnum::ENormal:
        {
            iScroll = SCROLL_SPEED_HIGH;
        }
        case TEnum::EHard:
        {
            iScroll = SCROLL_SPEED_HIGH + 1;
        }
    }
}
TRect CData::GetMotionRectByNum(TInt aNum)
{
    TRect rect;
    if (aNum == 0)
    {
        rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontOFF, 0);
    }
    else if (aNum == 10)
    {
        rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontMAX, 0);
    }
    else
    {
        rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontNum0, aNum);
    }
    return rect;
}
TRect CData::GetMotionRectByLevel(TEnum::TGameLevel aLevel)
{
    TRect rect;
    switch (aLevel)
    {
        case TEnum::EEasy:
        {
            rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontEasy, 0);
            break;
        }
        case TEnum::ENormal:
        {
            rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontNormal, 0);
            break;
        }
        case TEnum::EHard:
        {
            rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontHard, 0);
            break;
        }
    }
    return rect;
}

TRect CData::GetMotionRectByLayout(TEnum::TLayoutType aLayoutType)
{
    TRect rect;
    switch (aLayoutType)
    {
        case TEnum::ELeftHand:
        {
            rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontLayoutLeftHand, 0);
            break;
        }
        case TEnum::EHands:
        {
            rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontLayoutHands, 0);
            break;
        }
        case TEnum::ERightHand:
        {
            rect = ipBitMapPosition->GetPosition(TBitMapPosition::FontLayoutRightHand, 0);
            break;
        }
    }
    return rect;
}
TRect CData::GetMOtionRectByBool(TBool aBool)
{
    if (aBool)
    {
        return ipBitMapPosition->GetPosition(TBitMapPosition::FontON, 0);
    }
    else
    {
        return ipBitMapPosition->GetPosition(TBitMapPosition::FontOFF, 0);
    }
}

void CData::GetOptionValue(TInt32 iFlag)
{
    TInt temp;
    //Sound 个位
    iSoundDegree = iFlag % 10;
    //Vibra 十位
    iFlag = iFlag / 10;
    temp = iFlag % 10;
    if (temp == 0)
    {
        iVibraEnable = EFalse;
    }
    else
    {
        iVibraEnable = ETrue;
    }
    //Level 百位
    iFlag = iFlag / 10;
    temp = iFlag % 10;
    switch (temp)
    {
        case 1:
        {
            iGameLevel = TEnum::EEasy;
            break;
        }
        case 2:
        {
            iGameLevel = TEnum::ENormal;
            break;
        }
        case 3:
        {
            iGameLevel = TEnum::EHard;
            break;
        }
        default:
            break;
    }
    //Layout 千位
    iFlag = iFlag / 10;
    temp = iFlag % 10;
    switch (temp)
    {
        case 1:
        {
            iLayoutType = TEnum::ELeftHand;
            break;
        }
        case 2:
        {
            iLayoutType = TEnum::EHands;
            break;
        }
        case 3:
        {
            iLayoutType = TEnum::ERightHand;
            break;
        }
        default:
            break;
    }
}
void CData::SetFilePathNameL()
{
#ifdef  __WINS__
    _LIT(KFilePath,"c:\\data\\RS_Man\\Sounds\\Wood.wav");
    _LIT(KFilePath1,"c:\\data\\RS_Man\\Sounds\\Stab.wav");
    _LIT(KFilePath2,"c:\\data\\RS_Man\\Sounds\\Marble.wav");
    _LIT(KFilePath3,"c:\\data\\RS_Man\\Sounds\\Convey.wav");
    _LIT(KFilePath4,"c:\\data\\RS_Man\\Sounds\\NormalDead.wav");
    _LIT(KFilePath5,"c:\\data\\RS_Man\\Sounds\\DropDead.wav");
    _LIT(KFilePath6,"c:\\data\\RS_Man\\Sounds\\Spring.wav");
    _LIT(KFilePath7,"c:\\data\\RS_Man\\Sounds\\Congratulations.wav");
    iFilePathWood = new (ELeave) TFileName(KFilePath);
    iFilePathStab = new (ELeave) TFileName(KFilePath1);
    iFilePathMarble = new (ELeave) TFileName(KFilePath2);
    iFilePathConvey = new (ELeave) TFileName(KFilePath3);
    iFilePathNormalDead = new (ELeave) TFileName(KFilePath4);
    iFilePathDropDead = new (ELeave) TFileName(KFilePath5);
    iFilePathSpring = new (ELeave) TFileName(KFilePath6);
    iFilePathCongratulations = new (ELeave) TFileName(KFilePath7);
#else
    _LIT(KFilePath,"\\resource\\apps\\RS_Man\\Sounds\\Wood.wav");
    _LIT(KFilePath1,"\\resource\\apps\\RS_Man\\Sounds\\Stab.wav");
    _LIT(KFilePath2,"\\resource\\apps\\RS_Man\\Sounds\\Marble.wav");
    _LIT(KFilePath3,"\\resource\\apps\\RS_Man\\Sounds\\Convey.wav");
    _LIT(KFilePath4,"\\resource\\apps\\RS_Man\\Sounds\\NormalDead.wav");
    _LIT(KFilePath5,"\\resource\\apps\\RS_Man\\Sounds\\DropDead.wav");
    _LIT(KFilePath6,"\\resource\\apps\\RS_Man\\Sounds\\Spring.wav");
    _LIT(KFilePath7,"\\resource\\apps\\RS_Man\\Sounds\\Congratulations.wav");
    
    //
    iFilePathWood=new(ELeave)TFileName(KFilePath);
    iFilePathStab=new(ELeave)TFileName(KFilePath1);
    iFilePathMarble=new(ELeave)TFileName(KFilePath2);
    iFilePathConvey=new(ELeave)TFileName(KFilePath3);
    iFilePathNormalDead=new(ELeave)TFileName(KFilePath4);
    iFilePathDropDead=new(ELeave)TFileName(KFilePath5);
    iFilePathSpring=new(ELeave)TFileName(KFilePath6);
    iFilePathCongratulations=new(ELeave)TFileName(KFilePath7);
    //
    User::LeaveIfError(CompleteWithAppPath(*iFilePathWood));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathStab));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathMarble));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathConvey));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathNormalDead));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathDropDead));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathSpring));
    User::LeaveIfError(CompleteWithAppPath(*iFilePathCongratulations));
#endif
}

void CData::SetOptionValue()
{
    TInt32 newOption = 0;
    //千位
    newOption = iLayoutType;
    newOption *= 10;
    //百位
    newOption += iGameLevel;
    newOption *= 10;
    //十位
    if (iVibraEnable)
    {
        newOption += 1;
    }
    //各位
    newOption *= 10;
    newOption += iSoundDegree;
    iPlayerInfo.SetOptionInfo(newOption);
}
