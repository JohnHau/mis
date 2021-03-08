#!/bin/bash

echo "echo your directory name"

read ndir

if [ -d "$ndir" ]
then
echo "dir exist"
else
`mkdir $ndir`
echo "dir created"
fi
