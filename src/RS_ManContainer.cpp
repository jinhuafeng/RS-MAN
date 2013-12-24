/*
 ============================================================================
 Name		: RS_ManAppView.cpp
 Author	  : jinhuafeng
 Copyright   : RS-Man Version 1.0
 Build v20100730_60 

 Copyright (c) 2009 Jinhuafeng . All rights reserved.
 Description : Application view implementation
 ============================================================================
 */

// INCLUDE FILES
#include <coemain.h>
#include "RS_ManContainer.h"

#include <eiklabel.h>  // for example label control
#include <e32keys.h>
#include <akndef.h> //for KEikDynamicLayoutVariantSwitch
#include <AknUtils.h> //for layoututils
#include <coemain.h>
#include <eikenv.h>
#include <eikdef.h>
#include <E32MATH.h>
#include <MdaAudioSamplePlayer.h>
#include "CGfxTimer.h"
#include <RS_Man.mbg>
#include <RS_Man_0xE2A1DCB7.rsg>
//#include <RS_Man.rsg>
#include "RS_ManAppUi.h"

#include  "Macro.h"

CRS_ManContainer::~CRS_ManContainer()
{
    delete iBackupBitmap;
    delete iGfxTimer;
    delete iBitmapDevice;
    delete iBitmapGc;
    delete iBackGround;
    delete iBitmapNum;

    delete iWoodPlayer;
    delete iStabPlayer;
    delete iMarblePlayer;
    delete iConveyPlayer;
    delete iNormalDeadPlayer;
    delete iDropDeadPlayer;
    delete iSpringPlayer;
    delete iSpringPlayer2;
    delete iCongratulationPlayer;
    delete iCallMonitor;
    if (iTelephoneState)
    {
        delete iTelephoneState;
    }
    //if (iEditor)
    //{
    //    delete iEditor;
    //}
}

void CRS_ManContainer::GetDataObject(CData* aData)
{
    iData = aData;
}

void CRS_ManContainer::Draw(const TRect& aRect) const
{
    CWindowGc& gc = SystemGc();
    gc.BitBlt(aRect.iTl, iBackupBitmap, aRect);
    //iEditor->TextView()->DrawL(iEditor->Rect(), gc)
}

void CRS_ManContainer::SizeChanged()
{
    //if (iEditor)
    //{
    //    iEditor->SetExtent(TPoint(10, 180), iEditor->MinimumSize());
    //}
    DrawNow();
}

void CRS_ManContainer::HandlePointerEventL(const TPointerEvent& aPointerEvent)
{
    CCoeControl::HandlePointerEventL(aPointerEvent);
    //先判断可能的来电事件
    if (iCallStatus == CTelephony::EStatusRinging)
    {
        iData->iGameState = TEnum::EControlPaused;
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        return;
    }
    //分析其它状态
    if (iData->iGameState == TEnum::EPlaying)
    {
        switch (aPointerEvent.iType)
        {
            case TPointerEvent::EButton1Down:
            {
                iGameKey = iActionAnalyst.GetGameKey(aPointerEvent.iPosition);
                break;
            }
            case TPointerEvent::EButton1Up:
            {
                iGameKey = TEnum::EKeyNone;
                break;
            }
            default:
            {
                break;
            }
        }

    }
    else if (iData->iGameState == TEnum::EControlAward && (iNormalDeadPlayer->iIsPlayCompleted
        || iDropDeadPlayer->iIsPlayCompleted))
    {
        //游戏结束
        Congratulation();
        //
        //iData->ResetDataForNewGame();
        ReportEventL(MCoeControlObserver::EEventStateChanged);
        return;
    }

    //处理暂停

    if (iGameKey == TEnum::EKeyPause)
    {
        iGfxTimer->Pause();
        iData->iGameState = TEnum::EControlPaused;
        ReportEventL(MCoeControlObserver::EEventStateChanged);
    }

    //HandleDebugGameKey();
}

//Man dead 以后，还没切换到Award以前，看是否需要祝贺
void CRS_ManContainer::Congratulation()
{
    if (iData->iPlayerInfo.IsBrokeAwardRecord(iData->iFloor))
    {
        iGfxTimer->Pause();
        iCongratulationPlayer->Play();
        TBuf<30> oName;
        TBuf<30> oTitle(_L("Enter your name:"));
        CAknTextQueryDialog* oDlg = new (ELeave) CAknTextQueryDialog(oName, oTitle);
        oDlg->PrepareLC(R_DEMO_DATA_QUERY);
        oDlg->SetMaxLength(15);
        if (oDlg->RunLD())
        {
            if (oName.Length() > 0)
            {
                iData->iPlayerInfo.UpdatePlayerList(iData->iFloor, oName);
            }
            // ok pressed, text is the descriptor containing the entered text // in the editor.
        }
    }
}

void CRS_ManContainer::ConstructL(const TRect& aRect, CData* aData)
{
    iData = aData;
    CreateWindowL();
    SetBlank();
    SetRect(aRect);

    //初始化BitMap变量
    iBackupBitmap = new (ELeave) CWsBitmap(iCoeEnv->WsSession());
    iBackupBitmap->Create(Rect().Size(), EColor16M);
    iBitmapDevice = CFbsBitmapDevice::NewL(iBackupBitmap);
    User::LeaveIfError(iBitmapDevice->CreateContext(iBitmapGc));
    //初始化心跳包
    //iFramesPerSecond = KFRAMES_PER_SECOND;
    //iScroll = SCROLL_SPEED_HIGH;
    iGfxTimer = new (ELeave) CGfxTimer(*this, NULL);
    iGfxTimer->ConstructL();
    //iWoodPlayer = CAudioPlayer::NewL(_L("c:\\data\\RS_Man\\Sounds\\Wood.wav"), iData->iSoundDegree);
    iWoodPlayer = CAudioPlayer::NewL(*iData->iFilePathWood, iData->iSoundDegree);
    iStabPlayer = CAudioPlayer::NewL(*iData->iFilePathStab, iData->iSoundDegree);
    iMarblePlayer = CAudioPlayer::NewL(*iData->iFilePathMarble, iData->iSoundDegree);
    iConveyPlayer = CAudioPlayer::NewL(*iData->iFilePathConvey, iData->iSoundDegree);
    iNormalDeadPlayer = CAudioPlayer::NewL(*iData->iFilePathNormalDead, iData->iSoundDegree);
    iDropDeadPlayer = CAudioPlayer::NewL(*iData->iFilePathDropDead, iData->iSoundDegree);
    iSpringPlayer = CAudioPlayer::NewL(*iData->iFilePathSpring, iData->iSoundDegree);
    iSpringPlayer2 = CAudioPlayer::NewL(*iData->iFilePathSpring, iData->iSoundDegree);
    iCongratulationPlayer = CAudioPlayer::NewL(*iData->iFilePathCongratulations, iData->iSoundDegree);
    iSpringSoundSwitch = EFalse;
    iGfxTimer->StartPulse(KONE_SECOND_IN_MICRO_SECONDS / iData->iFramesPerSecond);
    iBitmapNum = new (ELeave) TBitmapNum;
    iBitmapNum->SetOriginNum(iData->iFloor, iData);
    iActionAnalyst.SetActionAnalystByLayoutType(iData->iLayoutType);
    iGameKey = TEnum::EKeyNone;
    iTicks = 0;
    //初始化Man
    iIsFlagDelete = EFalse;
    TRAPD(err3, iBackGround= iEikonEnv->CreateBitmapL(_L("\\resource\\apps\\RS_Man.mbm"),EMbmRs_manBackground));
    ActivateL();
    iCallMonitor = CCallMonitor::NewL(*this);
    iCallStatus = CTelephony::EStatusUnknown;
}

void CRS_ManContainer::SetGameState()
{
    iWoodBoardPool = iData->iWoodBoardPool;
    iMarbleBoardPool = iData->iMarbleBoardPool;
    iConveyBoardPool = iData->iConveyBoardPool;
    iStabBoardPool = iData->iStabBoardPool;
    iSpringBoardPool = iData->iSpringBoardPool;
    //ipBitMapPosition = iData->ipBitMapPosition;
    iMan = iData->iMan;
    iResourceMap = iData->iResourceMap;
    //iGfxTimer->StartPulse(KONE_SECOND_IN_MICRO_SECONDS / iData->iFramesPerSecond);
}

void CRS_ManContainer::GfxTimerFiredL(TInt /*aId*/)
{
    //先判断可能的来电事件,如果有来电，则触发 虚拟触摸事件，然后到暂停界面
    if (iCallStatus == CTelephony::EStatusRinging)
    {
        TRawEvent lEventDown;
        lEventDown.Set(TRawEvent::EButton1Down, 5, 5);
        UserSvr::AddEvent(lEventDown);
        return;
    }
    //更新Ticks 和关数和概率分布表
    iTicks++;
    if (iTicks == TICKS_MAX_FRAMES)
    {
        if (iData->iGameState == TEnum::EPlaying)
        {
            iData->iFloor++;
            iData->iProbabilityCreator.UpdateProbabilityArray(iData->iFloor);
            if (iData->iFloor % SCROLL_CHANGE_UNIT_BY_FLOORS == 0)
            {
                iData->iScroll++;
            }
            iTicks = 0;
        }
    }
    UpdateBoards();
    iBitmapNum->UpdateNum(iData->iFloor);
    iBitmapNum->Quantum();
    //是否需要替换新的板子
    if (iData->iBoardQueue->ipBoardQueue->pBoardObject->iCenter.iY < Y_AXIS_REPLACE_POSITION + 2)
    {
        iData->iBoardQueue->UpdateQueue(iData->GetObjectFromPoolNoNull());
    }
    DrawGame();
    HandleManMain();
    //DrawIndicator();
    DrawNow();
}

void CRS_ManContainer::DrawGame()
{
    //iBitmapGc->Reset();
    //iBitmapGc->SetBrushColor(KRgbBlack);
    //Clear 2010-9-17被注释掉
    //iBitmapGc->Clear();
    if (iBackGround)
    {
        //TPoint bitmapOffset = Rect().Size().AsPoint() - iBackGround->SizeInPixels().AsPoint();
        //iBitmapGc->BitBlt(bitmapOffset, iBackGround);
        iData->iDrawer->DrawBackground(iBackupBitmap, iBackGround);
    }
    SBoardQueue* pHead = iData->iBoardQueue->ipBoardQueue;
    SBoardQueue* pCur = pHead;
    do
    {
        pCur->pBoardObject->Draw(iBackupBitmap, iResourceMap);
        pCur = pCur->next;
    } while (pCur != pHead);
    //
    iData->iDrawer->Draw(iBackupBitmap, iResourceMap, iGameKey, iData->iLayoutType);
    iData->iDrawer->DrawUpLimitStab(iBackupBitmap, iResourceMap);
    iData->iDrawer->DrawTitleBackground(iBackupBitmap, iResourceMap);
    iData->iDrawer->DrawLifeValue(iBackupBitmap, iResourceMap, iData->iMan->iLifeValue);
    DrawReturnArrow();
    iBitmapNum->Draw(iBackupBitmap, iResourceMap);

}
void CRS_ManContainer::DrawReturnArrow()
{
    TRect rect;
    if (iGameKey != TEnum::EKeyPause)
    {
        rect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontReturnUp, 0);
        iData->iDrawer->DrawReturnArrow(iBackupBitmap, iResourceMap, iActionAnalyst.iPauseNav, rect);
        return;
    }
    else
    {
        rect = iData->ipBitMapPosition->GetPosition(TBitMapPosition::FontReturnDown, 0);
        iData->iDrawer->DrawReturnArrow(iBackupBitmap, iResourceMap, iActionAnalyst.iPauseNav, rect);
        return;
    }
}
//更新Boards
void CRS_ManContainer::UpdateBoards()
{
    //Update Boards
    //TWorldObject* object;
    SBoardQueue* pHead = iData->iBoardQueue->ipBoardQueue;
    SBoardQueue* pCur = pHead;
    do
    {
        pCur->pBoardObject->Quantum(iData->iScroll);
        pCur = pCur->next;
    } while (pCur != pHead);

}
void CRS_ManContainer::FocusChanged(TDrawNow aDrawNow)
{
    //SetPaused(!IsFocused());
    if (aDrawNow)
    {
        DrawNow();
    }
}

void CRS_ManContainer::SetPaused(TBool aState)
{
    if (aState)
    {
        iGfxTimer->Pause();
    }
    else
    {
        iGfxTimer->ReStart();
    }
}

void CRS_ManContainer::ResetGame()
{

}

TInt CRS_ManContainer::CountComponentControls() const
{
    return 0;
}

void CRS_ManContainer::HandleResourceChange(TInt aType)
{
    CCoeControl::HandleResourceChange(aType);
    if (aType == KEikDynamicLayoutVariantSwitch)
    {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EApplicationWindow, rect);
        SetRect(rect);
        //TRAPD(err,RecreateBitmapsL());
        //if (err)
        //   User::Exit(err);
    }
}

CCoeControl* CRS_ManContainer::ComponentControl(TInt aIndex) const
{
    return NULL;
}

TKeyResponse CRS_ManContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
{
    if (aType == EEventKey)
    {
        iGfxTimer->Pause();
        iData->iGameState = TEnum::EControlPaused;
        ReportEventL(MCoeControlObserver::EEventStateChanged);
    }
    return EKeyWasNotConsumed;
}

void CRS_ManContainer::AddFrame()
{
    iData->iFramesPerSecond++;
    iGfxTimer->ChangeinterVal(KONE_SECOND_IN_MICRO_SECONDS / iData->iFramesPerSecond);
}

void CRS_ManContainer::DescFrame()
{
    iData->iFramesPerSecond--;
    iGfxTimer->ChangeinterVal(KONE_SECOND_IN_MICRO_SECONDS / iData->iFramesPerSecond);
}

void CRS_ManContainer::HandleDebugGameKey()
{
    switch (iGameKey)
    {
        case TEnum::EFramesAdd:
        {
            AddFrame();
            iGameKey = TEnum::EKeyNone;
            break;
        }
        case TEnum::EFramesDesc:
        {
            DescFrame();
            iGameKey = TEnum::EKeyNone;
            break;
        }
        case TEnum::EScrollAdd:
        {
            iData->iScroll++;
            iGameKey = TEnum::EKeyNone;
            break;
        }
        case TEnum::EScrollDesc:
        {
            if (iData->iScroll > 0)
            {
                iData->iScroll--;
            }
            iGameKey = TEnum::EKeyNone;
            break;
        }
        case TEnum::EKeyPause:
        {
            iGfxTimer->Pause();
            iData->iGameState = TEnum::EControlPaused;
            ReportEventL(MCoeControlObserver::EEventStateChanged);
            break;
        }
    }
}

void CRS_ManContainer::DrawIndicator()
{
    iBitmapGc ->UseFont(iEikonEnv->NormalFont());
    if (iTelephoneState)
    {
        iBitmapGc->DrawText(*iTelephoneState, TPoint(30, 320));
    }
    /*
     iBitmapGc ->UseFont(iEikonEnv->NormalFont());
     TBuf<20> textScroll;
     //textScroll.Num(iScroll);
     textScroll.Num(iMan->iLifeValue);
     TBuf<20> textFrames;
     textFrames.Num(iData->iFramesPerSecond);

     iBitmapGc->DrawText(textScroll, TPoint(1, 69));
     iBitmapGc->DrawText(textFrames, TPoint(180, 69));
     iBitmapGc->DiscardFont();
     */
}
;

/*
 Man           Board
 iYOld |       iYNew  ^
 |              |
 |              |
 iYNew v       iYOld  |
 */
void CRS_ManContainer::CalculateCollisions()
{
    iMan->iDeltaX = 0;
    //先判断碰到最上的情况，最下的情况在EFree中判断
    if (iMan->iCenter.iY - iMan->iManHalfHeight < Y_AXIS_MIN_LIMIT + Y_UP_LIMIT_HEIGHT)
    {
        iMan->SetHurting();
        if (!iMan->iLifeValue > 0)
        {
            if (iNormalDeadPlayer)
            {
                iData->iGameState = TEnum::EControlAward;
                StopAllAudioPlayer();
                iNormalDeadPlayer->Play();
            }
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            return;
        }
        else
        {
            if (iStabPlayer)
            {
                StopAllAudioPlayer();
                iStabPlayer->Play();
            }
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            iMan->iCenter.iY = Y_AXIS_MIN_LIMIT + Y_UP_LIMIT_HEIGHT + iMan->iManHalfHeight + 1;
            //将 这个速度设置为10
            iMan->iDeltaY = GRAVITY_INITIAL_VELOCITY;
            iMan->iYNew = iMan->iCenter.iY + iMan->iManHalfHeight;
            iMan->iCollisionState = TEnum::EFree;
            iData->iBoardQueue->SetAllBoardsNotActive();
            return;
            //iData->iBoardQueue->SetAllBoardsNotActive();
        }
    }
    //
    SBoardQueue* pCur = NULL;
    SBoardQueue* pHead = iData->iBoardQueue->ipBoardQueue;
    switch (iMan->iCollisionState)
    {
        case TEnum::ECollisionWood:
        case TEnum::ECollisionStab:
        {
            pCur = pHead->next;
            do
            {
                if ((pCur->pBoardObject->iBoardName == TWorldObject::WoodBoard || pCur->pBoardObject->iBoardName
                    == TWorldObject::StabBoard) && pCur->pBoardObject->iIsActive)
                {
                    iMan->iDeltaY = iData->iScroll * (-1);
                    //如果Man与BoardName没有交汇点
                    if (iMan->iWorldPosition.iBr.iX < pCur->pBoardObject->iWorldPosition.iTl.iX
                        || iMan->iWorldPosition.iTl.iX > pCur->pBoardObject->iWorldPosition.iBr.iX)
                    {
                        //无焦点
                        iMan->iCollisionState = TEnum::EFree;
                        pCur->pBoardObject->iIsActive = EFalse;
                    }
                    break;
                }
                else
                {
                    pCur = pCur->next;
                    continue;
                }
            } while (pCur != pHead->next);
            break;
        }

        case TEnum::ECollisionConvey:
        {
            pCur = pHead->next;
            do
            {
                if (pCur->pBoardObject->iBoardName == TWorldObject::ConveyBoard && pCur->pBoardObject->iIsActive)
                {
                    iMan->iDeltaY = iData->iScroll * (-1);
                    //判断X轴坐标是否还与BoardName有交汇点
                    if (iMan->iWorldPosition.iBr.iX < pCur->pBoardObject->iWorldPosition.iTl.iX
                        || iMan->iWorldPosition.iTl.iX > pCur->pBoardObject->iWorldPosition.iBr.iX)
                    {
                        //无焦点
                        iMan->iCollisionState = TEnum::EFree;
                        //iMan.iAccelerationY = GRAVITY_ACCELERATION_SCROLL;
                        iMan->iDeltaY = GRAVITY_INITIAL_VELOCITY;
                        //iMan.iCurrentFrame=0;
                        pCur->pBoardObject->iIsActive = EFalse;
                        break;
                    }
                    else
                    {
                        iMan->iDeltaX = ((TConveyBoard*) (pCur->pBoardObject))->iVelociry;
                        break;
                    }
                }
                else
                {
                    pCur = pCur->next;
                }
            } while (pCur != pHead->next);
            break;
        }
        case TEnum::EFree:
        {
            //判断Man掉出屏幕最底线的情况
            if (iMan->iCenter.iY > Y_AXIS_MAX_LIMIT)
            {
                if (iDropDeadPlayer)
                {
                    iData->iGameState = TEnum::EControlAward;
                    StopAllAudioPlayer();
                    iDropDeadPlayer->Play();
                }
                if (iData->iVibraEnable)
                {
                    iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
                }
                iMan->iLifeValue = 0;
            }
            //找到比较开始的Board
            pCur = pHead->next;

            //对可能出现的碰撞的Boards依次进行判断
            do
            {
                //Y轴判断碰撞的条件 Pa1<Pb1 && Pa2>=Pb2
                //X轴
                if (!(iMan->iWorldPosition.iTl.iX > pCur->pBoardObject->iWorldPosition.iBr.iX
                    || iMan->iWorldPosition.iBr.iX < pCur->pBoardObject->iWorldPosition.iTl.iX) && (iMan->iYOld
                    < pCur->pBoardObject->iYOld && iMan->iYNew >= pCur->pBoardObject->iYNew
                    && !pCur->pBoardObject->iIsActive))
                {
                    //产生了碰撞,根据不同的Board类型分别做相应的处理
                    CollisionOccur(pCur->pBoardObject);
                    return;
                }
                else
                {
                    pCur = pCur->next;
                    continue;
                }
            } while (pCur != pHead->next);
            //如果能走到此 则表示此时没有与任何对象发生碰撞，仍是自由落体，则更新新的Y轴速度
            iMan->iDeltaY += GRAVITY_ACCELERATION_SCROLL;//if(iMan.iYOld)
            break;
        }
    }
}

void CRS_ManContainer::HandleManMain()
{
    switch (iData->iGameState)
    {
        case TEnum::EWaitingStart:
        {
            TPoint point = iData->iBoardQueue->GetManPosition();
            if (iData->iBoardQueue->ValidManPosition(point))
            {
                iMan->Reset(point, iData->iScroll);
                iData->iGameState = TEnum::EPlaying;
            }
            break;
        }
        case TEnum::EPlaying:
        {
            /*
             if (iMan->IsDeath())
             {
             iData->iLives--;
             if (iData->iLives > 0)
             {
             iData->iLives--;
             iData->iGameState = TEnum::EWaitingStart;
             //music
             }
             else
             {
             iData->iGameState = TEnum::EControlAward;
             //iGfxTimer->Pause();
             if (iNormalDeadPlayer)
             {
             StopAllAudioPlayer();
             iNormalDeadPlayer->Play();
             }
             iGameKey = TEnum::EKeyNone;
             return;
             }
             }
             */
            iMan->Quentum();
            CalculateCollisions();
            //CalcActionState();
            UpdateMan();
            iMan->Draw(iBackupBitmap, iResourceMap);
            break;
        }
        case TEnum::EControlAward:
        {
            iGameKey = TEnum::EKeyNone;
            return;
        }
        default:
        {
            break;
        }
    }
}

//处理当Man与某一个Board发生碰撞时的Man和Board的数据变化
//在Man中 速度放向向下为正方向
void CRS_ManContainer::CollisionOccur(TWorldObject* pBoard)
{
    iMan->iCenter.iY = pBoard->iYNew - iMan->iManHalfHeight;
    iMan->iYNew = pBoard->iYNew;
    switch (pBoard->iBoardName)
    {
        case TWorldObject::WoodBoard:
        {
            if (iWoodPlayer)
            {
                StopAllAudioPlayer();
                iWoodPlayer->Play();
            }
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            //此时iManY速度为向上，为负方向
            iMan->iDeltaY = iData->iScroll * (-1);
            iMan->iCollisionState = TEnum::ECollisionWood;
            //
            pBoard->iIsActive = ETrue;
            //播放声音

            break;
        }
        case TWorldObject::MarbleBoard:
        {
            if (iMarblePlayer)
            {
                //iMarblePlayer->Stop();
                StopAllAudioPlayer();
                iMarblePlayer->Play();
            }
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            iMan->iDeltaY = 0;// GRAVITY_INITIAL_VELOCITY;
            //Man的状态改为从速度0开始自由落体
            iMan->iCollisionState = TEnum::EFree;
            //将Marble的状态改为真，并且当前帧为第一帧
            ((TMarbleBoard*) (pBoard))->SetActive();

            break;
        }
        case TWorldObject::ConveyBoard:
        {
            if (iConveyPlayer)
            {
                StopAllAudioPlayer();
                iConveyPlayer->Play();
            }
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            iMan->iDeltaY = iData->iScroll * (-1);
            iMan->iDeltaX = ((TConveyBoard*) (pBoard))->iVelociry;
            iMan->iCollisionState = TEnum::ECollisionConvey;
            //
            pBoard->iIsActive = ETrue;

            break;
        }
        case TWorldObject::SpringBoard:
        {
            //声音

            if (iSpringSoundSwitch && iSpringPlayer)
            {
                StopAllAudioPlayer();
                //iSpringPlayer2->Stop();
                iSpringPlayer->Play();
                iSpringSoundSwitch = EFalse;
            }
            else if (iSpringPlayer2)
            {
                StopAllAudioPlayer();
                //iSpringPlayer->Stop();
                iSpringPlayer2->Play();
                iSpringSoundSwitch = ETrue;
            }
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            iMan->iDeltaY = SPRING_BOARD_BELOCITY;
            iMan->iCollisionState = TEnum::EFree;
            //
            ((TSpringBoard*) (pBoard))->SetActive();
            break;
        }
        case TWorldObject::StabBoard:
        {
            if (iData->iVibraEnable)
            {
                iData->iTouchFeedBack->InstantFeedback(ETouchFeedbackBasic);
            }
            iMan->iDeltaY = iData->iScroll * (-1);
            iMan->iCollisionState = TEnum::ECollisionStab;
            iMan->SetHurting();
            //声音
            if (iMan->IsDeath())
            {
                if (iNormalDeadPlayer)
                {
                    iData->iGameState = TEnum::EControlAward;
                    StopAllAudioPlayer();
                    iNormalDeadPlayer->Play();
                }
            }
            else
            {
                if (iStabPlayer)
                {
                    StopAllAudioPlayer();
                    iStabPlayer->Play();
                }
            }
            //
            pBoard->iIsActive = ETrue;
            break;
        }
    }
}

void CRS_ManContainer::CalcActionState()
{
    switch (iGameKey)
    {
        case TEnum::EKeyLeft:
        {
            iMan->iDeltaX -= MAN_X_VELOCITY;
            break;
        }
        case TEnum::EKeyRight:
        {
            iMan->iDeltaX += MAN_X_VELOCITY;
            break;
        }
        case TEnum::EKeyNone:
        {
            //iMan.iDeltaX = 0;
            break;
        }
    }
    //根据速度判断行动动作 并且根据前一个动作设定当前帧
    //如果前后动作一致 则不修改
    TEnum::TManActionState eManActionState = iMan->iManActionState;

    if (iMan->iDeltaX > 0)
    {
        if (iMan->iCollisionState == TEnum::EFree)
        {
            //自由落体的情况
            if (iMan->iIsHurting)
            {
                iMan->iManActionState = TEnum::ERightJumpRed;
            }
            else
            {
                iMan->iManActionState = TEnum::ERightJump;
            }
        }
        else
        {
            //在板子上的情况
            if (iMan->iIsHurting)
            {
                iMan->iManActionState = TEnum::ERightRed;
            }
            else
            {
                iMan->iManActionState = TEnum::ERight;
            }
        }
    }
    if (iMan->iDeltaX < 0)
    {
        if (iMan->iCollisionState == TEnum::EFree)
        {
            //自由落体的情况
            if (iMan->iIsHurting)
            {
                iMan->iManActionState = TEnum::ELeftJumpRed;
            }
            else
            {
                iMan->iManActionState = TEnum::ELeftJump;
            }
        }
        else
        {
            //在板子上的情况
            if (iMan->iIsHurting)
            {
                iMan->iManActionState = TEnum::ELeftRed;
            }
            else
            {
                iMan->iManActionState = TEnum::ELeft;
            }
        }
    }
    if (iMan->iDeltaX == 0)
    {
        if (iMan->iCollisionState == TEnum::EFree)
        {
            //自由落体的情况
            if (iMan->iIsHurting)
            {
                iMan->iManActionState = TEnum::EJumpRed;
            }
            else
            {
                iMan->iManActionState = TEnum::EJump;
            }
        }
        else
        {
            //在板子上的情况
            if (iMan->iIsHurting)
            {
                iMan->iManActionState = TEnum::EStandRed;
            }
            else
            {
                iMan->iManActionState = TEnum::EStand;
            }
        }
    }
    if (iMan->iCollisionState == TEnum::ECollisionConvey && (iMan->iDeltaX == TConveyBoard::EConveyLeft
        || iMan->iDeltaX == TConveyBoard::EConveyRight))
    {
        if (iMan->iIsHurting)
        {
            iMan->iManActionState = TEnum::EStandRed;
        }
        else
        {
            iMan->iManActionState = TEnum::EStand;
        }
    }
    //根据当前动作是否和上一动作一致设置当前帧
    if (eManActionState != iMan->iManActionState)
    {
        //如果动作有变化，则将当前帧设置为0
        iMan->iCurrentFrame = 0;
        //重新计数
        //iMan.iTicks = 0;
        iMan->iTicksFrame = 0;
    }
    else
    {
        iMan->FrameChange();
    }
}

void CRS_ManContainer::UpdateMan()
{
    CalcActionState();
    iMan->CalcDrawableRect();
    //iMan.GetBitMapRect();
    //iMan.UpdateWorldPosition();
}
void CRS_ManContainer::StopAllAudioPlayer()
{
    if (iMarblePlayer)
    {
        iMarblePlayer->Stop();
    }
    if (iSpringPlayer)
    {
        iSpringPlayer->Stop();
    }
    if (iSpringPlayer2)
    {
        iSpringPlayer2->Stop();
    }
    if (iStabPlayer)
    {
        iStabPlayer->Stop();
    }
    if (iWoodPlayer)
    {
        iStabPlayer->Stop();
    }
    if (iConveyPlayer)
    {
        iConveyPlayer->Stop();
    }
}

void CRS_ManContainer::CallStatusChangedL(CTelephony::TCallStatus& aStatus, TInt aError)
{
    if (iTelephoneState)
    {
        delete iTelephoneState;
    }
    if (aError == KErrNone)
    {
        iCallStatus = CTelephony::EStatusRinging;
    }
}
// End of File


