//
//  SyntaxTests.hpp
//
//  Created by Arkin Terli on 4/17/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>
#include "Compiler.hpp"

class SyntaxTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( SyntaxTests );
    
    CPPUNIT_TEST( SyntaxAcceptanceTest );
    
    CPPUNIT_TEST_SUITE_END();
    
public:
    
    // Common test setup and cleanup.
    void setUp();
    void tearDown();
    
    // Tests given source code.
    SCC::SCModule * TestCode(std::string sourceCode,
                                    SCC::CompileResult expectedCompileResult,
                                    bool acceptExpectedCompileResult);
    
    // Syntax Acceptance Test
    
    void SyntaxAcceptanceTest();
};

