#!/bin/sh

cat testTime | time ./interpreter dico.bin > /dev/null

wc -l testTime
