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
    _reg.register_component<Pet>();
    _reg.register_component<Hitbox>();
    _reg.register_component<Controllable>();
    _reg.register_component<Animatable>();
    _reg.register_component<Parallax>();

    _reg.add_system<Position, Hitbox>(collision_system);
    _reg.add_system<Position, Velocity>(position_system);
    _reg.add_system<Animatable, Position, Parallax>(parallax_system);
    _reg.add_system<Animatable, Drawable>(animation_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
}

Engine::Engine(uint16_t width, uint16_t height, boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _game(width, height), _network(io_service, host, port)
{
    _reg.register_component<Position>();
    _reg.register_component<Velocity>();
    _reg.register_component<Drawable>();
    _reg.register_component<Pet>();
    _reg.register_component<Hitbox>();
    _reg.register_component<Controllable>();
    _reg.register_component<Animatable>();
    _reg.register_component<Parallax>();

    _reg.add_system<Position, Hitbox>(collision_system);
    _reg.add_system<Position, Velocity>(position_system);
    _reg.add_system<Animatable, Position, Parallax>(parallax_system);
    _reg.add_system<Animatable, Drawable>(animation_system);
    _reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &_game, std::placeholders::_1, std::placeholders::_2));
}

Engine::~Engine()
{
}

registry Engine::get_registry() {
    return _reg;
}

entity Engine::create_parallax(const int16_t id, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj) 
{
    entity ret = _reg.spawn_entity_by_id(id);

    Drawable draw;
    Position pos;
    Animatable anim;
    Parallax para;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, obj);

    _reg.add_component<Animatable>(ret, std::move(anim));
    _reg.emplace_component<Animatable>(ret, speed);

    _reg.add_component<Parallax>(ret, std::move(para));
    _reg.emplace_component<Parallax>(ret, -1920, 1920);

    return ret;
}

entity Engine::create_entity(int id, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret = _reg.spawn_entity_by_id(id);

    Drawable draw;
    Position pos;
    Velocity vel;
    Hitbox hbx;


    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    _reg.add_component<Hitbox>(ret, std::move(hbx));
    _reg.emplace_component<Hitbox>(ret, posX+45, posY+45);
    
    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, SHIP);

    return ret;
}

entity Engine::create_player(int id, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY)
{
    entity ret = _reg.spawn_entity_by_id(id);

    Drawable draw;
    Position pos;
    Velocity vel;
    Hitbox hbx;
    Controllable contr;
    Animatable anim;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, velY);
    
    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, SHIP);
    
    _reg.add_component<Animatable>(ret, std::move(anim));
    _reg.emplace_component<Animatable>(ret, 90);

    _reg.add_component<Hitbox>(ret, std::move(hbx));
    _reg.emplace_component<Hitbox>(ret, posX+45, posY+45);

    _reg.add_component<Controllable>(ret, std::move(contr));
    return ret;
}


entity Engine::create_projectile(int parentId, const uint16_t velX, const uint16_t velY)
{
    entity ret(_reg.spawn_entity());

    Drawable draw; 
    Position pos;
    Velocity vel;
    Hitbox hbx;
    Pet pet;
    Animatable anim;

    int16_t posX =_reg.get_components<Position>()[parentId].value()._x;
    int16_t posY =_reg.get_components<Position>()[parentId].value()._y;
    pos.set_component(posX, posY + 3);
    _reg.add_component<Position>(ret, std::move(pos));
   
    vel.set_component(velX, velY);
    _reg.add_component<Velocity>(ret, std::move(vel));
   
    draw.set_component(BULLET);
    _reg.add_component<Drawable>(ret, std::move(draw));
   
    pet.set_component(_reg.entity_from_index(parentId));
    _reg.add_component<Pet>(ret, std::move(pet));

    _reg.add_component<Hitbox>(ret, std::move(hbx));
    _reg.emplace_component<Hitbox>(ret, posX+10, posY+10);

    anim.set_component(10);
    _reg.add_component<Animatable>(ret, std::move(anim));
    
    return ret;
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

    for (auto &it : entityEvent.events) {
        switch (it) {
        case GAME_EVENT::LEFT:
            clientData.directionsX = -1;
            size++;
            break;
        case GAME_EVENT::RIGHT:
            clientData.directionsX = 1;
            size++;
            break;
        case GAME_EVENT::UP:
            clientData.directionsY = -1;
            size++;
            break;
        case GAME_EVENT::DOWN:
            clientData.directionsY = 1;
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

entity Engine::create_enemy_entity(int id, const int16_t velX, const uint16_t posX, const uint16_t posY)
{    
    entity ret = _reg.spawn_entity_by_id(id);

    Drawable draw;
    Position pos;
    Velocity vel;
    Hitbox hbx;

    _reg.add_component<Position>(ret, std::move(pos));
    _reg.emplace_component<Position>(ret, posX, posY);

    _reg.add_component<Velocity>(ret, std::move(vel));
    _reg.emplace_component<Velocity>(ret, velX, 0);

    _reg.add_component<Hitbox>(ret, std::move(hbx));
    _reg.emplace_component<Hitbox>(ret, posX+45, posY+45);

    _reg.add_component<Drawable>(ret, std::move(draw));
    _reg.emplace_component<Drawable>(ret, SHIP);

    return ret;
}

void Engine::sendData(ClientData data) 
{
    char *buffer = _network._protocol.serialiseData<ClientData>(data);
    std::cout << _network.getServerEndpoint() << std::endl;
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}

void Engine::updateRegistry(ServerData data)
{
    for (int i = 0; i < 4; i++) {
        if (!_reg.is_entity_alive(data.entities[i])) {
            create_entity(data.entities[i], 0, 0, data.posX[i], data.posY[i]);
            return;
        }
        _reg.get_components<Position>()[data.entities[i]].value().set_component(data.posX[i], data.posY[i]);
        _reg.get_components<Velocity>()[data.entities[i]].value().set_component(data.directionsX[i], data.directionsY[i]);
    }
    std::cout << "update client registry" << std::endl;
}

void Engine::runNetwork() 
{
    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1));
    _network.getIOService().run();
}

void Engine::runGame() 
{
    EntityEvent evt;
    while (1) {
        evt = _game.gameLoop(_reg);
        if (std::find(evt.events.begin(), evt.events.end(), GAME_EVENT::SHOOT) != evt.events.end()) {
            create_projectile(evt.entity, 15, 0);
        }
        ClientData clientData = buildClientData(evt);
        if(clientData.entity == -1)
            continue;
        // printf("send\n");
        // sendData(clientData);
    }
}

void Engine::run() 
{
    std::thread gameThread(&Engine::runNetwork, this);

  // Start the network handler in a separate thread
    std::thread networkThread(&Engine::runGame, this);

    gameThread.join();
    //networkThread.join();
}