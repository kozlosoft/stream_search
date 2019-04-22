# how to build and run in docker
```docker-compose up --build stream_search_service```

It builds, runs unit-tests, runs integrational tests inside ubuntu container.

# how to build and run on unix
Do the same things without container
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

# how to build and run js frontend in docker
```docker-compose up --build frontend```

It runs ReactJS app inside a container on: ```http://localhost:3000/```
