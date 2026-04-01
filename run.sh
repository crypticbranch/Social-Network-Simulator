#!/bin/bash
# -------------------------------
# COL106 SocialNet Simulator Runner
# Author: Ritik Raj
# -------------------------------

# Colors for better output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Compiling the project...${NC}"

# Compile all .cpp files
g++ -std=c++17 main.cpp -o socialnet

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo -e "${GREEN}Compilation successful!${NC}"
else
    echo -e "${RED}Compilation failed.${NC}"
    exit 1
fi

# Check if an input file is provided
if [ -f "input.txt" ]; then
    echo -e "${YELLOW}Running program with input.txt...${NC}"
    ./socialnet < input.txt > output.txt
    echo -e "${GREEN}Execution finished! Output saved to output.txt${NC}"
else
    echo -e "${YELLOW}No input.txt found.${NC}"
    echo -e "Running in interactive mode (type EXIT to quit):"
    ./socialnet
fi