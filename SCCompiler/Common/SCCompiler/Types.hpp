//
//  Types.hpp
//  SCC
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <iostream>


namespace SCC
{

    // Types.
    // Note: Changes to this enum requires change in promotion table.
    enum Type : uint32_t
    {
        tTypeUnknown     = 0,
        tTypeFloat       = 1,
        tTypeInt         = 2,
        tTypeBool        = 3,
        tTypeVoid        = 4,
        tTypeMax         = 5,
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
        static Type m_typePromotionTable[tTypeMax][tTypeMax];
    };

}
