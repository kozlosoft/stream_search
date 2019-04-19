FROM ubuntu:latest

RUN apt-get update && apt-get install -y \ 
    cmake \
    clang \
    locales \
    git

# Set the locale
RUN locale-gen en_US.UTF-8

WORKDIR /data/build_docker
CMD cmake .. && cmake --build . -- -j4 && ctest -V && ./stream_search
