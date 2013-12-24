/*
 * CGfxTimer.h
 *
 *  Created on: 2010-6-28
 *      Author: Administrator
 */

#ifndef CGFXTIMER_H_
#define CGFXTIMER_H_

#include <e32std.h>
#include <e32base.h>

class MGfxTimerCallBack
{
public:
    virtual void GfxTimerFiredL(TInt aId) = 0;
};

class CGfxTimer: public CTimer
{
public:

    CGfxTimer(MGfxTimerCallBack& aCallBackClient, TInt aId);
    void ConstructL();
    void StartPulse(TTimeIntervalMicroSeconds32 aInterval);
    void Start(TTimeIntervalMicroSeconds32 aInterval);
    void Pause();
    void ReStart();
    void ChangeinterVal(TTimeIntervalMicroSeconds32 aNewInterval);
    virtual void RunL();

private:
    MGfxTimerCallBack& iCallBackClient;
    TInt iId;
    TInt iRestartTimer;
    TTimeIntervalMicroSeconds32 iInterVal;
};

#endif /* CGFXTIMER_H_ */
