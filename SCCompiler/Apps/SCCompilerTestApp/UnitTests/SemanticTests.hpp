//
//  SemanticTests.hpp
//  SCC
//
//  Created by Arkin Terli on 4/18/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>

#include "Compiler.hpp"


#pragma mark - Class SemanticTests

class SemanticTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( SemanticTests );
    
    CPPUNIT_TEST( SemanticUndeclaredIdentifierTest );
    CPPUNIT_TEST( SemanticTypeMismatchTest );
    CPPUNIT_TEST( SemanticNonSpecificTest );

    CPPUNIT_TEST_SUITE_END();
    
public:
    
    // Common test setup and cleanup.
    void setUp();
    void tearDown();
    
    // Tests given source code.
    scc::SCModule * TestCode(std::string sourceCode,
                             scc::SCCompileResult expectedCompileResult,
                             bool acceptExpectedCompileResult);

    // Semantic Tests
    
    void SemanticUndeclaredIdentifierTest();

    void SemanticTypeMismatchTest();

    void SemanticNonSpecificTest();

};


