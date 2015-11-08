#!/bin/bash

while true; do
  clear
  cmake ../
  VERBOSE=1 make && ./vectest

  fswatch -1 src deps
done
