#!/bin/sh
gcc -o dow dow.c
./dow > londontzstruct.c
gcc -o testtzstruct londontzstruct.c tzstruct.c testtzstruct.c
./testtzstruct

