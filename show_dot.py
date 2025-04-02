#!/usr/bin/env python3
#
#  Copyright © 2018-Present, Arkin Terli. All rights reserved.
#

import sys
import shutil
import subprocess
import os

def showHelp():
    # Display usage information and an example for running the script.
    print("Shows/Visualizes GraphViz dot file.")
    print("")
    print("Usage:")
    print(f"    {sys.argv[0]} <filename>")
    print("")
    print("Example:")
    print(f"    {sys.argv[0]} ast.dot")
    print("")

def openFile(filePath):
    # Open a file with the default application based on the operating system.
    if sys.platform.startswith('darwin'):       # macOS
        subprocess.run(['open', filePath], check=True)
    elif sys.platform.startswith('win'):        # Windows
        os.startfile(filePath)                  # Note: os.startfile is Windows-only and doesn't support check=True
    elif sys.platform.startswith('linux'):      # Linux
        subprocess.run(['xdg-open', filePath], check=True)
    else:
        print("Unsupported operating system for opening files.")

def main(dotFile):
    # Convert a GraphViz dot file to SVG and open it.
    if shutil.which("dot"):
        outputFile = "ast.svg"
        command = f"dot -Tsvg -o {outputFile} {dotFile}"
        try:
            subprocess.run(command, shell=True, check=True)
            openFile(outputFile)
        except subprocess.CalledProcessError:
            print(f"Failed to convert {dotFile} to SVG.")
    else:
        print("Graphviz 'dot' command is not installed.")

if __name__ == "__main__":
    if len(sys.argv) >= 2:
        main(sys.argv[1])
    else:
        showHelp()
