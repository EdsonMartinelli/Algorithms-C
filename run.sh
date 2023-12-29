#!/bin/bash

if ! [ -n "$1" ]; then 
    echo "No arguments!"
    exit
fi

case $1 in 
LinkedList) ./src/LinkedList/output/bin/main_linkedlist.out;;
HashMap) ./src/HashMap/output/bin/main_hashmap.out;;
PriorityQueue) ./src/PriorityQueue/output/bin/main_priorityqueue.out;;
HeapSort) ./src/HeapSort/output/bin/main_heapsort.out;;
Vector) ./src/Vector/output/bin/main_vector.out;;
InfinityArray) ./src/InfinityArray/output/bin/main_infinityarray.out;;
*) echo "This folder not exists!";;
esac

exit
