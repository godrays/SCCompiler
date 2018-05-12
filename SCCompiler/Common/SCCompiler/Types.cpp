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

Type TypeChecker::m_typePromotionTable[kTypeMax][kTypeMax] =
{
                           // kTypeUnknown, kTypeFloat,   kTypeInt,     kTypeBool,    kTypeVoid
    /* kTypeUnknown */      { kTypeUnknown, kTypeUnknown, kTypeUnknown, kTypeUnknown, kTypeUnknown  },
    /* kTypeFloat */        { kTypeUnknown, kTypeFloat,   kTypeFloat,   kTypeUnknown, kTypeUnknown  },
    /* kTypeInt */          { kTypeUnknown, kTypeFloat,   kTypeInt,     kTypeUnknown, kTypeUnknown  },
    /* kTypeBool */         { kTypeUnknown, kTypeUnknown, kTypeUnknown, kTypeBool,    kTypeUnknown  },
    /* kTypeVoid */         { kTypeUnknown, kTypeUnknown, kTypeUnknown, kTypeUnknown, kTypeVoid     },
};


Type TypeChecker::Promote(Type type1, Type type2)
{
    assert(type1 < kTypeMax && type2 < kTypeMax);

    return m_typePromotionTable[type1][type2];
}
