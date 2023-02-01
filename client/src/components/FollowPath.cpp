/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FollowPath
*/

#include <iostream>
#include "FollowPath.hpp"

void FollowPath::parse_follow_path_file(const std::string &fileFollowPath)
{
    std::cout << "file follow path = " << fileFollowPath << std::endl;
}

void FollowPath::build_component(const std::string &fileFollowPath)
{
    _current_checkpoint = 0;
    parse_follow_path_file(fileFollowPath);
}