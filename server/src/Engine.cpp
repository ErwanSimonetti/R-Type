/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include <unistd.h>
#include "Engine.hpp"

int TICK_DURATION = 50000;

Engine::Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port, const std::string &graphicLibrary) : _reg(), _network(io_service, port)
{
    std::cout << "entering server engine" << std::endl;
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();
    _reg.register_component<Shootable>();
}

Engine::~Engine()
{
}

registry Engine::get_registry() 
{
    return _reg;
}

void Engine::create_entity(entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY);
}

void Engine::create_player(entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
{
    Controllable contr;

    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velX);
    _reg.add_component<Controllable>(newEntity, std::move(contr));
    // can shot component
    Player newPlayer{newEntity, false};
    _players.emplace_back(newPlayer);
}

void Engine::create_enemy_entity(entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY)
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
        data.xVelocity[i] = 0;
        data.yVelocity[i] = 0;
        data.hasShot[i] = 0;

        if (i >= _players.size()) {
            data.entities[i] = -1;
            continue;
        }
        
        data.entities[i] = _players.at(i).id;
        auto const &pos = positions[_players.at(i).id];
        if (pos) {
            data.posX[i] = pos.value()._x;
            data.posY[i] = pos.value()._y;
        }

        if (_players.at(i).hasShot) {
            data.hasShot[i] = 1;
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
    if (!_reg.is_entity_alive(data.entity)) {
        create_player(_reg.spawn_entity(), data.xVelocity, data.yVelocity, data.posX, data.posY);
    } else {
        std::cout << "x velocity before setting component = " << data.xVelocity << std::endl;
        std::cout << "y velocity before setting component = " << data.yVelocity << std::endl;
        _reg.get_components<Velocity>()[data.entity].value().set_component(data.xVelocity, data.yVelocity);
        for (int i = 0; i < _players.size(); i++) {
            if (_players.at(i).id == data.entity) {
                    if (data.hasShot) {
                        create_entity(_reg.spawn_entity(), 0, 0, data.posX, data.posX);
                        _players.at(i).hasShot = true;
                    } else
                        _players.at(i).hasShot = false;
            }
        }
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
        if (tickPosition())
            position_system(_reg, _reg.get_components<Position>(), _reg.get_components<Velocity>(), _reg.get_components<Controllable>());
    }
}

void Engine::run() 
{
    create_entity(_reg.spawn_entity_by_id(0), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);
    create_entity(_reg.spawn_entity(), 0, 0, 100, 100);

    std::thread gameThread(&Engine::runGame, this);
    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}

bool Engine::tickPosition()
{
    static clock_t tick_position = std::clock();
    clock_t current_tick = std::clock();

    if (current_tick - tick_position > TICK_DURATION) {
        tick_position = std::clock();
        return true;
    }
    return false;
}