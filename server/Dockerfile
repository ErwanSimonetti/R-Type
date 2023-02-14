FROM ubuntu:latest

EXPOSE 1234/udp
EXPOSE 1234/tcp

COPY server/ /app/server
COPY ECS/ /app/ECS
COPY network/ /app/network

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

CMD cd app/server && ./make_server && ./../r-type_server