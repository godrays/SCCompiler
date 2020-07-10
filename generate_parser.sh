GRAMMAR_FILE=SCCompiler.g4

java -jar "Externals/ANTLR/4.7.1/Tool/antlr-4.7.1-complete.jar" -Dlanguage=Cpp -visitor ./Targets/SCCompilerLib/Parser/$GRAMMAR_FILE
