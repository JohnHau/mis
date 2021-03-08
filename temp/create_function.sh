#!/bin/bash

function greeting()
{
	str="hello $name"
	echo $str

}


echo "Enter your name"
read name

val=$(greeting)

echo "return value of the funciotn is $val"

