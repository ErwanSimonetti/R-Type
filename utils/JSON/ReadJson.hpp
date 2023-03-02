/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ReadJson
*/


#ifndef READJSON_HPP_
#define READJSON_HPP_

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

class ReadJson {
    public:
        ReadJson(std::string fileName);
        ~ReadJson();
        std::string readValue(std::string value);
        std::string readValueFromArray(std::string array, uint16_t index, std::string value);
        int getNumberOfElement(std::string array);
        int IntValueFromArray(std::string array, uint16_t index, std::string value);

    protected:
    private:
        std::ifstream _file;
        Json::Value root;
};

#endif /* !READJSON_HPP_ */
