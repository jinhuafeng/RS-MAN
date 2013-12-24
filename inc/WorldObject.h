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
    //根据对象当前在屏幕中的位置，算出可以在屏幕中显示的部分，并计算在资源图中相应的需要绘制的部分。
    virtual void CalcDrawableRect();
    //重置对象的状态
    virtual void Reset();
    //计算该对象最上一条边的中点坐标
    virtual TPoint GetMidPointofTop();
    //绘制图像
    virtual void Draw(CWsBitmap* aBitmap, CWsBitmap* aResourceBitmap);
    //
    virtual void FrameChange();
public:
    TBitMapPosition* ipBitMapPosition;
public:
    TInt iCurrentFrame;
    //该对象当前是否正在被使用
    TBool iIsUsed;
    //iIsActive表示该对象当前正在被使用，而且刚刚与Man发生了碰撞
    TBool iIsActive;
    //图形在屏幕上可以显示的位置
    TRect iWorldPosition;
    //图形资源图中可以被画的位置
    TRect iDrawableBitMapRect;
    BoardName iBoardName;
    TInt iFrameCount;//该对象的帧数
    TWorldPoint iCenter;//
    //用于记录两帧中 碰撞检测点的Y轴位置
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
    //iDeltaX 向右为X轴速度正方向
    TInt iDeltaX;//x-axis velocity
    //iDeltaY 向下为Y轴速度正方向
    TInt iDeltaY;//y-axis velocity
    //TInt iTicks;
    //帧变化频率
    TInt iFrequency;
    TBool iIsHurting;
    TInt iLifeValue;
    //TInt iScore;
    TEnum::TManActionState iManActionState;
    TEnum::TCollisionState iCollisionState;
    TInt iManHalfHeight;
    TInt iManHalfWidth;
    //控制Man Hurting的iHurtTicks
    TInt iTicksHurting;
    //控制帧的Ticks
    TInt iTicksFrame;
    //控制生命复原的Ticks
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
    //弹簧静止不动时 高
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
