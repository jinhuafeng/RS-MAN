// 
// Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of the License "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
// 
// Initial Contributors:
// Nokia Corporation - initial contribution.
// 
// Contributors:
// 
// Description:
// 
#ifndef CBOARDSPOOL_H_
#define CBOARDSPOOL_H_

#include <e32std.h>
#include <e32base.h>
#include "RS_Man.pan"
#include "WorldObject.h"

template<class T, TInt S>
class CObjectPool: public CBase
{
public:
    CObjectPool()
    {
        iSize = S;
        Reset();
    }
    ;

    void Reset()
    {
        for (TInt i = 0; i < iSize; i++)
        {
            ((TWorldObject*) &iObjects[i])->iIsUsed=EFalse;
        }
    }

    T* GetTheNextAvaliable()
    {
        for (TInt i = 0; i < iSize; i++)
        {
            if (!((TWorldObject*)& iObjects[i])->iIsUsed)
            {
                return &iObjects[i];
            }
        }
        return NULL;
    }
private:
    T iObjects[S];
    TInt iSize;
};

#endif /*CASTEROIDPOOL_H_*/
