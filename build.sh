#!/bin/bash

cmake -S. -Bbuild -DTARGET_GROUP=teste
cmake --build build

cd build && make test