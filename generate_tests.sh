#!/bin/bash
# generates the test data 
THE_BLACK_DRAMA="the_black_drama.txt"
PRIDE_AND_PREJUDICE="pride_and_prejudice.txt"

if [ ! -f "$THE_BLACK_DRAMA" ]; then
    curl -o the_black_drama.txt https://www.gutenberg.org/cache/epub/74147/pg74147.txt
fi

if [ ! -f "$PRIDE_AND_PREJUDICE" ]; then
    curl -o pride_and_prejudice.txt https://www.gutenberg.org/files/1342/1342-0.txt
fi
