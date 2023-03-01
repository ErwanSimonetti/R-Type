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
    libsfml-dev \
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
    libboost-all-dev

COPY server/ /app/server
COPY ECS/ /app/ECS
COPY modules /app/modules
COPY network/ /app/network
COPY utils /app/utils

CMD cd modules && make

CMD cd app/server && ./make_server && cd ../ && ./r-type_server ${GAME}