# R-Type
![TitleScreen](./docs/images/RTypeTitle.jpg)  
### Table of Contents

Launch by using `./make_r-type client`
1. [Presentation of the project](#presentation-of-the-project)
2. [Requirements](#Requirements)
3. [How to run the game](#How-to-run-the-game)
4. [Controls](#controls)
5. [Developers](#Developers)

### Presentation of the project
#
The purpose of this project is to remake the R-Type game, adding a multiplayer element to it.
R-type is a a shoot them up with horizontal scrolling,
developed by Irem and released in 1987 on arcade machines.

![Screenshot](./docs/images/screenshotRtype.jpg)

In order to make the game multiplayer, we implemented a multithreaded server using [Asio](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_asio.html), from the [Boost](https://www.boost.org) library.

The game is rendered using the [SFML](https://www.sfml-dev.org/) library, and has fully been developped in C++. 

### Requirements
#

![windows logo](./docs/images/winlogo.png) ![linux logo](./docs/images/linlogo.png) ![apple logo](./docs/images/applogo.png)  
The project runs on Windows and Unix systems, using [CMake](https://cmake.org/).  
Make sure Boost is already installed on your system, or use their [man page](https://www.boost.org/doc/libs/1_67_0/doc/html/boost_asio/using.html) to install it according to your specs. 
<br/>

### Run the Engine
#
![linux logo](./docs/images/linlogo.png) ![apple logo](./docs/images/applogo.png)  
To launch the engine, you must use our docker container and specify the shared object libraries you want to use.  
We have two containers: one for the client and one for the server.  
  
To run the server container, you need to provide a .so game
```sh
$ ./makeDocker server [nameOfContainer] [path: .so game]
ex: ./makeDocker server server ./modules/rtype.so
```

To run the client container, you need to provide a graphic librarie .so and a game .so
```sh
$ ./makeDocker client [nameOfContainer] [path: .so graphic] [path: .so game]
ex: ./makeDocker client client ./modules/sfml.so ./modules/rtype.so
```

![windows logo](./docs/images/winlogo.png)  
On Windows :
```sh
$ In a future release
```
### Controls
#
 Button        | Direction
 --------------|-------------
 Up Arrow      | Top
 Down Arrow    | Down
 Left Arrow    | Left
 Right Arrow   | Right
 Spacebar      | Shoot


### Developers
#

| [<img src="https://github.com/Azzzen.png?size=85" width=85><br><sub>Axel Zenine</sub>](https://github.com/Azzzen) | [<img src="https://github.com/ErwanSimonetti.png?size=85" width=85><br><sub>Erwan Simonetti</sub>](https://github.com/ErwanSimonetti) | [<img src="https://github.com/BlanchoMartin.png?size=85" width=85><br><sub>Martin Blancho</sub>](https://github.com/BlanchoMartin) | [<img src="https://github.com/JulietteDestang.png?size=85" width=85><br><sub>Juliette Destang</sub>](https://github.com/JulietteDestang) | [<img src="https://github.com/TdeBoynes.png?size=85" width=85><br><sub>Timothée De Boynes</sub>](https://github.com/TdeBoynes)
| :---: | :---: | :---: | :---: | :---: |