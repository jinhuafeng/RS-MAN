/*
 * CBoardQueue.h
 *
 *  Created on: 2010-7-1
 *      Author: Administrator
 */

#ifndef CBOARDQUEUE_H_
#define CBOARDQUEUE_H_

#include "WorldObject.h"

struct SBoardQueue
{
    TWorldObject* pBoardObject;
    SBoardQueue* next;
};

class TBoardQueue
{
public:
    TBoardQueue();
    //����һ������ѭ������,pBoardObject���ݲ���ֵ
    void CreateQueueL(TInt aCount);
    void UpdateQueue(TWorldObject* aObject);
    //
    TPoint GetManPosition();
    TBool ValidManPosition(TPoint aPoint);
    void SetAllBoardsNotActive();
    // 
    ~TBoardQueue();
public:
    //�����ͷָ�룬��ָ��ǰ������Ķ���,iBoardQueue.next��ָ��ǰ�����ϵĶ���
    //һ�����ϵĶ����������ڽ�����������next�ڵ�Ϊ�����ᣬȻ��iBoardQueue=iBoardQueue.next
    SBoardQueue* ipBoardQueue;
    TInt iCount;
};


#endif /* CBOARDQUEUE_H_ */
