/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** FollowPath
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "FollowPath.hpp"

void FollowPath::parse_follow_path_file(const std::string &fileFollowPath)
{
    std::string actualFile = "./client/src/enemy_paths/" + fileFollowPath + ".csv";
    std::ifstream is(actualFile);
    std::string line;
    std::stringstream lineStream;
    std::vector<int16_t> currentCheckpointCoords;
    std::string substring;

    if (!is.good())
        throw std::invalid_argument("File " + actualFile + " not found.");
    for (int i = 0; getline(is, line); i += 1) {
        if (i == 0)
            continue;
        lineStream << line;
        for (int j = 0; std::getline(lineStream, substring, ','); j += 1) {
            if (j == 0)
                continue;
            currentCheckpointCoords.push_back(std::stoi(substring));
        }
        _checkpoints.push_back(currentCheckpointCoords);
        lineStream.clear();
        currentCheckpointCoords.clear();
    }
}

void FollowPath::set_component(const std::string &fileFollowPath)
{
    _current_checkpoint = 0;
    parse_follow_path_file(fileFollowPath);
}