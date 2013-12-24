/*
 * CGfxTimer.cpp
 *
 *  Created on: 2010-6-28
 *      Author: Administrator
 */

#include "CGfxTimer.h"

//改成EPriorityLow
//原来是EPriorityHigh
CGfxTimer::CGfxTimer(MGfxTimerCallBack& aCallBackClient, TInt aId) :
    CTimer(CActive::EPriorityLow), iCallBackClient(aCallBackClient), iId(aId)
{
}

void CGfxTimer::ConstructL()
{
    CTimer::ConstructL();
    CActiveScheduler::Add(this);
}

void CGfxTimer::StartPulse(TTimeIntervalMicroSeconds32 aInterval)
{
    Cancel();
    iRestartTimer = ETrue;
    After(aInterval);
    iInterVal = aInterval;
}

void CGfxTimer::Start(TTimeIntervalMicroSeconds32 aInterval)
{
    Cancel();
    iRestartTimer = EFalse;
    After(aInterval);
}
void CGfxTimer::ChangeinterVal(TTimeIntervalMicroSeconds32 aNewInterval)
{
    iInterVal=aNewInterval;
    ReStart();
}
void CGfxTimer::Pause()
{
    iRestartTimer=EFalse;
    Cancel();
}

void CGfxTimer::ReStart()
{
    StartPulse(iInterVal);
}

void CGfxTimer::RunL()
{
    iCallBackClient.GfxTimerFiredL(iId);
    if (iRestartTimer)
    {
        StartPulse(iInterVal);
    }
}

