//
//  main.cpp
//  SCCTestApp
//
//  Created by Arkin Terli on 4/1/18.
//  Copyright © 2018 Arkin Terli. All rights reserved.
//

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

// It's possible to remove main function here by adding only CATCH_CONFIG_RUNNER definition.

int main(int argc, char* argv[])
{
    Catch::Session session;

    auto exitCode = session.applyCommandLine(argc, argv);

    return exitCode != 0 ? exitCode : session.run();
}
