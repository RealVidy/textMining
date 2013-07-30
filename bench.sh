#!/bin/sh

cat testBase | ./ref/TextMiningApp ./ref/dico.bin > log1 2> /dev/null
cat testBase | ./interpreter dico.bin > log2

diff log1 log2
