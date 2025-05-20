#!/bin/bash

# sed -i 's/\r$//' run.sh (run this when switch to windows)

# Script to run test suites and clean test directories
# Usage: ./run.sh {lexer|parser|clean}

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 {lexer|parser|ast|clean}"
  exit 1
fi

# Define test directories
INPUT="./test/testcases"
OUTPUT="./test/solutions"

# Process command line argument
case "$1" in
    lexer)
        # Generate and run lexer tests
        python run.py gen && clear
        rm -f ${INPUT}/* 2>/dev/null
        rm -f ${OUTPUT}/* 2>/dev/null
        python run.py test LexerSuite
        ;;
    parser)
        # Generate and run parser tests
        python run.py gen && clear
        rm -f ${INPUT}/* 2>/dev/null
        rm -f ${OUTPUT}/* 2>/dev/null
        python run.py test ParserSuite
        ;;
    ast)
        # Run AST generation tests
        python run.py gen && clear
        rm -f ${INPUT}/* 2>/dev/null
        rm -f ${OUTPUT}/* 2>/dev/null
        python run.py test ASTGenSuite
        ;;
    clean)
        # Clean all test directories, suppressing errors for empty directories
        clear
        rm -f ${INPUT}/* 2>/dev/null
        rm -f ${OUTPUT}/* 2>/dev/null
        echo "Cleaned test directories:"
        echo "- ${INPUT}"
        echo "- ${OUTPUT}"
        ;;
    *)
        echo "Usage: $0 {lexer|parser|ast|clean}"
        exit 1
        ;;
esac