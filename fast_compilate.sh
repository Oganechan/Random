#!/bin/bash

debug=1

if [[ "$1" == "-d" || "$1" == "--debug" ]]; then
    echo "Optimization off"
    debug=0
else
    echo "Optimization on"
fi

cd $(dirname $0)
mkdir -p build

for cpp in $(find ./examples -name "*.cpp"); do
    filename=$(basename "$cpp" .cpp)
    if [[ $debug -eq 0 ]]; then
        g++ "$cpp" -o "./build/$filename"
    else
        g++ -O3 "$cpp" -o "./build/$filename"
    fi
done 
