/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &port) : _reg(), _network(io_service, port)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();

    _reg.add_system<Position, Velocity>(position_system);
    // boost::asio::io_service io_service;
}

Engine::~Engine()
{
}

registry Engine::get_registry() 
{
    return _reg;
}

entity Engine::create_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

    Drawable draw;
    Position pos;
    Velocity vel;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);

    return ret;
}

entity Engine::create_player(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

    Drawable draw;
    Position pos;
    Velocity vel;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);

    _player.emplace_back(ret);
    return ret;
}

entity Engine::create_enemy_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

    Drawable draw;
    Position pos;
    Velocity vel;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    return ret;
}

void Engine::updateRegistry(ClientData newData)
{
    std::cout << "update server registry" << std::endl;
    if (!_reg.is_entity_alive(newData.entity)) {
        create_player(newData.entity, sf::Color::Blue, 0, 0, newData.posX, newData.posY);
        return;
    }
    _reg.get_components<Position>()[newData.entity].value().build_component(newData.posX, newData.posY);

    _reg.get_components<Velocity>()[newData.entity].value().build_component(newData.directionsX, newData.directionsY);
    sendData(createServerData());
}


ServerData Engine::createServerData() 
{
    ServerData data;
    auto &positions = _reg.get_components<Position>();
    for (int i = 0; i < _player.size(); i++) {
        data.entities[i] = _player.at(i);
        auto const &pos = positions[_player.at(i)];
        if (pos) {
            data.posX[i] = pos.value()._x;
            data.posY[i] = pos.value()._y;
        }
    }
    return data;
}

// void printMonCul(ClientData clientData) {
//     std::cerr << "⠄⠄⠸⣿⣿⢣⢶⣟⣿⣖⣿⣷⣻⣮⡿⣽⣿⣻⣖⣶⣤⣭⡉⠄⠄⠄⠄⠄\n⠄⠄⠄⢹⠣⣛⣣⣭⣭⣭⣁⡛⠻⢽⣿⣿⣿⣿⢻⣿⣿⣿⣽⡧⡄⠄⠄⠄\n⠄⠄⠄⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣶⣌⡛⢿⣽⢘⣿⣷⣿⡻⠏⣛⣀⠄⠄\n⠄⠄⠄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⠙⡅⣿⠚⣡⣴⣿⣿⣿⡆⠄\n⠄⠄⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠄⣱⣾⣿⣿⣿⣿⣿⣿⠄\n⠄⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢸⣿⣿⣿⣿⣿⣿⣿⣿⠄\n⠄⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠣⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄\n⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠑⣿⣮⣝⣛⠿⠿⣿⣿⣿⣿⠄\n⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠄\n⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠄⠄⠄⠄⢹⣿⣿⣿⣿⣿⣿⣿⣿⠁⠄\n⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠄⠄⠄⠄⠄⠸⣿⣿⣿⣿⣿⡿⢟⣣⣀\n";
//     std::cerr << "|" << clientData.entity << "|" << "\n";
//     std::cerr << "|" << clientData.posX << " " << clientData.posY << "|" << "\n";
// }

void Engine::sendData(ServerData data) 
{
    char *buffer = _network._protocol.serialiseData<ServerData>(data);
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}

void Engine::runNetwork() 
{
    _network.UDPReceiveServer(std::bind(&Engine::updateRegistry, this, std::placeholders::_1));
    // printf("network\n");
    _network.getIOService().run();
}

void Engine::runGame() 
{
    // printf("whileisOK\n");
    // std::cout << "hola" << std::endl;
    while (1) {
        _reg.run_systems();
    }
}

void Engine::run() 
{

    std::thread gameThread(&Engine::runNetwork, this);

  // Start the network handler in a separate thread
    std::thread networkThread(&Engine::runGame, this);

    gameThread.join();
    networkThread.join();
    // _network.getIOService().run();
    printf("jaj\n");
}