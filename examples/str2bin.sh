#!/bin/sh
perl -e 'print pack "H*", $1' > tmp.bin
xxd -e -g4 tmp.bin | xxd -r > output.bin
rm tmp.bin
