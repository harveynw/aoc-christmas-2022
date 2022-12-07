#!/bin/bash

if [ ! -d build ]; then
  mkdir build
fi
cd build

cmake ..
make

for name in ./Problem*; do
    echo "Executing $name"
    $name
done