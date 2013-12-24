/*
 * AudioPlayer.cpp
 *
 *  Created on: 2010-9-13
 *      Author: Jinhuafeng
 */

#include "AudioPlayer.h"
#include <MdaAudioTonePlayer.h>
#include <eikmenup.h>

CAudioPlayer* CAudioPlayer::NewL(const TDesC& aFileName,TInt aSoundDegree)
{
    CAudioPlayer* self = NewLC(aFileName,aSoundDegree);
    CleanupStack::Pop(self);
    return self;
}
CAudioPlayer* CAudioPlayer::NewLC(const TDesC& aFileName,TInt aSoundDegree)
{
    CAudioPlayer* self = new (ELeave) CAudioPlayer();
    CleanupStack::PushL(self);
    self->ConstructL(aFileName,aSoundDegree);
    return self;
}
CAudioPlayer::~CAudioPlayer()
{
    if(iPlayUtility)
    {
        iPlayUtility->Stop();
        iPlayUtility->Close();
    }
    delete iPlayUtility;
}
CAudioPlayer::CAudioPlayer()
{
    iIsPlayCompleted=EFalse;
}
void CAudioPlayer::ConstructL(const TDesC& aFileName,TInt aSoundDegree)
{
    iPlayUtility = CMdaAudioPlayerUtility::NewFilePlayerL(aFileName, *this);
    iSoundDegree=aSoundDegree;
}
void CAudioPlayer::Play()
{
    iPlayUtility->Play();
}
void CAudioPlayer::Pause()
{
    iPlayUtility->Pause();
}
void CAudioPlayer::Stop()
{
    iPlayUtility->Stop();
}
void CAudioPlayer::MapcPlayComplete(TInt /*aError*/)
{
    iIsPlayCompleted=ETrue;
}
void CAudioPlayer::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/)
{
    if(aError == KErrNone)
    {
        iPlayUtility->SetVolume((iPlayUtility->MaxVolume()*iSoundDegree)/10);
    }
}
void CAudioPlayer::SetSoundDegree(TInt aSoundDegree)
{
    iSoundDegree=aSoundDegree;
    iPlayUtility->SetVolume((iPlayUtility->MaxVolume()*iSoundDegree)/10);
}
