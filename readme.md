# how to build and run in docker
```docker-compose up --build```

# how to build and run on unix
```
mkdir build
cd build
cmake .. 
cmake --build . -- -j4
ctest -V 
(cd .. ; ./test.sh)
./stream_search <dict_path> <input_type=text|html> 
    e.g. ./stream_search ../data/1/dict.txt text 
```
