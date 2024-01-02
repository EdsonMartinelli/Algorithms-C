#!/bin/bash

if ! [ -n "$1" ]; then 
    echo "No arguments!"
    exit
fi

case $1 in 
LinkedList) ./output/bin/main_linkedlist.out;;
HashMap) ./output/bin/main_hashmap.out;;
PriorityQueue) ./output/bin/main_priorityqueue.out;;
HeapSort) ./output/bin/main_heapsort.out;;
Vector) ./output/bin/main_vector.out;;
InfinityArray) ./output/bin/main_infinityarray.out;;
*) echo "This folder not exists!";;
esac

exit
