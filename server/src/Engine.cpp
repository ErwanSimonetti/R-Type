/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"
#include "CLI.hpp"

Engine::Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port, const std::string &gameModulePath) : _reg(), _network(io_service, port)
{
    loadModules(gameModulePath, MODULE_TYPE::GAME);

    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Pet>();
    _reg.register_component<Hitbox>();
    _reg.register_component<Controllable>();
    _reg.register_component<Animatable>();
    _reg.register_component<Parallax>();
    _reg.register_component<FollowPath>();
    _reg.register_component<Shootable>();

    _reg.add_system<Position, Velocity, Controllable>(position_system);
    _reg.add_system<Shootable>(shoot_system);
    _reg.add_system<Position, Hitbox>(collision_system);
}

Engine::~Engine()
{
}

registry Engine::get_registry() 
{
    return _reg;
}

void Engine::loadModules(std::string libName, MODULE_TYPE type)
{
    LoadLibrary library(libName);

    void *lib = library.loadLibrary();
    switch (type) {
        case MODULE_TYPE::GAME: {
            create_d_game newGame = (create_d_game)library.getFunction(lib, "createLibrary");
            _game = newGame();
            break;
        }
    }
}

ServerData Engine::buildServerData(size_t id, uint16_t inputs[10]) 
{
    ServerData data;

    auto &positions = _reg.get_components<Position>();
    auto &velocities = _reg.get_components<Velocity>();
    for (int i = 0; i < 4; i++) {
        data.posX[i] = 0;
        data.posY[i] = 0;
        for (int j = 0; j < 10; j++) {
            data.inputs[i][j] = 0;
        }

        if (i >= _game->getPLayers().size()) {
            data.entities[i] = -1;
            continue;
        }
        
        data.entities[i] = _game->getPLayers().at(i);
        auto const &pos = positions[_game->getPLayers().at(i)];
        if (pos) {
            data.posX[i] = pos.value()._x;
            data.posY[i] = pos.value()._y;
        }

        if (_game->getPLayers().at(i) == id) {
            for (int j = 0; j < 10; j++) {
                data.inputs[i][j] = inputs[j];
            }
        }
    }

    return data;
}

void Engine::sendData(ServerData data) 
{
    char *buffer = _network.getProtocol().serialiseData<ServerData>(data);
    ServerData serverData = _network.getProtocol().readServer(buffer);

    for (int it = 0; it < _network.getEndpoints().size(); it++) {
        _network.udpSend<ServerData>(buffer, _network.getEndpoints().at(it));
    }
}

void Engine::updateRegistry(ClientData data)
{
    GameData gameData;

    gameData.entity = data.entity;
    memcpy(gameData.inputs, data.inputs, sizeof(uint16_t) * 10);

    _game->updateRegistry(_reg, gameData);
    sendData(buildServerData(data.entity, data.inputs));
}

void Engine::runNetwork() 
{
    _network.UDPReceiveServer(std::bind(&Engine::updateRegistry, this, std::placeholders::_1));
    _network.getIOService().run();
}

void Engine::runServerCommandLine()
{
    std::string line;

    std::cout << "Welcome to Server CLI !" << std::endl;
    CLI::displayHelp();
    while (1) {
        std::cout << "$> ";
        std::getline(std::cin, line);
        if (line.empty()) {
            std::cout << "please type a command. use `help` to see commands available." << std::endl;
            continue;
        }
        CLI::launchSearchedFunction(line, _reg);
    }
}

void Engine::runGame() 
{
    while (1) {
        _reg.run_systems();
    }
}

void Engine::run() 
{
    _game->initGame(_reg);

    std::thread gameThread(&Engine::runGame, this);
    std::thread networkThread(&Engine::runNetwork, this);
    std::thread serverCliThread(&Engine::runServerCommandLine, this);

    gameThread.join();
    networkThread.join();
    serverCliThread.join();
}
