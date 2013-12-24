/*
 * BoardQueue.cpp
 *
 *  Created on: 2010-7-1
 *      Author: Administrator
 */
#include <e32math.h>
#include "BoardQueue.h"

#include "Macro.h"

//#define Y_AXIS_BEGIN   555
//#define CENTER_SPAN_AXIS_Y   60

TBoardQueue::TBoardQueue()
{
}

void TBoardQueue::CreateQueueL(TInt aCount)
{
    iCount = aCount;
    SBoardQueue* pHead;
    SBoardQueue* pCur;
    pCur = new (ELeave) SBoardQueue;
    pHead = pCur;
    for (TInt i = 0; i < iCount - 1; i++)
    {
        pCur->next = new (ELeave) SBoardQueue;
        pCur = pCur->next;
    }
    pCur->next = pHead;
    ipBoardQueue = pHead;
}

TBoardQueue::~TBoardQueue()
{
    SBoardQueue* pDelete;
    for (TInt i = 0; i < iCount; i++)
    {
        pDelete = ipBoardQueue;
        ipBoardQueue = ipBoardQueue->next;
        delete pDelete;

    }
}

void TBoardQueue::UpdateQueue(TWorldObject* aObject)
{
    //�¶��������
    aObject->Reset();
    aObject->iIsUsed = ETrue;
    aObject->iCenter.iY = ipBoardQueue->pBoardObject->iCenter.iY + CENTER_SPAN_AXIS_Y;
    //aObject->CalcDrawableRect();
    //�϶��������
    ipBoardQueue->next->pBoardObject->Reset();
    ipBoardQueue->next->pBoardObject->iIsUsed = EFalse;
    ipBoardQueue->next->pBoardObject->CalcDrawableRect();
    //�����µ�ͷָ��
    ipBoardQueue->next->pBoardObject = aObject;
    ipBoardQueue = ipBoardQueue->next;
}

//�ҵ������ϵĿ���λ��  λ��Ϊ���������һ���ߵ��е�
TPoint TBoardQueue::GetManPosition()
{
    TPoint point;
    point.SetXY(0, 0);
    //ֱ�Ӵ���һ���ڵ㿪ʼ
    //SBoardQueue* pCur = ipBoardQueue->next;
    TWorldObject* object = NULL;
    /*
     do
     {
     if (pCur->pBoardObject->iBoardName == TWorldObject::WoodBoard)
     {
     object = pCur->pBoardObject;
     }
     pCur=pCur->next;
     } while (pCur != ipBoardQueue->next);
     */
    if (ipBoardQueue->pBoardObject->iBoardName == TWorldObject::WoodBoard)
    {
        object = ipBoardQueue->pBoardObject;
    }
    if (object != NULL)
    {
        object->CalcDrawableRect();
        point.iX = object->iCenter.iX;
        point.iY = object->iWorldPosition.iTl.iY;
        object->iIsActive = ETrue;
    }
    return point;
}

TBool TBoardQueue::ValidManPosition(TPoint aPoint)
{
    if (aPoint.iY == 0)
    {
        return EFalse;
    }
    else
    {
        return ETrue;
    }
}

void TBoardQueue::SetAllBoardsNotActive()
{
    SBoardQueue* pCur = ipBoardQueue->next;
    do
    {
        if (pCur->pBoardObject->iIsActive)
        {
            if (pCur->pBoardObject->iBoardName != TWorldObject::SpringBoard)
            {
                pCur->pBoardObject->iIsActive = EFalse;
            }
            break;
        }
        pCur = pCur->next;
    } while (pCur != ipBoardQueue->next);
}

