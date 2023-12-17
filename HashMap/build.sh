#!/bin/bash

IMPLEMENTATIONS=(
    "../LinkedList/implementation/linkedlist.c"
    "./implementation/hashmap.c"
)

gcc main.c -o main.out ${IMPLEMENTATIONS[*]}
./main.out