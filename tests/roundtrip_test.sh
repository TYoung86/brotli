#!/bin/bash
#
# Roundtrip test for the brotli command-line tool.

set -o errexit

BRO=`ls -L --append-exe ../tools/bro || ../tools/bro`

INPUTS="""
testdata/alice29.txt
testdata/asyoulik.txt
testdata/lcet10.txt
testdata/plrabn12.txt
../enc/encode.cc
../enc/dictionary.h
../dec/decode.c
$BRO
"""

file_errors=0
pipe_errors=0
for file in $INPUTS; do
  for quality in 1 6 9 11; do
    echo "Roundtrip file testing $file at quality $quality"
    compressed=${file}.bro
    uncompressed=${file}.unbro
    $BRO -f -q $quality -i $file -o $compressed
    $BRO -f -d -i $compressed -o $uncompressed
    diff -q $file $uncompressed || true $(( file_errors++ ))
    # Test the streaming version
    echo "Roundtrip pipe testing $file at quality $quality"
    $BRO -q $quality < $file | $BRO -d > $uncompressed
    diff -q $file $uncompressed || true $(( pipe_errors++ ))
  done
done
errors=$(( file_errors + pipe_errors ))
echo "Encountered $errors roundtrip errors"
exit $errors
