/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "Engine.hpp"

Engine::Engine(boost::asio::io_service &io_service, const std::string &host, const std::string &port, const std::string &graphicModulePath, const std::string &gameModulePath) : _reg(), _network(io_service, host, port)
{
    loadModules(gameModulePath, MODULE_TYPE::GAME);
    _graphicPath = graphicModulePath;
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
    _reg.register_component<Stats>();
    _reg.register_component<DrawableText>();
    _reg.register_component<Particulable>();
    _reg.register_component<SoundEffect>();

    _reg.add_system<Position, Hitbox>(collision_system);
    _reg.add_system<Position, Velocity, Controllable>(position_system);
    _reg.add_system<Shootable>(shoot_system);
    _reg.add_system<Animatable, Position, Parallax>(parallax_system);
    // _reg.add_system<Position, Velocity, FollowPath>(followPathSystem);
    _reg.add_system<Stats, Position, Pet>(entity_killing_system);
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
            _reg.add_system<Animatable, Drawable>(std::bind(&IGraphic::animation_system, _graphic, std::placeholders::_1, std::placeholders::_2));
            _reg.add_system<Position, Drawable, Particulable, DrawableText>(std::bind(&IGraphic::draw_system, _graphic, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)); 
            _reg.add_system<SoundEffect>(std::bind(&IGraphic::sound_system, _graphic, std::placeholders::_1));
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
    GameData gameData[4];
    Header* headerDeserialized = reinterpret_cast<Header*>(data);
    std::cout << "Header received == " << headerDeserialized->_id << std::endl;

    if (headerDeserialized->_id == 3) {
        ServerData* dataDeserialized = reinterpret_cast<ServerData*>(data + sizeof(Header));
        for (int i = 0; i < 4; i++) {
            gameData[i].entity = dataDeserialized->entities[i];
            gameData[i].posX = dataDeserialized->posX[i];
            gameData[i].posY = dataDeserialized->posY[i];
            memcpy(gameData[i].inputs, dataDeserialized->inputs[i], sizeof(uint16_t) * 10);
        }
    }

    _game->updateRegistry(_reg, gameData);
}

void Engine::runGame() 
{
    loadModules(_graphicPath, MODULE_TYPE::GRAPHIC);
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