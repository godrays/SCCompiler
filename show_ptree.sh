ANTLR_VERSION=4.7.1
PROJECT_PATH=`echo $PWD`
GRAMMAR_NAME=SCCompiler
GRAMMAR_PATH=$PROJECT_PATH/Targets/SCCompilerLib/Parser
GRAMMAR_FILE=$GRAMMAR_NAME.g4
INPUT_FILE=$1
JAR_FILE=$PROJECT_PATH/Externals/antlr/$ANTLR_VERSION/bin/antlr-$ANTLR_VERSION-complete.jar
PARSER_FIRST_RULE_NAME=program

# Remove all folder if there is
if [ -d /tmp/$GRAMMAR_NAME ]; then
    rm -rf /tmp/$GRAMMAR_NAME  &> /dev/null
fi

# Create a temp folder in /tmp folder
mkdir /tmp/$GRAMMAR_NAME
pushd . &> /dev/null

# Copy files to tmp folder.
cp $GRAMMAR_PATH/$GRAMMAR_FILE /tmp/$GRAMMAR_NAME/ &> /dev/null
cp $INPUT_FILE /tmp/$GRAMMAR_NAME/ &> /dev/null

# Generate parse files in tmp folder.
cd /tmp/$GRAMMAR_NAME &> /dev/null
java -jar $JAR_FILE $GRAMMAR_FILE -o . 

# Compile files and show AST
javac -cp "$JAR_FILE" $GRAMMAR_NAME*.java &&
java -cp ".:$JAR_FILE" org.antlr.v4.gui.TestRig $GRAMMAR_NAME $PARSER_FIRST_RULE_NAME -gui < $(basename $INPUT_FILE)

popd  &> /dev/null
