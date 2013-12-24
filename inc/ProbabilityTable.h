/*
 * ProbabilityTable.h
 *
 *  Created on: 2010-7-5
 *      Author: Administrator
 */

#ifndef PROBABILITYTABLE_H_
#define PROBABILITYTABLE_H_

#include <e32std.h>
#include <e32base.h>

//
//
//
class TProbabilityCreator
{
public:
    TProbabilityCreator();
    void UpdateProbabilityArray(TInt aFloor);
    TInt GetRadomObject();
    void ResetAllFields();
public:
    TFixedArray<TInt, 30> iProbabilityArray;
    //TInt iFactor;
    //记录下一个需要改变的index
    TInt iCurFlag;
};

#endif /* PROBABILITYTABLE_H_ */
