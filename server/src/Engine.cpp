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

void Engine::create_entity(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY);
}

void Engine::create_player(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY);
    // can shot component

    _players.emplace_back(newEntity);
}

void Engine::create_enemy_entity(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY);
    // can shot component
}

ServerData Engine::buildServerData() 
{
    ServerData data;

    auto &positions = _reg.get_components<Position>();
    auto &velocities = _reg.get_components<Velocity>();
    for (int i = 0; i < 4; i++) {
        data.posX[i] = 0;
        data.posY[i] = 0;
        data.directionsX[i] = 0;
        data.directionsY[i] = 0;

        if (i >= _players.size()) {
            data.entities[i] = -1;
            continue;
        }
        data.entities[i] = _players.at(i);
        auto const &pos = positions[_players.at(i)];
        if (pos) {
            data.posX[i] = pos.value()._x;
            data.posY[i] = pos.value()._y;
        }

        auto const &vel = velocities[_players.at(i)];
        if (vel) {
            data.directionsX[i] = vel.value()._vx;
            data.directionsY[i] = vel.value()._vy;
        }
    }
    printf("CREATE SERVER DATA:\n");
    printServerData(data);
    printf("\n");
    return data;
}

void Engine::sendData(ServerData data) 
{
    char *buffer = _network._protocol.serialiseData<ServerData>(data);
    ServerData serverData = _network._protocol.readServer(buffer);

    for (int it = 0; it < _network._endpoints.size(); it++) {
        std::cout << _network._endpoints[it].address().to_string() << std::endl;
        _network.udpSend<ServerData>(buffer, _network._endpoints.at(it));
    }
}

void Engine::updateRegistry(ClientData data)
{
    printf("UPDATE SERVER REG\n");
    printClientData(data);
    printf("\n");
    if (!_reg.is_entity_alive(data.entity)) {
        printf("new PLayer\n");
        create_player(_reg.spawn_entity(), sf::Color::Blue, data.directionsX, data.directionsY, data.posX, data.posY);
    } else {
        // _reg.get_components<Position>()[data.entity].value().set_component(data.posX, data.posY);
        _reg.get_components<Velocity>()[data.entity].value().set_component(data.directionsX, data.directionsY);
    }
    sendData(buildServerData());
}

void Engine::runNetwork() 
{
    _network.UDPReceiveServer(std::bind(&Engine::updateRegistry, this, std::placeholders::_1));
    _network.getIOService().run();
}

void Engine::runGame() 
{
    while (1) {
        _reg.run_systems();
    }
}

void Engine::run() 
{
    create_entity(_reg.spawn_entity_by_id(0), sf::Color::Red, 0, 0, 100, 100);
    std::thread gameThread(&Engine::runGame, this);

    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}