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
    //创建一个单向循环链表,pBoardObject域暂不赋值
    void CreateQueueL(TInt aCount);
    void UpdateQueue(TWorldObject* aObject);
    //
    TPoint GetManPosition();
    TBool ValidManPosition(TPoint aPoint);
    void SetAllBoardsNotActive();
    // 
    ~TBoardQueue();
public:
    //链表的头指针，它指向当前最年轻的对象,iBoardQueue.next则指向当前最年老的对象，
    //一旦最老的对象生命周期结束，则重置next节点为最年轻，然后将iBoardQueue=iBoardQueue.next
    SBoardQueue* ipBoardQueue;
    TInt iCount;
};


#endif /* CBOARDQUEUE_H_ */
