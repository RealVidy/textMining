#!/bin/sh

#./compilator data/words.txt dicoTest.bin
#./ref/TextMiningCompiler data/words.txt ref/dicoTest.bin
cat testBase | ./ref/TextMiningApp ./ref/dicoTest.bin > log1
cat testBase | ./interpreter dicoTest.bin > log2

diff -q log1 log2
