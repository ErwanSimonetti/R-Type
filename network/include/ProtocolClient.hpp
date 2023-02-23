/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProtocolClient
*/

#ifndef PROTOCOLCLIENT_HPP_
#define PROTOCOLCLIENT_HPP_

#include <unordered_map>
#include <functional>
#include <cstddef>

#include "Header.hpp"
#include "AProtocol.hpp"

namespace Protocol
{
    class ProtocolClient : public IProtocol {
        public:
            ProtocolClient()
            {

            };

            ~ProtocolClient() = default;

            void read(char *buffer)
            {
                std::cout << "Receive buffer of size == " << strlen(buffer) << std::endl;
                Header* ptr1 = reinterpret_cast<Header*>(buffer);
                std::cout << "Header ==  [" << ptr1->_id << "]" << std::endl;

                std::cout << "Size of the map == " << _idToType.size() << std::endl;
                if (_idToType.count(ptr1->_id)) {
                    _idToType[ptr1->_id](buffer, sizeof(Header));
                } else {
                    std::cout << "Error: Invalid header id : "  << ptr1->_id << " not found." << std::endl;
                }
            };


        protected:
        private:
            std::unordered_map<int, std::function<void(char *, size_t)>> _idToType;
    };
}

#endif /* !PROTOCOLCLIENT_HPP_ */
