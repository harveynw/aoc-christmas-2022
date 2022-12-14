#!/bin/zsh

if [ ! -d build ]; then
  mkdir build
fi
cd build

cmake ..
make

for name in ./Problem*(n); do
    echo "Executing $name"
    $name
done