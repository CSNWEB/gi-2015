#!/bin/bash

printf "=== RUN INTERNAL TESTS: ===\n\n"
./bin/runner

printf "\n=== RUN EXTERNAL TESTS FROM FILES: ===\n"
printf "considers all files starting with \'test_\' and ending with \'.txt\'\n\n"

mkdir -p output
OUTPREFIX="output/"

for f in $( ls | grep 'test_.*.txt' ); do
	NAME=$(echo $f | sed s/.txt//)
	OUTNAME=$OUTPREFIX$NAME

	echo === TEST FILE: $NAME ===
	./bin/runner $f $OUTNAME
	printf "\n"
done