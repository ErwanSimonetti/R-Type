/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CLI
*/

#include <iostream>
#include <map>
#include <functional>
#include "CLI.hpp"

namespace cli
{
    void displayHelp()
    {
        std::cout << "- - - HELP MENU - - -" << std::endl << std::endl;
        std::cout << "commands :" << std::endl;
        std::cout << "\t" << "help" << std::endl;
    }

    typedef std::map<std::string, std::function<void()>> script_map;

    script_map functionsToLaunch = {
        {"help", displayHelp}
    };

    void launchSearchedFunction(std::string functionSearched)
    {
        if (functionsToLaunch.find(functionSearched) != functionsToLaunch.end())
            functionsToLaunch[functionSearched]();
    }
}