/*
 * ProbabilityTable.cpp
 *
 *  Created on: 2010-7-5
 *      Author: Administrator
 */
#define WOOD_INDEX 0
#define MARBLE_INDEX 3
#define CONVEY_INDEX 5
#define STAB_INDEX 9
#define SPRING_INDEX 13
#define MAX_INDEX 30
//如果当前关数超过MAX_FLOORS，概率分布表不再变化
#define MAX_FLOORS  170
//每一个CHANGE_UNIT概率分布表 变化一次
#define CHANGE_UNIT  10
//用来填充的board数
#define BOARD_COUNT 4

//            Wood    Marble   Convey    Stab   Spring
//开始时比重       17      3        2         4      4
//最终比重            10      5        4         6      5
#include <e32math.h>
#include "ProbabilityTable.h"
#include "WorldObject.h"

TProbabilityCreator::TProbabilityCreator()
{
    ResetAllFields();
}
//初始化所有的域
void TProbabilityCreator::ResetAllFields()
{
    //
    for (TInt i = 0; i < MARBLE_INDEX; i++)
    {
        iProbabilityArray[i] = TWorldObject::MarbleBoard;
    }
    for (TInt i = MARBLE_INDEX; i < CONVEY_INDEX; i++)
    {
        iProbabilityArray[i] = TWorldObject::ConveyBoard;
    }
    for (TInt i = CONVEY_INDEX; i < STAB_INDEX; i++)
    {
        iProbabilityArray[i] = TWorldObject::StabBoard;
    }
    for (TInt i = STAB_INDEX; i < SPRING_INDEX; i++)
    {
        iProbabilityArray[i] = TWorldObject::SpringBoard;
    }
    for (TInt i = SPRING_INDEX; i < MAX_INDEX; i++)
    {
        iProbabilityArray[i] = TWorldObject::WoodBoard;
    }
    //
    iCurFlag=SPRING_INDEX;
}


//每13层，概率分布表变化一次
void TProbabilityCreator::UpdateProbabilityArray(TInt aFloor)
{
    //一共有17个Wood可以待更改,按每10Floor更新一次概率分布表。则可以更改到170Floor。 170Floors往后，概率分布表不再变化
    if (aFloor % CHANGE_UNIT != 0 || iCurFlag>=MAX_INDEX)
    {
        return;
    }
    TInt offset=aFloor/CHANGE_UNIT;
    offset=offset%BOARD_COUNT;
    switch (offset)
    {
        case 0:
        {
            iProbabilityArray[iCurFlag++] = TWorldObject::MarbleBoard;
            break;
        }
        case 1:
        {
            iProbabilityArray[iCurFlag++] = TWorldObject::ConveyBoard;
            break;
        }
        case 2:
        {
            iProbabilityArray[iCurFlag++] = TWorldObject::StabBoard;
            break;
        }
        case 3:
        {
            iProbabilityArray[iCurFlag++] = TWorldObject::SpringBoard;
            break;
        }
    }
}

TInt TProbabilityCreator::GetRadomObject()
{
    TInt num = Math::Random() % 30;
    return iProbabilityArray[num];
}
