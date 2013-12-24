/*
 * AudioPlayer.h
 *
 *  Created on: 2010-9-13
 *      Author: jinhuafeng
 */
#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_
#include <e32std.h>
#include <MdaAudioSamplePlayer.h>

class CAudioPlayer : public CBase, public MMdaAudioPlayerCallback
{
    public:
        static CAudioPlayer* NewL(const TDesC& aFileName,TInt aSoundDegree);
        static CAudioPlayer* NewLC(const TDesC& aFileName,TInt aSoundDegree);
        ~CAudioPlayer();
    private:
        CAudioPlayer();
        void ConstructL(const TDesC& aFileName,TInt aSoundDegree);
    public:
        void Play();
        void Stop();
        void Pause();
    public: // from MMdaAudioToneObserver
        void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);
        void MapcPlayComplete(TInt aError);
        void SetSoundDegree(TInt aSoundDegree);
    public:
        TBool iIsPlayCompleted;
        TInt iSoundDegree;
    private:
        CMdaAudioPlayerUtility* iPlayUtility;
};

#endif /* AUDIOPLAYER_H_ */
