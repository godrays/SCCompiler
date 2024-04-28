ANTLR_VERSION=4.7.1
GRAMMAR_DIR=./Targets/SCCompilerLib/Parser
GRAMMAR_FILE=$GRAMMAR_DIR/SCCompiler.g4

echo Parser files will be generated in: $GRAMMAR_DIR
java -jar "Externals/antlr/$ANTLR_VERSION/bin/antlr-$ANTLR_VERSION-complete.jar" -Dlanguage=Cpp -visitor $GRAMMAR_FILE
