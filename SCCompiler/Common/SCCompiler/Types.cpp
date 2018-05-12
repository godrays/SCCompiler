//
//  Types.cpp
//  SCC
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <cassert>
#include "Types.hpp"

using namespace scc;


#pragma mark - Type Checker Implementations.

Type TypeChecker::m_typePromotionTable[tTypeMax][tTypeMax] =
{
                           // tTypeUnknown, tTypeFloat,   tTypeInt,     tTypeBool,    tTypeVoid
    /* tTypeUnknown */      { tTypeUnknown, tTypeUnknown, tTypeUnknown, tTypeUnknown, tTypeUnknown  },
    /* tTypeFloat */        { tTypeUnknown, tTypeFloat,   tTypeFloat,   tTypeUnknown, tTypeUnknown  },
    /* tTypeInt */          { tTypeUnknown, tTypeFloat,   tTypeInt,     tTypeUnknown, tTypeUnknown  },
    /* tTypeBool */         { tTypeUnknown, tTypeUnknown, tTypeUnknown, tTypeBool,    tTypeUnknown  },
    /* tTypeVoid */         { tTypeUnknown, tTypeUnknown, tTypeUnknown, tTypeUnknown, tTypeVoid     },
};


Type TypeChecker::Promote(Type type1, Type type2)
{
    assert(type1 < tTypeMax && type2 < tTypeMax);

    return m_typePromotionTable[type1][type2];
}
