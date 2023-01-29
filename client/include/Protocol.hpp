/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#include <iostream>
#include <cstring>

struct Header {
    uint16_t dataType;
    uint16_t dataSize;
};

struct Astructlol {
    int a;
    char b;
};

template <class Data>
struct Result {
    DataTypes type;
    Data data;
};

enum DataTypes {
    typeA = 1,
    typeB = 2,
    typeC = 3,
    typeD = 4
};

class Protocol {
    public:
        Protocol();
        ~Protocol();

        template <class Data>
        char *serialiseData(Data data, DataTypes type) {
            char *buffer = new char[sizeof(Data)];
            Header header;

            header.dataType = type;
            header.dataSize = sizeof(Data);

            std::memcpy(buffer, &header, sizeof(Header));
            std::memcpy(buffer, &data, sizeof(Data));

            return buffer;
        };

        template <typename Data>
        Result<Data> handleData(char *buffer) {
            Header header;
            std::memcpy(&header, buffer, sizeof(Header));

            switch (header.dataType) {
            case typeA:
                A a;
                std::memcpy(&a, buffer, sizeof(A));
                Result res{typeA, a};
                return res;
            default:
                break;
            }
        };

    protected:
    private:
};

#endif /* !PROTOCOL_HPP_ */
