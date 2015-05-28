#!/bin/bash

./translate < test.c > test.s
spim load "test.s"

