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
<<<<<<< HEAD
    // boost::asio::io_service io_service;
=======
}

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _network(io_service, host, port)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();

    _reg.add_system<Position, Velocity>(position_system);
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
}

Engine::~Engine()
{
}

<<<<<<< HEAD
registry Engine::get_registry() 
{
    return _reg;
}

void Engine::create_entity(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY, 0, 0);
}

void Engine::create_player(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY, 0, 0);
    // can shot component

    _players.emplace_back(newEntity);
}

void Engine::create_enemy_entity(entity newEntity, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, velX, velY, 0, 0);
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
            data.directionsX[i] = vel.value()._vX;
            data.directionsY[i] = vel.value()._vY;
        }
    }
    printf("CREATE SERVER DATA:\n");
    printServerData(data);
    printf("\n");
    return data;
}

void Engine::sendData(ServerData data) 
{
    char *buffer = _network.getProtocol().serialiseData<ServerData>(data);
    ServerData serverData = _network.getProtocol().readServer(buffer);

    for (int it = 0; it < _network.getEndpoints().size(); it++) {
        std::cout << _network.getEndpoints()[it].address().to_string() << std::endl;
        _network.udpSend<ServerData>(buffer, _network.getEndpoints().at(it));
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
        _reg.get_components<Velocity>()[data.entity].value().set_component(data.directionsX, data.directionsY, 0, 0);
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
=======
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
>>>>>>> 6be9af8 (feat(hierarchy) split the project in two section: client & server)
}