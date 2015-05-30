#!/bin/bash

./translate < test.c > test.s
spim -stat load "test.s"

