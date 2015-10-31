#!/bin/bash

while true; do
  clear
  cmake .
  make && out/bin/cpuvoxels

  fswatch -1 src deps
done
