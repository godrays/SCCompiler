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


#pragma mark - Class CodeGenerationTests

class CodeGenerationTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( CodeGenerationTests );

    CPPUNIT_TEST( CodeGenerationExplicitTypeConversionTests );
    CPPUNIT_TEST( CodeGenerationUnaryOPTests );
    CPPUNIT_TEST( CodeGenerationComparisonOPTests );
    CPPUNIT_TEST( CodeGenerationIfStatementTests );

    CPPUNIT_TEST_SUITE_END();
    
public:
    
    // Common test setup and cleanup.
    void setUp();
    void tearDown();
    
    // Tests given source code.
    scc::SCModule * TestCode(std::string sourceCode,
                             scc::SCCompileResult expectedCompileResult,
                             bool acceptExpectedCompileResult);

    // Code Generation Tests

    void CodeGenerationExplicitTypeConversionTests();

    void CodeGenerationUnaryOPTests();

    void CodeGenerationComparisonOPTests();
    
    void CodeGenerationIfStatementTests();
};
