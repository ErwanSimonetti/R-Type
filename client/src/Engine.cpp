/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"
#include "DeleteEntities.hpp"

Engine::Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port, const std::string &graphicModulePath, const std::string &gameModulePath) : _reg(), _network(io_service, host, port)
{
    loadModules(gameModulePath, MODULE_TYPE::GAME);

    _graphicPath = graphicModulePath;

    _clock = std::chrono::high_resolution_clock::now();
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
    _reg.register_component<Jump>();
    _reg.register_component<Gravity>();
    _reg.register_component<Stats>();
    _reg.register_component<DrawableText>();
    _reg.register_component<Particulable>();
    _reg.register_component<SoundEffect>();
    _reg.register_component<Cliquable>();

    _reg.add_system<Velocity, Hitbox, Gravity>(gravity_system);
    _reg.add_system<Position, Velocity, Hitbox>(collision_system);
    _reg.add_system<Position, Velocity, Hitbox, Jump, Gravity>(jump_system);
    _reg.add_system<Position, Velocity, Controllable, Hitbox>(position_system);
    _reg.add_system<Shootable>(shoot_system);
    _reg.add_system<Stats, Position, Pet>(entity_killing_system);
    _reg.add_system<Animatable, Position, Parallax>(parallax_system);
    _reg.add_system<Position, Velocity, FollowPath>(follow_path_system);
    _reg.add_system<Stats, DrawableText, Pet>(update_drawable_texts_system);
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
            create_d_graphic newGraphic = (create_d_graphic)library.getFunction(lib, "createLibrary");  
            _graphic = newGraphic();
            _graphic->loadModuleSystem(_reg);
            break;
        }
        case MODULE_TYPE::GAME: {
            create_d_game newGame = (create_d_game)library.getFunction(lib, "createLibrary");
            _game = newGame();
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

    clientData.entity = _game->getPlayers().at(0);
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

    return clientData;
}

void Engine::sendData(ClientData data) 
{
    std::vector<char> buffer;
    Header header{3};
    const char* headerBytes = _network.getProtocol().serialiseData<Header>(header);
    const char* dataBytes = _network.getProtocol().serialiseData<ClientData>(data);

    buffer.reserve(sizeof(Header) + sizeof(ClientData));
    buffer.insert(buffer.end(), headerBytes, headerBytes + sizeof(Header));
    buffer.insert(buffer.end(), dataBytes, dataBytes + sizeof(ClientData));
    _network.udpSend(buffer.data(), buffer.size(), _network.getServerEndpoint());
}

void Engine::updateRegistry(char *data)
{
    Header* headerDeserialized = reinterpret_cast<Header*>(data);

    if (headerDeserialized->_id == 3) {
        ServerData* dataDeserialized = reinterpret_cast<ServerData*>(data + sizeof(Header));
        GameData gameData[4];
        for (int i = 0; i < 4; i++) {
            gameData[i].entity = dataDeserialized->entities[i];
            gameData[i].posX = dataDeserialized->posX[i];
            gameData[i].posY = dataDeserialized->posY[i];
            memcpy(gameData[i].inputs, dataDeserialized->inputs[i], sizeof(uint16_t) * 10);
        }
        _game->updateRegistry(_reg, gameData);
    } else if (headerDeserialized->_id == 4) {
        DeleteEntities* dataDeserialized = reinterpret_cast<DeleteEntities*>(data + sizeof(Header));
        std::vector<entity> players = _game->getPlayers();
        auto it = find(players.begin(), players.end(), entity(dataDeserialized->_id));
        if (it != players.end()) {
            players.erase(it);
        }
        // _game->setPlayers(players);
        _reg.kill_entity(entity(dataDeserialized->_id));
    } else if (headerDeserialized->_id == 5) {
        exit(0);
    }

}

void Engine::runGame() 
{
    loadModules(_graphicPath, MODULE_TYPE::GRAPHIC);
    Events evt;
    std::vector<GAME_EVENT> gameEvents;
    while (1) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _clock);
        if (elapsedTime.count() >= 15) {
            _reg.run_systems();
            _clock = currentTime;
        }
        evt = _graphic->run_graphic(_reg);
        
        gameEvents = _game->run_gameLogic(_reg);
        if (std::find(evt.gameEvents.begin(), evt.gameEvents.end(), GAME_EVENT::WINDOW_CLOSE) != evt.gameEvents.end() || \
        std::find(gameEvents.begin(), gameEvents.end(), GAME_EVENT::WINDOW_CLOSE) != gameEvents.end()) {
            _graphic->closeWindow();
            return;
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

    clientData.entity = -1;
    for (int i = 0; i < 10; i++) {
        clientData.inputs[i] = 0;
    }

    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), false);
    sendData(clientData);
}

void Engine::runNetwork() 
{
    _network.UDPReceiveClient(std::bind(&Engine::updateRegistry, this, std::placeholders::_1), true);
    _network.getIOService().run();
}

void Engine::run()
{
    _game->initGame(_reg);
    connectToServer();

    std::thread gameThread(&Engine::runGame, this);
    std::thread networkThread(&Engine::runNetwork, this);

    gameThread.join();
    networkThread.join();
}