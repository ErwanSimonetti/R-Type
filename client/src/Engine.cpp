/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

// Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &port) : _reg(), _game(width, height), _network(io_service, port)
// {
//     _reg.register_component<Position>();
//     _reg.register_component<Velocity>();
//     _reg.register_component<Drawable>();
//     _reg.register_component<Controllable>();

//     _reg.add_system<Position, Velocity>(position_system);
//     _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
//     _player = entity(0);
// }

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _game(width, height), _network(io_service, host, port), _player(0)
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


void Engine::create_entity(entity newEntity, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, speedX, speedY);
    _reg.emplace_component<Drawable>(newEntity, 45, col);
}

void Engine::create_player(entity newEntity, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{
    Controllable contr;

    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, speedX, speedY);
    _reg.emplace_component<Drawable>(newEntity, 45, col);
    _reg.add_component<Controllable>(newEntity, std::move(contr));
    // can shoot component

}

void Engine::create_enemy_entity(entity newEntity, sf::Color col, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{    
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, speedX, speedY);
    _reg.emplace_component<Drawable>(newEntity, 45, col);
    _reg.emplace_component<FollowPath>(ret, "middle_diagonal");
    // can shoot component
}

ClientData Engine::buildClientData(EntityEvent entityEvent) 
{
    ClientData clientData;
    
    if (entityEvent.entity == -1) {
        clientData.entity = -1;
        return clientData;
    }
    Position &pos = _reg.get_components<Position>()[entityEvent.entity].value();
    int size = 0;
    clientData.entity = entityEvent.entity;
    clientData.posX = pos._x;
    clientData.posY = pos._y;
    clientData.directionsX = 0;
    clientData.directionsY = 0;

    for (auto &it : entityEvent.events) {
        switch (it) {
        case GAME_EVENT::LEFT:
            clientData.directionsX += -1;
            size++;
            break;
        case GAME_EVENT::RIGHT:
            clientData.directionsX += 1;
            size++;
            break;
        case GAME_EVENT::UP:
            clientData.directionsY += -1;
            size++;
            break;
        case GAME_EVENT::DOWN:
            clientData.directionsY += 1;
            size++;
            break;
        case GAME_EVENT::SHOOT:
            clientData.shoot = true;
            break;
        default:
            break;
        }
    }
    printf("CREATE Client DATA:\n");
    printClientData(clientData);
    printf("\n");
    return clientData;
}

void Engine::sendData(ClientData data) 
{
    char *buffer = _network._protocol.serialiseData<ClientData>(data);
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}

void Engine::updateRegistry(ServerData data)
{
    printf("UPDATE Client REG:\n");
    printServerData(data);
    printf("\n");
    bool isfirstEmpty = true;
    for (int i = 0; i < 4; i++) {
        if (data.entities[i] == -1) {
            continue;
        }
        if (isfirstEmpty && _player == 0 && (i == 3 || data.entities[i + 1] == -1)) {
            entity newEntity = _reg.spawn_entity_by_id(data.entities[i]);
            create_player(newEntity, sf::Color::Blue, data.directionsX[i], data.directionsY[i], data.posX[i], data.posY[i]);
            isfirstEmpty = false;
            _player = newEntity;
            printf("Our Player\n");
            continue;
        }
        if (!_reg.is_entity_alive(data.entities[i])) {
            printf("New player\n");
            create_entity(_reg.spawn_entity_by_id(data.entities[i]), sf::Color::Blue, 0, 0, data.posX[i], data.posY[i]);
        } else {
            _reg.get_components<Position>()[data.entities[i]].value().set_component(data.posX[i], data.posY[i]);
            _reg.get_components<Velocity>()[data.entities[i]].value().set_component(data.directionsX[i], data.directionsY[i]);
        }   
    }
}

void Engine::runNetwork() 
{
    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), true);
    _network.getIOService().run();
}

void Engine::runGame() 
{
    while (1) {
        ClientData clientData = buildClientData(_game.gameLoop(_reg));
        if(clientData.entity == -1)
            continue;
        sendData(clientData);
    }
}

void Engine::connectToServer()
{
    ClientData clientData;

    clientData.directionsX = 0;
    clientData.directionsY = 0;
    clientData.entity = -1;
    clientData.shoot = false;
    clientData.posX = 0;
    clientData.posY = 0;

    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), false);
    sendData(clientData);
    // _network.getIOService().run();
}

void Engine::run() 
{
    create_entity(_reg.spawn_entity_by_id(0), sf::Color::Red, 0, 0, 100, 100);
    // create_player(_reg.spawn_entity_by_id(1), sf::Color::Blue, 0, 0, 10, 10);
    connectToServer();

    std::thread gameThread(&Engine::runGame, this);

  // Start the network handler in a separate thread
    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}