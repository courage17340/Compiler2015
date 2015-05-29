#!/bin/bash

./translate < test.c > test.s
echo $?
spim load "test.s"
echo

