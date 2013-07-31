#!/bin/sh

cat testTime | time ../TextMiningApp ../dico.bin > /dev/null

wc -l testTime
