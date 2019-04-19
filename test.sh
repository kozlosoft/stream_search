#!/bin/bash
cd build

TEST_DIR=../data/1
INPUT_TYPE=text
./stream_search $TEST_DIR/dict.txt $INPUT_TYPE < $TEST_DIR/input.txt > $TEST_DIR/output.txt
diff $TEST_DIR/output.txt $TEST_DIR/output_etalon_$INPUT_TYPE.txt

TEST_DIR=../data/1
INPUT_TYPE=html
./stream_search $TEST_DIR/dict.txt $INPUT_TYPE < $TEST_DIR/input.txt > $TEST_DIR/output.txt
diff $TEST_DIR/output.txt $TEST_DIR/output_etalon_$INPUT_TYPE.txt
