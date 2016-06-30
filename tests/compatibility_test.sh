#!/bin/bash
#
# Test that the brotli command-line tool can decompress old brotli-compressed
# files.

set -o errexit

BRO=../tools/bro
file_errors=0
pipe_errors=0
for file in testdata/*.compressed*; do
  echo "Testing decompression by opening file $file"
  expected=${file%.compressed*}
  uncompressed=${expected}.uncompressed
  $BRO -f -d -i $file -o $uncompressed
  diff -q $uncompressed $expected || true $(( file_errors++ ))
  # Test the streaming version
  echo "Testing decompression by piping file $file"
  $BRO -d > $uncompressed < $file
  diff -q $uncompressed $expected || true $(( pipe_errors++ ))
done
errors=$(( file_errors + pipe_errors ))
echo "Encountered $errors compatibility errors"
exit $errors
