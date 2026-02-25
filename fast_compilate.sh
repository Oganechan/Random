#!/bin/bash

cd $(dirname $0)
mkdir -p build

for cpp in $(find ./examples -name "*.cpp"); do
    filename=$(basename "$cpp" .cpp)
    g++ "$cpp" -o "./build/$filename"
done 
