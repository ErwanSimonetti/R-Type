/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &port) : _reg(), _game(width, height), _network(io_service, port)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();

    _reg.add_system<Position, Velocity>(position_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
}

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _game(width, height), _network(io_service, host, port)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Controllable>();
    _reg.register_component<FollowPath>();

    _reg.add_system<Position, Velocity>(position_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
    _reg.add_system<Position, Velocity, FollowPath>(followPathSystem);
}

Engine::~Engine()
{
}

registry Engine::get_registry() {
    return _reg;
}

entity Engine::create_player(int id, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{
    entity ret(id);

    _reg.emplace_component<Position>(ret, posX, posY);
    _reg.emplace_component<Velocity>(ret, 1, 1, speedX, speedY);
    _reg.emplace_component<Drawable>(ret, 45, col);
    _reg.emplace_component<Controllable>(ret);

    return ret;
}

entity Engine::create_enemy_entity(int id, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY) // FIXME: replace positions by just the name of the file handling the path
{
    entity ret(id);

    _reg.emplace_component<Position>(ret, posX, posY);
    _reg.emplace_component<Velocity>(ret, 1, 1, speedX, speedY);
    _reg.emplace_component<Drawable>(ret, 45, col);
    _reg.emplace_component<FollowPath>(ret, "middle_diagonal");

    return ret;
}

ClientData Engine::buildClientData(EntityEvent entityEvent) 
{
    ClientData clientData;
    printf("%d\n", entityEvent.entity);
    if (entityEvent.entity == -1) {
        printf("hello\n");
        clientData.entity = -1;
        return clientData;
    }
    printf("jaj\n");
    Position &pos = _reg.get_components<Position>()[1].value();
    printf("joj\n");
    int size = 0;
    clientData.entity = entityEvent.entity;
    clientData.posX = pos._x;
    clientData.posY = pos._y;
    for (int i = 0; i < 4; i++) {
        clientData.directions[i] = 0;
    }
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

void Engine::sendData(ClientData data) 
{
    char *buffer = _network._protocol.serialiseData<ClientData>(data);
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}

void Engine::updateRegistry(ServerData data)
{
    for (int i = 0; i < 4; i++) {
        if (!_reg.is_entity_alive(data.entities[i])) {
            create_entities(data.entities[i], sf::Color::Blue, 0, 0, data.posX[i], data.posY[i]);
            return;
        }
        _reg.get_components<Position>()[newData.entity].value().build_component(data.posX[i], data.posY[i]);
        _reg.get_components<Velocity>()[data.entities[i]].value().build_component(data.directionsX[i], data.directionsY[i]);
    }
}

void Engine::run_game() 
{
    _network.UDPReceiveServer(std::bind(&Engine::printMonCul, this, std::placeholders::_1));
    while (1) {
        ClientData clientData = buildClientData(_game.gameLoop(_reg));
        printf("%d\n", clientData.entity);
        if(clientData.entity == -1)
            continue;
        printf("send\n");
        sendData(clientData);
    }
}