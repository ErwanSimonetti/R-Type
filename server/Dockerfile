FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    git \
    gcc \
    clang \
    g++ \
    libegl1-mesa \ 
    libgl1-mesa-dev \
    libglu1-mesa \
    libglu1-mesa-dev \
    libgtest-dev \
    binutils-dev \
    libtool \
    lua5.2 \
    liblua5.2-dev \
    liblua5.2-0 \
    graphviz \
    doxygen \
    cmake protobuf-compiler \
    udev \
    libboost-all-dev\
    libjsoncpp-dev

COPY server/ /app/server
COPY ECS/ /app/ECS
COPY modules /app/modules
COPY network/ /app/network
COPY utils /app/utils

RUN cd app/server && ./make_server
RUN cd app/modules && rm -f *.so && make game
CMD cd app/ && ./r-type_server ${GAME}
