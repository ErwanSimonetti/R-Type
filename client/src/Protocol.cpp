/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Protocol
*/

#include "Protocol.hpp"

Protocol::Protocol()
{
}

Protocol::~Protocol()
{
}

// template <class Data>
// char *Protocol::serialiseData(Data data, DataTypes type)
// {
//     char *buffer[sizeof(Data)];
//     Header header;

//     header.dataType = type;
//     header.dataSize = sizeof(Data);

//     std::memcpy(buffer, &header, sizeof(Header));
//     std::memcpy(buffer, &data, sizeof(Data));
    
//     return buffer;
// }

// void Protocol::handleData(char *buffer) {

//     Header header;
//     std::memcpy(&header, buffer, sizeof(Header));

//     switch (header.dataType) {
//     case typeA:
//         // A a;
//         // std::memcpy(&a, buffer, sizeof(A));
//         break;
//     default:
//         break;
//     }
// }