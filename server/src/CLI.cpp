/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CLI
*/

#include <iostream>
#include <map>
#include <functional>
#include <bits/stdc++.h>

#include "DeleteEntities.hpp"
#include "registry.hpp"
#include "MyNetwork.hpp"
#include "entity.hpp"
#include "CLI.hpp"

namespace CLI
{
    std::vector<std::string> commandsAvailable = {
        "help", "exit",
        "list_entities (optionnal) <size_t> [entity1] [entity2] ...",
        "spawn (optionnal) <size_t> [entity]", "kill <size_t> [entity]",
        "list_players",
        "kick <size_t> [player]"
    };

    void displayHelp()
    {
        std::cout << "- - - HELP MENU - - -" << std::endl << std::endl;
        std::cout << "commands :" << std::endl;
        for(std::size_t i = 0; i < commandsAvailable.size(); i += 1) {
            std::cout << "\t- " << commandsAvailable[i] << std::endl;
        }
        std::cout << std::endl;
    }

    void exitProgram()
    {
        exit(0);
    }

    void listEntities(registry &reg, const std::string &args)
    {
        std::vector<entity> entitiesToList;
        std::istringstream iss(args);
        std::string entityToListStr;

        if (args.empty())
            entitiesToList = reg.get_entities();
        else {
            while (std::getline(iss, entityToListStr, ' ')) {
                if (entityToListStr.empty()) {
                    entitiesToList = reg.get_entities();
                    break;
                }
                try
                {
                    entity entityToAdd(std::stoi(entityToListStr));
                    entitiesToList.emplace_back(entityToAdd);
                }
                catch(const std::invalid_argument &error)
                {
                    std::cerr << "couldn't convert '" << entityToListStr << "' to a number." << std::endl;
                    return;
                }
            }
        }
        for (int i = 0; i < entitiesToList.size(); i += 1) {
            std::cout << "- - - entity '" << entitiesToList.at(i) << "' - - -" << std::endl;
            std::cout << "alive : " << reg.is_entity_alive(i) << std::endl;
            if (i + 1 < entitiesToList.size())
                std::cout << std::endl;
        }
    }

    void spawnEntity(registry &reg, const std::string &args)
    {
        std::istringstream iss(args);
        std::string entityToSpawnStr;
        int idToSpawn = -1;
        
        std::getline(iss, entityToSpawnStr, ' ');
        if (entityToSpawnStr.empty()) {
            idToSpawn = reg.spawn_entity();
            if (reg.is_entity_alive(idToSpawn))
                std::cout << "spawned entity with id '" << idToSpawn << "'." << std::endl;
            else
                std::cerr << "failed to spawn entity '" << idToSpawn << "'." << std::endl;
            return;
        }
        try
        {
            idToSpawn = std::stoi(entityToSpawnStr);
        }
        catch(const std::invalid_argument &error)
        {
            std::cerr << "couldn't convert '" << entityToSpawnStr << "' to a number." << std::endl;
            return;
        }        
        if (idToSpawn <= 0) {
            std::cout << "entity id must be superior to 0." << std::endl;
            return;
        }
        if (reg.is_entity_alive(idToSpawn)) {
            std::cout << "entity '" << idToSpawn << "' already spawned and alive." << std::endl;
            return;
        }
        reg.spawn_entity_by_id(idToSpawn);
        if (reg.is_entity_alive(idToSpawn))
            std::cout << "entity '" << idToSpawn << "' spawned successfully." << std::endl;
        else
            std::cerr << "failed to spawn entity '" << idToSpawn << "'." << std::endl;
    }

    void killEntity(registry &reg, const std::string &args)
    {
        std::istringstream iss(args);
        std::string entityToKillStr;
        int idToKill = -1;

        if (args.empty()) {
            std::cout << "expecting an argument. Use `help`to get more details." << std::endl;
            return;
        }
        std::getline(iss, entityToKillStr, ' ');
        if (entityToKillStr.empty()) {
            std::cout << "empty arg." << std::endl;
            return;
        }
        try
        {
            idToKill = std::stoi(entityToKillStr);
        }
        catch(const std::exception& e)
        {
            std::cerr << "couldn't convert '" << entityToKillStr << "' to a number." << std::endl;
            return;
        }        
        if (idToKill < 0) {
            std::cout << "entity id must be superior to 0." << std::endl;
            return;
        }
        if (!reg.is_entity_alive(idToKill)) {
            std::cout << "entity '" << idToKill << "' already dead." << std::endl;
            return;
        }
        try
        {
            reg.kill_entity(entity(idToKill));
        }
        catch(const NoEntityFound &e)
        {
            std::cerr << "NoEntityFound exception on entity with id '" << idToKill << "'." << std::endl;
            return;
        }        
        if (!reg.is_entity_alive(idToKill))
            std::cout << "entity '" << idToKill << "' killed." << std::endl;
        else
            std::cerr << "failed to kill entity '" << idToKill << "'." << std::endl;
    }

    void listPlayers(MyNetwork &network, registry &reg, const std::string &args, std::function<std::vector<entity>()> func)
    {
        std::vector<EndpointInformation> endpoints = network.getEndpoints();

        for (size_t i = 0; i < endpoints.size(); i += 1) {
            std::cout << "- - - endpoint '" << i << "' - - -" << std::endl;
            std::cout << "accepted: " << endpoints.at(i)._isAccepted << std::endl;
            std::cout << "port: " << endpoints.at(i)._endpoint.port() << std::endl;
            std::cout << "IP address: " << endpoints.at(i)._endpoint.address() << std::endl;
            if (i + 1 < endpoints.size())
                std::cout << std::endl;
        }
    }

    void kickPlayer(MyNetwork &network, registry &reg, const std::string &args, std::function<std::vector<entity>()> func)
    {
        std::vector<EndpointInformation> endpoints = network.getEndpoints();
        std::istringstream iss(args);
        std::string playerIdToKillStr;
        int idToKick = -1;

        if (args.empty()) {
            std::cout << "expecting an argument. Use `help`to get more details." << std::endl;
            return;
        }
        std::getline(iss, playerIdToKillStr, ' ');
        if (playerIdToKillStr.empty()) {
            std::cout << "empty arg." << std::endl;
            return;
        }
        try
        {
            idToKick = std::stoi(playerIdToKillStr);
        }
        catch(const std::invalid_argument &error)
        {
            std::cerr << "couldn't convert '" << playerIdToKillStr << "' to a number." << std::endl;
            return;
        }
        if (idToKick < 0) {
            std::cerr << "player id must be superior to 0." << std::endl;
            return;
        }
        std::cout << "id to kick = " << idToKick << std::endl;
        std::cout << "endpoints size = " << endpoints.size() << std::endl;
        if (idToKick + 1 > endpoints.size()) {
            std::cerr << "no player to kick with '" << idToKick << "' id." << std::endl;
            return;
        }
        reg.kill_entity(entity(func()[idToKick]));
        sendDestroyEntityMessage(4, static_cast<size_t>(func()[idToKick]), network);
        sendHeaderExpulse(5, network, network.getEndpoints().at(idToKick)._endpoint);
        auto it =  network.getEndpoints().begin() + idToKick;
        network.getEndpoints().erase(it);
        std::vector<entity> players = func();
        auto ite = find(players.begin(), players.end(), entity(func()[idToKick]));
        if (ite != players.end())
            players.erase(ite);
        std::cout << "player '" << idToKick << "' has been kicked successfully." << std::endl;
    }

    typedef std::map<std::string, std::function<void()>> script_map;
    typedef std::map<std::string, std::function<void(registry &, std::string &)>> script_map_registry;
    typedef std::map<std::string, std::function<void(MyNetwork &, registry &reg, std::string &, std::function<std::vector<entity>()> func)>> script_map_network;    

    script_map functionsNoArgs = {
        {"help", displayHelp},
        {"exit", exitProgram},
    };

    script_map_registry functionsRegistry = {
        {"list_entities", listEntities},
        {"spawn", spawnEntity},
        {"kill", killEntity},
    };

    script_map_network functionsNetwork = {
        {"list_players", listPlayers},
        {"kick", kickPlayer},
    };

    void launchSearchedFunction(std::string &line, registry &reg, MyNetwork &network, std::function<std::vector<entity>()> func)
    {
        std::istringstream iss(line);
        std::string args;
        std::string command;
        
        std::getline(iss, command, ' ');
        if (command.size() < line.size())
            args = line.substr(command.size() + 1, line.size() - command.size());
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (functionsNoArgs.find(command) != functionsNoArgs.end())
            functionsNoArgs[command]();
        else if (functionsRegistry.find(command) != functionsRegistry.end())
            functionsRegistry[command](reg, args);
        else if (functionsNetwork.find(command) != functionsNetwork.end())
            functionsNetwork[command](network, reg, args, func);
        else
            std::cout << "command not recognized : '" << command << 
            "'. use `help` to see commands available." << std::endl;
    }

    void sendDestroyEntityMessage(const int &headerValue, const int &idEntity, MyNetwork &network)
    {
        std::vector<char> buffer;
        Header header{headerValue};
        const char* headerBytes = network.getProtocol().serialiseData<Header>(header);
        const char* dataBytes = network.getProtocol().serialiseData<DeleteEntities>(DeleteEntities{idEntity});

        buffer.reserve(sizeof(Header) + sizeof(DeleteEntities));
        buffer.insert(buffer.end(), headerBytes, headerBytes + sizeof(Header));
        buffer.insert(buffer.end(), dataBytes, dataBytes + sizeof(DeleteEntities));
        network.udpSendToAllClients(buffer.data(), buffer.size());
    }

    void sendHeaderExpulse(const int &headerValue, MyNetwork &network, boost::asio::ip::udp::endpoint endpoint)
    {
        std::vector<char> buffer;
        Header header{headerValue};
        const char* headerBytes = network.getProtocol().serialiseData<Header>(header);

        buffer.reserve(sizeof(Header) + sizeof(DeleteEntities));
        buffer.insert(buffer.end(), headerBytes, headerBytes + sizeof(Header));
        network.udpSend(buffer.data(), buffer.size(), endpoint);
    }
}