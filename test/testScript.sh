#!/bin/bash

N=100000

echo
echo Timing for $N runs

echo
echo simpleMoran.cpp:
g++ simpleMoran.cpp
time ./a.out $N

echo
echo lessSimpleMoran.cpp:
g++ lessSimpleMoran.cpp
time ./a.out $N
