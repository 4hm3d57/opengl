#!/bin/sh


set -xe

CXX="${CXX:-g++}"
CXXFLAGS="-Wall -Wextra -Wswitch-enum -std=c++11 -pedantic -fno-exceptions -fexceptions -ggdb -Wno-unused-parameter"
LIBS="-lGL -lglfw -ldl"

$CXX $CXXFLAGS -o main -I./include src/main.cpp src/glad.c $LIBS
