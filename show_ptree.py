import os
import sys
import shutil
import subprocess

def showHelp():
    # Display usage information and an example for running the script.
    print("Shows parse-tree for the given source code file.")
    print("")
    print("Usage:")
    print(f"    {sys.argv[0]} <cmake-build_dir> <grammar-file> <source-code-file>")
    print("")
    print("Example:")
    print(f"    {sys.argv[0]} build-release Targets/SCCompilerLib/Parser/SCCompiler.g4 example-code.src")
    print("")

def runShellCmd(command):
    # Run a shell command and ignore any errors, as provided in the query.
    try:
        subprocess.run(command, shell=True, check=True)
    except:
        pass

def main(buildDir, grammarFile, sourceFile):
    # Generate and display the parse tree for a source code file using ANTLR4.
    # Convert input paths to absolute paths for consistency across platforms
    absBuildDir = os.path.abspath(buildDir)
    absGrammarFile = os.path.abspath(grammarFile)
    absSourceFile = os.path.abspath(sourceFile)

    # Extract the grammar filename and its name without extension.
    grammarFilename = os.path.basename(absGrammarFile)
    grammarName = os.path.splitext(grammarFilename)[0]

    # Define paths using os.path.join for cross-platform compatibility.
    jarFile = os.path.join(absBuildDir, 'Externals', 'antlr4_tool', 'download', 'antlr4-tool.jar')
    tempDir = os.path.join(absBuildDir, 'Temp' + grammarFilename)
    parserFirstRuleName = 'program'     # Default start rule, consistent with typical ANTLR usage.

    # Remove the temporary directory if it already exists.
    if os.path.exists(tempDir):
        shutil.rmtree(tempDir)

    # Create the temporary directory.
    os.makedirs(tempDir)

    # Copy the grammar file to the temporary directory.
    shutil.copy(absGrammarFile, tempDir)

    # Generate parser files using ANTLR4.
    runShellCmd(f"java -jar {jarFile} {os.path.join(tempDir, grammarFilename)} -o {tempDir}")

    # Compile the generated Java files.
    runShellCmd(f"javac -cp {jarFile} {os.path.join(tempDir, grammarName + '*.java')}")

    # Run ANTLR4 TestRig to display the parse tree GUI.
    classpath = f"{tempDir}{os.pathsep}{jarFile}"
    runShellCmd(f"java -cp {classpath} org.antlr.v4.gui.TestRig "
                f"{grammarName} {parserFirstRuleName} -gui < {absSourceFile}")

    # Clean up by removing the temporary directory.
    if os.path.exists(tempDir):
        shutil.rmtree(tempDir)

if __name__ == '__main__':
    if len(sys.argv) == 4:
        main(buildDir=sys.argv[1], grammarFile=sys.argv[2], sourceFile=sys.argv[3])
    else:
        showHelp()
