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

struct A {
    int a;
    char b;
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

        template <typename Data>
        char *serialiseData(Data data, DataTypes type);

        void handleData(char *buffer);
    protected:
    private:
};

#endif /* !PROTOCOL_HPP_ */
