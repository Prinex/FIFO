#!/bin/sh

rm -rf ./lib
rm -rf ./bin

echo "Compiling..."
mkdir lib
cd ./lib
g++ --std=c++14 -c ../FIFO.cpp
cd ..

echo "Running..."
mkdir bin
cd ./bin
g++ --std=c++14 ../FIFO.cpp -o ./FIFO
cd ..
./bin/FIFO.exe


read -n1 -s -r -p $'Press space to continue...\n' key

if [ "$key" = ' ' ] then
	exit 0