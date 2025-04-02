#!/bin/bash
#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

function showHelp()
{
    echo "Generates parser files."
    echo ""
    echo "Usage:"
    echo "    $0 <cmake-build-dir>"
    echo ""
    echo "Example:"
    echo "    $0 build-release"
    echo ""
}

function main()
{
  GRAMMAR_DIR=./Targets/SCCompilerLib/Parser
  GRAMMAR_FILE=$GRAMMAR_DIR/SCCompiler.g4
  BUILD_DIR=$1

  echo Parser files will be generated in: $GRAMMAR_DIR
  java -jar "$BUILD_DIR/Externals/antlr4-tool/download/antlr4-tool.jar" -Dlanguage=Cpp -visitor $GRAMMAR_FILE
}

if [ "$#" -ge 1 ]; then
    main "$@"  # Pass all parameters
else
    showHelp
fi
