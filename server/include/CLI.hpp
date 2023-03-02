/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** CLI
*/

#pragma once

#ifndef CLI_HPP_
#define CLI_HPP_

#include <string>

namespace CLI {
    void launchSearchedFunction(std::string &line, registry &reg);
    void displayHelp();
};

#endif /* !CLI_HPP_ */