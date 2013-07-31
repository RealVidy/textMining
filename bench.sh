#!/bin/sh

#./compilator data/words.txt dico.bin
#./ref/TextMiningCompiler data/words.txt ref/dico.bin
cat testBase | ./ref/TextMiningApp ./ref/dico.bin > log1
cat testBase | ./interpreter dico.bin > log2

diff -q log1 log2
