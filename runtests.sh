#!/bin/bash

olddir=$(pwd)
cd "$(dirname "$0")"

if [ ! -f "./build/tests/metaxxa-tests" ]; then
    ./rebuild.sh
fi

./build.sh
./build/tests/metaxxa-tests

cd $olddir
