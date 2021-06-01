#!/bin/bash

cd build
rm -rf *
cmake ..  "$1"
