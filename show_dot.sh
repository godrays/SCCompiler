#!/bin/bash

function showHelp()
{
    echo "Shows/Visualizes GraphViz dot file."
    echo ""
    echo "Usage:"
    echo "    $0 <filename>"
    echo ""
    echo "Example:"
    echo "    $0 ast.dot"
    echo ""
}

function main()
{
    if command -v dot >/dev/null 2>&1; then
        dot -Tsvg -o ast.svg $1 && open ast.svg
    else
        echo "Graphviz 'dot' command is not installed."
    fi
}

if [ "$#" -ge 1 ]; then
    main "$@"  # Pass all parameters
else
    showHelp
fi
