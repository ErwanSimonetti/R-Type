/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _reg(), _network(io_service, host, port)
{
    loadModules("./modules/sfml.so", MODULE_TYPE::GRAPHIC);
    loadModules("./modules/rtype.so", MODULE_TYPE::GAME);


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

ClientData Engine::buildClientData(Events events)
{
    ClientData clientData;
    
    if (events.inputs.size() == 0) {
        clientData.entity = -1;
        return clientData;
    }

    clientData.entity = _game->getPLayers().at(0);
    for (int i = 0; i < 10; i++) {
        clientData.inputs[i] = 0;
    }

    int index = 0;
    for (auto &it : events.inputs) {
        if (index >= 10)
            break;

        clientData.inputs[index] = it;
        index++;
    }

    // printf("CREATE Client DATA:\n");
    // printClientData(clientData);
    // printf("\n");
    return clientData;
}

void Engine::sendData(ClientData data) 
{
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
    // printf("\n");

    GameData gameData[4];

    for (int i = 0; i < 4; i++) {
        gameData[i].entity = data.entities[i];
        gameData[i].posX = data.posX[i];
        gameData[i].posY = data.posY[i];
        memcpy(gameData[i].inputs, data.inputs[i], sizeof(uint16_t) * 10);
    }

    _game->updateRegistry(_reg, gameData);
}

void Engine::runGame() 
{
    Events evt;
    while (1) {
        _reg.run_systems();
        evt = _graphic->run_graphic(_reg);
        if (std::find(evt.gameEvents.begin(), evt.gameEvents.end(), GAME_EVENT::WINDOW_CLOSE) != evt.gameEvents.end()) {
            return;
        }
        _game->run_gameLogic(_reg, evt);
        ClientData clientData = buildClientData(evt);
        if(clientData.entity == -1)
            continue;
        sendData(clientData);
    }
}

void Engine::connectToServer()
{
    ClientData clientData;

    clientData.entity = -1;
    for (int i = 0; i < 10; i++) {
        clientData.inputs[i] = 0;
    }

    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), false);
    sendData(clientData);
}

void Engine::run() 
{
    _game->initGame(_reg);
    connectToServer();
    std::thread gameThread(&Engine::runGame, this);

  // Start the network handler in a separate thread
    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}