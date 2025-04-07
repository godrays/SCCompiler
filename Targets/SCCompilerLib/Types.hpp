//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018-Present, Arkin Terli. All rights reserved.
//

#pragma once

// Project includes
// External includes
// System includes
#include <iostream>


namespace scc
{

// Types.
// Note: Changes to this enum require changes in the promotion table.
enum Type : uint32_t
{
    kTypeUnknown     = 0,
    kTypeFloat       = 1,
    kTypeInt         = 2,
    kTypeBool        = 3,
    kTypeVoid        = 4,
    kTypeMax         = 5,
};


// Implements static helper methods for the type system.
class TypeChecker
{
public:
    // Promotes types if possible.
    static Type Promote(Type type1, Type type2);

protected:
    // The protected constructor disallows allocation of this object.
    TypeChecker() = default;

private:
    // Type promotion table.
    static Type m_typePromotionTable[kTypeMax][kTypeMax];
};

}
