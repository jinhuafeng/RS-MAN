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

//该内中函数调用顺序
//1:ConstructL(CFont* aFont)
//2:FillArrayText();
//3:FillArrayLength();
class CTextDisplayer
{
public:
    void ConstructL(const CFont* aFont);
    ~CTextDisplayer();
    //将BufText内容分割填充到每一行
    void FillArrayText();
    //计算每一行字符的开始位置
    void FillArrayPoint();
    void AddStartIndex(TInt aDistance);
    void DescStartIndex(TInt aDistance);
    void DrawArrayText(CFbsBitGc* aBitmapGc);
public:
    PBufText iBufText;//文本的内容
private:
    CArrayFix<TPtrC>* iArrayText;
    //每一行的X轴的坐标
    //CArrayFix<TInt>* iArrayStartX;
    //TPtrC iArrayText[AWARD_PLAYER_COUNT];
    //TInt iArrayStartX[MAX_LINES_COUNTS];
    TPoint iArrayPoint[MAX_LINES_COUNTS];
    
    TInt iCurrStartIndex;//当前第一个要显示的行对应的索引
    const CFont* iFont;
};

#endif /* TEXTDISPLAYER_H_ */
