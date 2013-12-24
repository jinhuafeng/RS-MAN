/*
 * TextDisplayer.cpp
 *
 *  Created on: 2010-9-25
 *      Author: jhf
 */
#include "TextDisplayer.h"

void CTextDisplayer::ConstructL(const CFont* aFont)
{
    iBufText = new (ELeave) BufText;
    iArrayText = new CArrayFixFlat<TPtrC> (MAX_LINES_COUNTS);
    //iArrayStartX = new CArrayFix<TInt> (50);
    iCurrStartIndex = 0;
    iFont = aFont;
}

CTextDisplayer::~CTextDisplayer()
{
    if (iBufText)
    {
        delete iBufText;
    }
    if (iArrayText)
    {
        delete iArrayText;
    }
}
void CTextDisplayer::FillArrayText()
{
    AknTextUtils::WrapToArrayL(*iBufText, MAX_PIXELS_ONE_LINE, *iFont, *iArrayText);
    FillArrayPoint();
}

void CTextDisplayer::FillArrayPoint()
{
    //CFont* oFont =iEikonEnv->DenseFont();// static_cast<const CFbsFont*>(CEikonEnv::Static()->DenseFont());
    TPoint point;
    point.iY = TEXT_DISPLAY_MIN_Y+TEXT_LINE_HEIGHT;
    for (TInt i = 0; i < iArrayText->Count(); i++)
    {
        //����ÿһ�еĿ��
        TInt width = iFont->TextWidthInPixels(iArrayText->At(i));
        TInt a = (MAX_PIXELS_ONE_LINE / 2) - (width / 2);
        //iArrayStartX[i]=a;
        iArrayPoint[i].iX = a;
        iArrayPoint[i].iY = point.iY;
        point.iY += TEXT_LINE_HEIGHT;
    }
}

//aDistanceΪ�ƶ��ľ��� ����Ϊ��ֵ
void CTextDisplayer::AddStartIndex(TInt aDistance)
{
    TInt counts = iArrayText->Count();

    //������һ��Ҳ�Ѿ�ȫ����ʾ�������仯
    if (iArrayPoint[counts - 1].iY <= TEXT_DISPLAY_MAX_Y - TEXT_LINE_HEIGHT)
    {
        return;
    }
    iCurrStartIndex = 0;
    TBool isFindIndex = EFalse;
    for (TInt i = 0; i < counts; i++)
    {
        iArrayPoint[i].iY -= aDistance;
        if (!isFindIndex && iArrayPoint[i].iY >= TEXT_DISPLAY_MIN_Y - TEXT_LINE_HEIGHT)
        {
            iCurrStartIndex = i;
            isFindIndex = ETrue;
        }
    }
}

void CTextDisplayer::DescStartIndex(TInt aDistance)
{
    TInt counts = iArrayText->Count();

    //�����һ��Ҳ�Ѿ�ȫ����ʾ�������仯
    if (iArrayPoint[0].iY >= TEXT_DISPLAY_MIN_Y+TEXT_LINE_HEIGHT)
    {
        return;
    }
    iCurrStartIndex = 0;
    TBool isFindIndex = EFalse;
    for (TInt i = 0; i < counts; i++)
    {
        iArrayPoint[i].iY += aDistance;
        if (!isFindIndex && iArrayPoint[i].iY >= TEXT_DISPLAY_MIN_Y - TEXT_LINE_HEIGHT)
        {
            iCurrStartIndex = i;
            isFindIndex = ETrue;
        }
    }
}

void CTextDisplayer::DrawArrayText(CFbsBitGc* aBitmapGc)
{
    aBitmapGc ->UseFont(iFont);
    TInt counts = iArrayText->Count();
    TPoint point(2,10);
    for (TInt i = 0; i < MAX_LINES; i++)
    {
        point.iY=iArrayPoint[iCurrStartIndex + i].iY;
        if (iCurrStartIndex + i < counts)
        { 
            if(iCurrStartIndex+i==counts-1)
            {
                aBitmapGc->DrawText(iArrayText->At(iCurrStartIndex + i), iArrayPoint[iCurrStartIndex + i]);
            }
            else
            {
                aBitmapGc->DrawText(iArrayText->At(iCurrStartIndex + i), point);
            }
        }
    }
}
