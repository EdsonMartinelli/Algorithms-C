#!/bin/bash

NAME=hashmap

gcc $NAME.c -o $NAME.out ../LinkedList/implementation/linkedlist.c
./$NAME.out