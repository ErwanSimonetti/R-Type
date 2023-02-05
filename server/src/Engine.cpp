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
    entity ret = _reg.spawn_entity_by_id(id);

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
    entity ret = _reg.spawn_entity_by_id(id);

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
    entity ret = _reg.spawn_entity_by_id(id);

    Drawable draw;
    Position pos;
    Velocity vel;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    return ret;
}

void Engine::updateRegistry(ClientData data)
{
    std::cout << "update server registry" << std::endl;
    if (!_reg.is_entity_alive(data.entity)) {
        printf("new PLayer\n");
        create_player(data.entity, sf::Color::Blue, data.directionsX, data.directionsY, data.posX, data.posY);
    } else {
        _reg.get_components<Position>()[data.entity].value().set_component(data.posX, data.posY);
        _reg.get_components<Velocity>()[data.entity].value().set_component(data.directionsX, data.directionsY);
    }
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
    std::cout << "bonjour oui" << std::endl;
    char *buffer = _network._protocol.serialiseData<ServerData>(data);
    // for (int it = 0; it < _network._endpoints.size(); it++) {
    //     std::cout << _network._endpoints[it].address().to_string() << std::endl;
    //     _network.udpSend<ClientData>(buffer, _network._endpoints.at(it));
    // }
    std::cout << "bonjour non" << std::endl;
}

void Engine::runNetwork() 
{
    printf("before UDPReceiveServer\n");
    _network.UDPReceiveServer(std::bind(&Engine::updateRegistry, this, std::placeholders::_1));
    printf("after UDPReceiveServer\n");
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

    // std::thread networkThread(&Engine::runGame, this);

    gameThread.join();
    // networkThread.join();
    // _network.getIOService().run();
    printf("jaj\n");
}