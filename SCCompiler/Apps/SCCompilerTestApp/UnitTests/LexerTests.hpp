//
//  LexerTests.hpp
//  SCCompilerTestApp
//
//  Created by Arkin Terli on 4/1/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#pragma once

#include <string>
#include <stdexcept>
#include <cppunit/extensions/HelperMacros.h>


class LexerTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( LexerTests );
    
    CPPUNIT_TEST( LexerAcceptanceTest );
    
    CPPUNIT_TEST_SUITE_END();
    
public:
    
    // Common test setup and cleanup.
    void setUp();
    void tearDown();
    
    // Lexer Acceptance Test
    
    void LexerAcceptanceTest();
};
