#!/bin/bash

#./midtermvars.sh

#make clean

#make

#cp semantic bin/semantic

for source in `ls data/*/*/*.c`; do
  cp $source test.c
  ./semantic < test.c
  echo $? $source
done

