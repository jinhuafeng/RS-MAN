/*
 * TextDisplayer.h
 *
 *  Created on: 2010-9-25
 *      Author: jhf
 */

#ifndef TEXTDISPLAYER_H_
#define TEXTDISPLAYER_H_
#include <AknUtils.h> 
#include <e32std.h>
#include <eikdef.h>
#include <fbs.h>
#include <GDI.H> 
#include <e32cmn.h> 
#include "Macro.h"

//�����к�������˳��
//1:ConstructL(CFont* aFont)
//2:FillArrayText();
//3:FillArrayLength();
class CTextDisplayer
{
public:
    void ConstructL(const CFont* aFont);
    ~CTextDisplayer();
    //��BufText���ݷָ���䵽ÿһ��
    void FillArrayText();
    //����ÿһ���ַ��Ŀ�ʼλ��
    void FillArrayPoint();
    void AddStartIndex(TInt aDistance);
    void DescStartIndex(TInt aDistance);
    void DrawArrayText(CFbsBitGc* aBitmapGc);
public:
    PBufText iBufText;//�ı�������
private:
    CArrayFix<TPtrC>* iArrayText;
    //ÿһ�е�X�������
    //CArrayFix<TInt>* iArrayStartX;
    //TPtrC iArrayText[AWARD_PLAYER_COUNT];
    //TInt iArrayStartX[MAX_LINES_COUNTS];
    TPoint iArrayPoint[MAX_LINES_COUNTS];
    
    TInt iCurrStartIndex;//��ǰ��һ��Ҫ��ʾ���ж�Ӧ������
    const CFont* iFont;
};

#endif /* TEXTDISPLAYER_H_ */
