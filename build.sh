#!/bin/bash
g++ -c chaos.cc -std=c++0x
g++ chaos.o -o chaos -lsfml-graphics -lsfml-window -lsfml-system
rm chaos.o