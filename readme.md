# how to build and run in docker
```docker-compose up --build```

# how to build and run on unix
```
mkdir build
cd build
cmake .. 
cmake --build . -- -j4
ctest -V 
./stream_search 
```