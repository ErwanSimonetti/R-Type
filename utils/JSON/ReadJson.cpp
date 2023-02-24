/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ReadJson
*/

#include "ReadJson.hpp"

ReadJson::ReadJson(std::string fileName): _file(fileName)
{
    _file >> root;
}

ReadJson::~ReadJson()
{
}

std::string ReadJson::readValue(std::string value)
{
    Json::Reader reader;
    Json::Value completeJsonData;
    Json::FastWriter fastWriter;

    reader.parse(_file, completeJsonData);
    return fastWriter.write(completeJsonData[value]);
}

int ReadJson::getNumberOfElement(std::string array)
{
    Json::Value asset = root[array];
    int numElements = asset.size();

    return numElements;
}

std::string ReadJson::readValueFromArray(std::string array, uint16_t index, std::string value)
{
    
    Json::Value asset = root[array];
    if (!asset.empty()) {
        Json::Value element = asset[index];
        if (!element.empty()) {
            std::string type = element.get(value, "").asString();
            return type;
        }
    }
    return "none";
}

int ReadJson::IntValueFromArray(std::string array, uint16_t index, std::string value)
{
    Json::Value asset = root[array];
    if (!asset.empty()) {
        Json::Value element = asset[index];
        if (!element.empty()) {
            int type = element.get(value, "").asInt();
            return type;
        }
    }
    return 0;
}