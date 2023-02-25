/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _network(io_service, host, port), _player(0)
{
    loadModules("./modules/libsfml.so", MODULE_TYPE::GRAPHIC);
    loadModules("./modules/librtype.so", MODULE_TYPE::GAME);


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
    // _reg.add_system<Position, Velocity, Controllable>(position_system);
    _reg.add_system<Shootable>(shoot_system);
    _reg.add_system<Animatable, Position, Parallax>(parallax_system);
    _reg.add_system<Animatable, Drawable>(std::bind(&IGraphic::animation_system, _graphic, std::placeholders::_1, std::placeholders::_2));
    _reg.add_system<Position, Drawable>(std::bind(&IGraphic::draw_system, _graphic, std::placeholders::_1, std::placeholders::_2));
    // _reg.add_system<Position, Velocity, FollowPath>(followPathSystem);
}

Engine::~Engine()
{
}

registry &Engine::get_registry()
{
    return _reg;
}

void Engine::loadModules(std::string libName, MODULE_TYPE type)
{
    LoadLibrary library(libName);

    void *lib = library.loadLibrary();
    switch (type) {
        case MODULE_TYPE::GRAPHIC: {
            create_d_graphic newGraphicLibrary = (create_d_graphic)library.getFunction(lib, "createLibrary");  
            _graphic = newGraphicLibrary();
            break;
        }
        case MODULE_TYPE::GAME: {
            create_d_game newGameLibrary = (create_d_game)library.getFunction(lib, "createLibrary");
            _game = newGameLibrary();
            break;
        }
    }
}

ClientData Engine::buildClientData(EntityEvent entityEvent) 
{
    ClientData clientData;
    
    if (entityEvent.entity == -1) {
        clientData.xVelocity = 0;
        clientData.yVelocity = 0;
        clientData.entity = -1;
        return clientData;
    }
    Position &pos = _reg.get_components<Position>()[entityEvent.entity].value();
    int size = 0;
    clientData.entity = entityEvent.entity;
    // clientData.posX = pos._x;
    // clientData.posY = pos._y;
    clientData.xVelocity = entityEvent.xVelocity;
    clientData.yVelocity = entityEvent.yVelocity;
    clientData.hasShot = 0;
    
    // std::cout << "x velocity client = " << clientData.xVelocity << std::endl;
    // std::cout << "y velocity client = " << clientData.yVelocity << std::endl;
    for (auto &it : entityEvent.events) {
        switch (it) {
            case GAME_EVENT::SHOOT:
                clientData.hasShot = 1;
                break;
            default:
                break;
        }
    }
    // printClientData(clientData);
    // printf("\n");
    return clientData;
}

void Engine::sendData(ClientData data) 
{
    std::cout << "SENDING DATA !" << std::endl;
    std::cout << "x velocity = " << data.xVelocity << std::endl;
    std::cout << "y velocity = " << data.yVelocity << std::endl;

    char *buffer = _network.getProtocol().serialiseData<ClientData>(data);
    _network.udpSend<ClientData>(buffer, _network.getServerEndpoint());
}

void Engine::runNetwork() 
{
    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), true);
    _network.getIOService().run();
}

void Engine::updateRegistry(ServerData data)
{
    // printf("UPDATE Client REG:\n");
    // printServerData(data);
    printf("\n");

    GameData gameData;

    for (int i = 0; i < 4; i++) {
        gameData.entities[i] = data.entities[i];
        gameData.posX[i] = data.posX[i];
        gameData.posY[i] = data.posY[i];
        gameData.xVelocity[i] = data.xVelocity[i];
        gameData.yVelocity[i] = data.yVelocity[i];
        gameData.hasShot[i] = data.hasShot[i];
    }

    _game->updateRegistry(_reg, gameData);
}

void Engine::runGame() 
{
    EntityEvent evt;
    while (1) {
        _reg.run_systems();
        evt = _graphic->run_graphic(_reg);
        // if (std::find(evt.events.begin(), evt.events.end(), GAME_EVENT::WINDOW_CLOSE) != evt.events.end()) {
        //     return;
        // }
        _game->run_gameLogic(_reg, evt);
        ClientData clientData = buildClientData(evt);
        // if(clientData.entity == -1)
        //     continue;
        sendData(clientData);
    }
}

void Engine::connectToServer()
{
    ClientData clientData;

    clientData.xVelocity = 0;
    clientData.yVelocity = 0;
    clientData.entity = -1;
    clientData.hasShot = 0;
    clientData.posX = 0;
    clientData.posY = 0;

    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), false);
    sendData(clientData);
}

void Engine::run() 
{
    _game->initGame(_reg);
    // create_player(_reg.spawn_entity(), 10, 10, 100, 100);
    // _game->create_enemy_entity(_reg, _reg.spawn_entity(), -10, 0, 1900, 200);

    connectToServer();
    std::thread gameThread(&Engine::runGame, this);

  // Start the network handler in a separate thread
    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}