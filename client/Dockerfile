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
    libxrandr-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxi-dev \
    libboost-all-dev \
    libjsoncpp-dev \
    libasound2-dev \
    libxcursor-dev \
    mesa-common-dev \
    libxi-dev \
    libogg-dev \
    xorg-dev \
    libboost-all-dev \
    libjsoncpp-dev \
    libopenal1 \
    alsa-base \
    alsa-utils \
    libsndfile1-dev \
    libglfw3-dev \
    libvorbis-dev \
    libopenal-dev 

RUN git clone https://github.com/raysan5/raylib.git && \
    cd raylib && mkdir build && cd build && cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON .. && make && make install

# Copy client files
COPY client/ /app/client
COPY ECS/ /app/ECS
COPY network/ /app/network 
COPY ressources/ /app/ressources
COPY modules/ /app/modules
COPY utils /app/utils

# Launch game
RUN cd app/client && ./make_client
RUN cd app/modules && rm -f *.so && make
CMD cd app/ && ./r-type_client ${GRAPHIC} ${GAME}
