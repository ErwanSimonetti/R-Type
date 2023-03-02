FROM ubuntu:latest

# Install apt packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    wget \
    git \
    gcc \
    clang \
    g++ \
    libfreetype6-dev \
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
    libx11-dev \
    libdrm-dev \
    libboost-all-dev \
    libjsoncpp-dev

# Copy client files
COPY client/ /app/client
COPY ECS/ /app/ECS
COPY network/ /app/network 
COPY ressources/ /app/ressources
COPY modules/ /app/modules
COPY utils /app/utils

RUN cd app/modules && make

# Launch game
CMD cd app/client && ./make_client && cd ../ && ./r-type_client ${GRAPHIC} ${GAME}
