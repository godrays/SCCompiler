//
//  CodeGenerationTests.hpp
//
//  Created by Arkin Terli on 5/8/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#include <string>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>

#include "Compiler.hpp"


class CodeGenerationTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( CodeGenerationTests );
    
    CPPUNIT_TEST_SUITE_END();
    
public:
    
    // Common test setup and cleanup.
    void setUp();
    void tearDown();
    
    // Tests given source code.
    SCCompiler::SCModule * TestCode(std::string sourceCode,
                                    SCCompiler::CompileResult expectedCompileResult,
                                    bool acceptExpectedCompileResult);

    // Code Generation Tests

};
