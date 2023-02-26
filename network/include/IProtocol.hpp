/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IProtocol
*/

#pragma once

#include <iostream>
#include <sstream>
#include <cstring>

// #include "MyNetwork.hpp"

namespace Protocol
{
    class IProtocol {
        public:
            virtual ~IProtocol() = default;

            virtual void read(char *buffer) = 0;
            virtual char *askConnection(char *buffer, int id) = 0;

        protected:
        private:
    };

    template <class Data>
    char *serialiseData(Data data)
    {
        char *buffer = new char[sizeof(Data)];

        std::memcpy(buffer, &data, sizeof(Data));

        return buffer;
    };
}
