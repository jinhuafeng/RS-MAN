/*
 * BitmapNum.h
 *
 *  Created on: 2010-9-19
 *      Author: Administrator
 */

#ifndef BITMAPNUM_H_
#define BITMAPNUM_H_

#include "MotionElement.h"

class CData;

class TBitmapNum
{
public:
    void SetOriginNum(TInt aOriginNum, CData* iData);
    void UpdateNum(TInt aNewNum);
    void Quantum();
    void Draw(CWsBitmap* aBitmap, CWsBitmap* aResourceBitmap);
    
    CData* iData;
private:
    TRect GetMotionRectByNum(TInt aNum);
    //TInt iCurNum;
    TMotionElement iMotionUnits;
    TMotionElement iMotionTens;
    TMotionElement iMotionHundreds;
    TMotionElement iMotionThousands;
    TInt iUintNum;
    TInt iTenNum;
    TInt iHundredNum;
    TInt iThousandNum;
    TInt iOriginNum;
};

#endif /* BITMAPNUM_H_ */
