//
//  Types.hpp
//  SCC
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <iostream>


namespace scc
{

    #pragma mark - Enum Type.

    // Types.
    // Note: Changes to this enum requires change in promotion table.
    enum Type : uint32_t
    {
        kTypeUnknown     = 0,
        kTypeFloat       = 1,
        kTypeInt         = 2,
        kTypeBool        = 3,
        kTypeVoid        = 4,
        kTypeMax         = 5,
    };


    #pragma mark - Class TypeChecker.

    // Implements static helper methods for type system.
    class TypeChecker
    {
    public:
        // Check if two types are equal.
        static Type Promote(Type type1, Type type2);
        
    protected:
        // Protected constructor disallows allocation of this object.
        TypeChecker() { }

    private:
        // Type promotion table.
        static Type m_typePromotionTable[kTypeMax][kTypeMax];
    };

}
