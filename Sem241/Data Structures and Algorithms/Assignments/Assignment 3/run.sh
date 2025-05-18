#!/bin/bash

# Clear the terminal
clear

# Check if exactly one argument is provided
if [ "$#" -ne 1 ]; then
    echo "ERROR: Usage: $0 { graph | topo}"
    exit 1
fi

# Use a case statement to handle different arguments
case "$1" in
    graph)
        echo "Running graph-related tasks..."
        # Add commands to execute for 'graph' argument
        g++ -fsanitize=address -fsanitize=undefined -std=c++17 -o main -Iinclude -Itest main.cpp test/unit_test/graph/unit_test.cpp test/unit_test/graph/test/*.cpp  -DTEST_GRAPH
        ;;
    topo)
        echo "Running topological sort tasks..."
        # Add commands to execute for 'topo' argument
        g++ -fsanitize=address -fsanitize=undefined -std=c++17 -o main -Iinclude -Itest main.cpp test/unit_test/sort_topo/unit_test.cpp test/unit_test/sort_topo/test/*.cpp  -DTEST_SORT_TOPO
        ;;
    *)
        echo "Invalid argument. Please use 'graph' or 'topo'."
        exit 1
        ;;
esac

# If the compilation was successful, clear the terminal and run the tests
if [ $? -eq 0 ]; then
    clear
    ./main test_unit
fi