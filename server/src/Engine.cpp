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
}

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _network(io_service, host, port)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();

    _reg.add_system<Position, Velocity>(position_system);
}

Engine::~Engine()
{
}

registry Engine::get_registry() {
    return _reg;
}

entity Engine::create_friendly_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

    Drawable draw;
    Position pos;
    Velocity vel;
    Controllable contr;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);
    
    _reg.add_component<Controllable>(ret, std::move(contr));

    return ret;
}

entity Engine::create_enemy_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{    
    entity ret(id);

    Drawable draw;
    Position pos;
    Velocity vel;
    Controllable contr;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);

    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, 45, col);
    
    return ret;
}

ClientData Engine::buildClientData(EntityEvent entityEvent) {
    ClientData clientData;
    if (entityEvent.entity == -1) {
        clientData.entity = -1;
        return clientData;
    }
    Position &pos = _reg.get_components<Position>()[1].value();
    int size = 0;
    clientData.entity = entityEvent.entity;
    clientData.posX = pos._x;
    clientData.posY = pos._y;
    for (auto &it : entityEvent.events) {
        switch (it) {
        case GAME_EVENT::LEFT:
            clientData.directions[size] = GAME_EVENT::LEFT;
            size++;
            break;
        case GAME_EVENT::RIGHT:
            clientData.directions[size] = GAME_EVENT::RIGHT;
            size++;
            break;
        case GAME_EVENT::UP:
            clientData.directions[size] = GAME_EVENT::UP;
            size++;
            break;
        case GAME_EVENT::DOWN:
            clientData.directions[size] = GAME_EVENT::DOWN;
            size++;
            break;
        case GAME_EVENT::SHOOT:
            clientData.shoot = true;
            break;
        default:
            break;
        }
    }
    return clientData;
}

void Engine::UpdateRegistery(ClientData newData)
{
    for (int i = 0; i != 4; ++i) {
        if (_reg.entity_from_index(newData.entity[i])) {

        }
        // if (newData.entity[i]
    }
}

void Engine::run_game() {
    while (1) {
        _reg.run_systems();
        _network.UDPReceiveClient(std::bind(&printMonCul, std::placeholders::_1));
    }
}

void Engine::sendData(ServerData data) {
    char *buffer = _network._protocol.serialiseData<ServerData>(data);
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}