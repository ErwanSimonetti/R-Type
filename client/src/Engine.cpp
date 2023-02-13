/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _game(width, height), _network(io_service, host, port), _player(0)
{
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

    _reg.add_system<Position, Hitbox>(collision_system);
    _reg.add_system<Position, Velocity, Controllable>(position_system);
    _reg.add_system<Shootable>(shoot_system);
    _reg.add_system<Animatable, Position, Parallax>(parallax_system);
    _reg.add_system<Animatable, Drawable>(animation_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
    // _reg.add_system<Position, Velocity, FollowPath>(followPathSystem);
}

Engine::~Engine()
{
}

registry &Engine::get_registry() {
    return _reg;
}


void Engine::create_entity(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, speedX, speedY, 0, 0);
    _reg.emplace_component<Drawable>(newEntity, SHIP);
    _reg.emplace_component<Animatable>(newEntity, 90);
}

void Engine::create_player(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{
    Controllable contr;

    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, 0, 0, speedX, speedY);
    _reg.emplace_component<Drawable>(newEntity, SHIP);
    _reg.add_component<Controllable>(newEntity, std::move(contr));
    _reg.emplace_component<Animatable>(newEntity, 90);
    _reg.emplace_component<Hitbox>(newEntity, posX+45, posY+45, PLAYER);
    _reg.emplace_component<Shootable>(newEntity);
    // _player = newEntity;
    // can shoot component

}

void Engine::create_enemy_entity(entity newEntity, const uint16_t speedX, const uint16_t speedY, const uint16_t posX, const uint16_t posY)
{    
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Velocity>(newEntity, speedX, speedY, 0, 0);
    _reg.emplace_component<Drawable>(newEntity, ENEMYSHIP);
    _reg.emplace_component<Hitbox>(newEntity, posX+45, posY+45, ENEMY);
    _reg.emplace_component<FollowPath>(newEntity, "middle_diagonal");
    // can shoot component
}

void Engine::create_parallax(entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj) 
{
    _reg.emplace_component<Position>(newEntity, posX, posY);
    _reg.emplace_component<Drawable>(newEntity, obj);
    _reg.emplace_component<Animatable>(newEntity, speed);
    _reg.emplace_component<Parallax>(newEntity, -1920, 1920);
}

void Engine::create_projectile(entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY)
{
    Drawable draw; 
    Position pos;
    Velocity vel;
    Hitbox hbx;
    Pet pet;
    Animatable anim;

    int16_t posX =_reg.get_components<Position>()[parentId].value()._x;
    int16_t posY =_reg.get_components<Position>()[parentId].value()._y;
    pos.set_component(posX, posY + 3);
    _reg.add_component<Position>(newEntity, std::move(pos));

    vel.set_component(velX, velY, 0, 0);
    _reg.add_component<Velocity>(newEntity, std::move(vel));

    draw.set_component(BULLET);
    _reg.add_component<Drawable>(newEntity, std::move(draw));

    pet.set_component(entity(parentId));
    _reg.add_component<Pet>(newEntity, std::move(pet));

    _reg.add_component<Hitbox>(newEntity, std::move(hbx));
    _reg.emplace_component<Hitbox>(newEntity, posX+10, posY+10, PROJECTILE);

    anim.set_component(10);
    _reg.add_component<Animatable>(newEntity, std::move(anim));
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
    clientData.hasShot = 0;

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
            clientData.hasShot = 1;
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
    char *buffer = _network.getProtocol().serialiseData<ClientData>(data);
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}

void Engine::updateRegistry(ServerData data)
{
    printf("UPDATE Client REG:\n");
    printServerData(data);
    printf("\n");
    for (int i = 0; i < 4; i++) {
        if (data.entities[i] == -1) {
            continue;
        }
        if (_player == 0 && (i == 3 || data.entities[i + 1] == -1)) {
            entity newEntity = _reg.spawn_entity_by_id(data.entities[i]);
            create_player(newEntity, 10, 10, data.posX[i], data.posY[i]);
            _player = newEntity;
            printf("Our Player\n");
            continue;
        }
        if (!_reg.is_entity_alive(data.entities[i])) {
            printf("New player\n");
            create_entity(_reg.spawn_entity_by_id(data.entities[i]), 0, 0, data.posX[i], data.posY[i]);
        } else {
            _reg.get_components<Position>()[data.entities[i]].value().set_component(data.posX[i], data.posY[i]);
            _reg.get_components<Velocity>()[data.entities[i]].value().set_component(data.directionsX[i], data.directionsY[i], 10, 10);
            if (data.hasShot[i] == 1 && data.entities[i] != _player) {
                create_projectile(_reg.spawn_entity(), data.entities[i], 15, 0);
            }
        }   
    }
    printf("end of this shit\n");
}

void Engine::runNetwork() 
{
    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), true);
    _network.getIOService().run();
}

void Engine::runGame() 
{
    EntityEvent evt;
    while (1) {
        evt = _game.gameLoop(_reg);
        if (std::find(evt.events.begin(), evt.events.end(), GAME_EVENT::SHOOT) != evt.events.end()) {
            create_projectile(_reg.spawn_entity(), evt.entity, 15, 0);
        }
        ClientData clientData = buildClientData(evt);
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
    clientData.hasShot = 0;
    clientData.posX = 0;
    clientData.posY = 0;

    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), false);
    sendData(clientData);
    // _network.getIOService().run();
}

void Engine::run() 
{
    create_entity(_reg.spawn_entity_by_id(0), 0, 0, 100, 100);
    create_parallax(_reg.spawn_entity(), 1920, 0, 3, PARA_1);
    create_parallax(_reg.spawn_entity(), 0, 0, 3, PARA_1);
    create_parallax(_reg.spawn_entity(), 1920, 0, 6, PARA_2);
    create_parallax(_reg.spawn_entity(), 0, 0, 6, PARA_2);
    create_parallax(_reg.spawn_entity(), 1920, 0, 9, PARA_3);
    create_parallax(_reg.spawn_entity(), 0, 0, 9, PARA_3);
    create_parallax(_reg.spawn_entity(), 1920, 346, 12, PARA_4);
    create_parallax(_reg.spawn_entity(), 0, 346, 12, PARA_4);
    create_enemy_entity(_reg.spawn_entity(), -20, 0, 1900, 200);
    // create_player(_reg.spawn_entity(), 10, 10, 0, 0);

    connectToServer();

    std::thread gameThread(&Engine::runGame, this);

  // Start the network handler in a separate thread
    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}