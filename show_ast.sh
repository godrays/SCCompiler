#!/bin/bash

# Make sure graphviz is installed and dot command line application is in the path.
dot -Tsvg -o ast.svg ast.dot && open ast.svg
