#!/usr/bin/env python3
#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#
#  NOTICE:  All information contained herein is, and remains the property of Arkin Terli.
#  The intellectual and technical concepts contained herein are proprietary to Arkin Terli
#  and may be covered by U.S. and Foreign Patents, patents in process, and are protected by
#  trade secret or copyright law. Dissemination of this information or reproduction of this
#  material is strictly forbidden unless prior written permission is obtained from Arkin Terli.

import os
import subprocess
import sys

def show_help():
    # Display usage information for the script.
    scriptName = os.path.basename(sys.argv[0])
    print("Generates parser files.\n")
    print("Usage:")
    print(f"    {scriptName} <cmake-build-dir>\n")
    print("Example:")
    print(f"    {scriptName} build-release\n")

def runShellCmd(command):
    try:
        subprocess.run(command, shell=True, check=True)
    except:
        pass

def main(buildDir):
    # Generate parser files using ANTLR tool with the specified build directory.
    grammarDir = os.path.join('.', 'Targets', 'SCCompilerLib', 'Parser')
    grammarFile = os.path.join(grammarDir, 'SCCompiler.g4')
    antlrJAR = os.path.join(buildDir, 'Externals', 'antlr4_tool', 'download', 'antlr4-tool.jar')
    command = [
        f"java -jar {antlrJAR} -Dlanguage=Cpp -visitor {grammarFile}",
    ]

    print(f"Parser files will be generated in: {grammarDir}")
    runShellCmd(command)

if __name__ == '__main__':
    if len(sys.argv) >= 2:
        main(buildDir=sys.argv[1])
    else:
        show_help()
