#!/bin/bash

function test {
    local TEST_DIR=$1
    local INPUT_TYPE=$2
    
    ./stream_search $TEST_DIR/dict.txt $INPUT_TYPE < $TEST_DIR/input.txt > $TEST_DIR/output.txt
    
    diff $TEST_DIR/output.txt $TEST_DIR/output_etalon_$INPUT_TYPE.txt
    RETURN_CODE=$?; 
    
    if [[ $RETURN_CODE != 0 ]]; then 
    echo not matches etalon at $TEST_DIR input_type=$INPUT_TYPE
    exit $RETURN_CODE; 
    else
    echo ok - $TEST_DIR input_type=$INPUT_TYPE
    fi
}

cd ./build

test ../data/1 text
# test ../data/1 html
