/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IProtocol
*/

#ifndef IPROTOCOL_HPP_
#define IPROTOCOL_HPP_

#include <iostream>
#include <sstream>
#include <cstring>

namespace Protocol
{
    class IProtocol {
        public:
            virtual ~IProtocol() = default;

            virtual void read(char *buffer) = 0;

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

#endif /* !IPROTOCOL_HPP_ */
