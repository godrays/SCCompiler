GRAMMAR_FILE=SCCompiler.g4

java -jar "Externals/ANTLR/4.8/tool/antlr-4.8-complete.jar" -Dlanguage=Cpp -visitor ./Targets/SCCompilerLib/Parser/$GRAMMAR_FILE
