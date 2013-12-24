/*
 * WorldObject.h
 *
 *  Created on: 2010-6-28
 *      Author: Administrator
 */

#ifndef WORLDOBJECT_H_
#define WORLDOBJECT_H_

#include <W32STD.H> 
#include "WorldPoint.h"
#include "BitMapPosition.h"
#include "Enum.h"
#include "Drawer.h"

class CRS_ManAppUi;
//#include "BoardQueue.h"

class TWorldObject
{
public:
    enum BoardName
    {
        WoodBoard, MarbleBoard, ConveyBoard, SpringBoard, StabBoard, Man, EFree
    };
public:
    virtual void Quantum(TInt aVelaocity);
    virtual TBool Intersects(TRect aManRect);
    virtual void SetWorldCenter(TPoint aPoint);
    virtual void UpdateWorldPosition();
    virtual TRect GetBitMapRect()=0;
    //���ݶ���ǰ����Ļ�е�λ�ã������������Ļ����ʾ�Ĳ��֣�����������Դͼ����Ӧ����Ҫ���ƵĲ��֡�
    virtual void CalcDrawableRect();
    //���ö����״̬
    virtual void Reset();
    //����ö�������һ���ߵ��е�����
    virtual TPoint GetMidPointofTop();
    //����ͼ��
    virtual void Draw(CWsBitmap* aBitmap, CWsBitmap* aResourceBitmap);
    //
    virtual void FrameChange();
public:
    TBitMapPosition* ipBitMapPosition;
public:
    TInt iCurrentFrame;
    //�ö���ǰ�Ƿ����ڱ�ʹ��
    TBool iIsUsed;
    //iIsActive��ʾ�ö���ǰ���ڱ�ʹ�ã����Ҹո���Man��������ײ
    TBool iIsActive;
    //ͼ������Ļ�Ͽ�����ʾ��λ��
    TRect iWorldPosition;
    //ͼ����Դͼ�п��Ա�����λ��
    TRect iDrawableBitMapRect;
    BoardName iBoardName;
    TInt iFrameCount;//�ö����֡��
    TWorldPoint iCenter;//
    //���ڼ�¼��֡�� ��ײ�����Y��λ��
    TBool iIsNeedDraw;
    TInt iYNew;
    TInt iYOld;
};

class TMan: public TWorldObject
{
public:
    TMan();
    void Quentum();
    void SetPosition(TPoint aPoint);
    void Reset(TPoint aPoint, TInt aSroll);
    void LifeAdd();
    void SetBitMapPosition(TBitMapPosition* apBitMapPosition);
    void LifeDescend();
    TBool IsDeath();
    void SetHurting();
    //virtual TInt GetMapIndex();
    virtual TRect GetBitMapRect();
    virtual void FrameChange();
    void HandleTicker();
    TInt GetFramesCountByActionState(TEnum::TManActionState aManActionState);
public:
    //iDeltaX ����ΪX���ٶ�������
    TInt iDeltaX;//x-axis velocity
    //iDeltaY ����ΪY���ٶ�������
    TInt iDeltaY;//y-axis velocity
    //TInt iTicks;
    //֡�仯Ƶ��
    TInt iFrequency;
    TBool iIsHurting;
    TInt iLifeValue;
    //TInt iScore;
    TEnum::TManActionState iManActionState;
    TEnum::TCollisionState iCollisionState;
    TInt iManHalfHeight;
    TInt iManHalfWidth;
    //����Man Hurting��iHurtTicks
    TInt iTicksHurting;
    //����֡��Ticks
    TInt iTicksFrame;
    //����������ԭ��Ticks
    TInt iTicksLife;
};


class TWoodBoard: public TWorldObject
{
public:
    TWoodBoard();
    virtual TRect GetBitMapRect();
};

class TMarbleBoard: public TWorldObject
{
public:
    TMarbleBoard();
    virtual void Reset();
    virtual TRect GetBitMapRect();
    virtual void FrameChange();
    void SetActive();
    //virtual void CalcDrawableRect();
private:
    TInt iTicks;
    TInt iFrequency;
};

class TConveyBoard: public TWorldObject
{
public:
    enum Velocity
    {
        EConveyLeft = -4,
        EConveyRight = 4
    };
public:
    TConveyBoard();
    void SetVelocity(Velocity aVelocity);
    virtual TRect GetBitMapRect();
    virtual void Reset();
    virtual void FrameChange();
public:
    Velocity iVelociry;
    TInt iTicks;
    TInt iFrequency;
};

class TSpringBoard: public TWorldObject
{
public:
    TSpringBoard();
    virtual TRect GetBitMapRect();
    virtual void FrameChange();
    virtual void Reset();
    virtual void UpdateWorldPosition();
    void SetActive();
    TInt iFrequency;
private:
    TInt iTicks;
    //���ɾ�ֹ����ʱ ��
    TInt iStaticHeight;
};

class TStabBoard: public TWorldObject
{
public:
    TStabBoard();
    virtual void Reset();
    virtual void Quantum(TInt aVelocity);
    virtual TRect GetBitMapRect();
};

typedef unsigned char u8;
typedef unsigned int u32;
//for 24-bitmap   
struct R8G8B8
{
public:
    u8 B;
    u8 G;
    u8 R;
    inline R8G8B8(int acolor32)
    {
        R = (acolor32 >> 16) & 0xFF;
        G = (acolor32 >> 8) & 0xFF;
        B = acolor32 & 0xFF;
    }
    inline bool operator !=(R8G8B8& acolor)
    {
        if ((this->B == acolor.B) && (this->G == acolor.G) && (this->R == acolor.R))
            return false;
        else
            return true;
    }
    inline void operator =(R8G8B8& acolor)
    {
        this->B = acolor.B;
        this->R = acolor.R;
        this->G = acolor.G;
    }
};

class TCommonObject
{
public:
    TEnum::TGameState iGameState;
    TBitMapPosition* ipBitMapPosition;
    CRS_ManAppUi* ipAppUi;
    TDrawer* iDrawer;
    CWsBitmap* iResourceMap;
    TInt iScroll;
    TInt iScore;
    TBool iSoundEnable;
    TBool iVibraEnable;
};
#endif /* WORLDOBJECT_H_ */
