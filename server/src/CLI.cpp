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
#include "entity.hpp"
#include "CLI.hpp"

namespace CLI
{
    std::vector<std::string> commandsAvailable = {
        "help", "exit", "kill"
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

    void killEntity(registry &reg)
    {
        entity test = reg.entity_from_index(0);
        std::cout << "entity 0 alive : " << reg.is_entity_alive(0) << std::endl;
        reg.kill_entity(test);
        std::cout << "entity 0 alive : " << reg.is_entity_alive(0) << std::endl;
    }

    typedef std::map<std::string, std::function<void()>> script_map;
    typedef std::map<std::string, std::function<void(registry &)>> script_map_registry;

    script_map functionsNoArgs = {
        {"help", displayHelp},
        {"exit", exitProgram},
    };

    script_map_registry functionsRegistry = {
        {"kill", killEntity},
    };

    void launchSearchedFunction(std::string &line, registry &reg)
    {
        std::istringstream iss(line);
        std::string args;
        std::string command;
        for (size_t i = 0; std::getline(iss, args, ' '); i += 1)
        {
            if (i == 0)
                command = args;
            else
                break;
        }
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (functionsNoArgs.find(command) != functionsNoArgs.end())
            functionsNoArgs[command]();
        else if (functionsRegistry.find(command) != functionsRegistry.end())
            functionsRegistry[command](reg);
        else
            std::cout << "command not recognized : '" << command << 
            "'. use `help` to see commands available." << std::endl;
        std::cout << "command = " << command << std::endl;
        std::cout << "args = " << args << std::endl;
    }
}