#!/bin/bash

cmake -S. -Bbuild -DTARGET_GROUP=testbuild
cmake --build build