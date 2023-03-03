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
#include "registry.hpp"
#include "MyNetwork.hpp"
#include "entity.hpp"
#include "CLI.hpp"

namespace CLI
{
    std::vector<std::string> commandsAvailable = {
        "help", "exit", "list_entities (optionnal) <size_t> [entity1] [entity2] ...", "spawn (optionnal) <size_t> [entity]", "kill <size_t> [entity]"
    };

    void displayHelp()
    {
        std::cout << "- - - HELP MENU - - -" << std::endl << std::endl;
        std::cout << "commands :" << std::endl;
        for(std::size_t i = 0; i < commandsAvailable.size(); i += 1) {
            std::cout << "\t" << commandsAvailable[i] << std::endl;
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
                entity entityToAdd(std::stoi(entityToListStr));
                entitiesToList.emplace_back(entityToAdd);
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
        idToSpawn = std::stoi(entityToSpawnStr);
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
        idToKill = std::stoi(entityToKillStr);
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

    typedef std::map<std::string, std::function<void()>> script_map;
    typedef std::map<std::string, std::function<void(registry &, std::string &)>> script_map_registry;

    script_map functionsNoArgs = {
        {"help", displayHelp},
        {"exit", exitProgram},
    };

    script_map_registry functionsRegistry = {
        {"list_entities", listEntities},
        {"spawn", spawnEntity},
        {"kill", killEntity},
    };

    void launchSearchedFunction(std::string &line, registry &reg, MyNetwork &network)
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
        else if (functionsRegistry.find(command) != functionsRegistry.end()) {
            functionsRegistry[command](reg, args);
        }
        else
            std::cout << "command not recognized : '" << command << 
            "'. use `help` to see commands available." << std::endl;
    }
}