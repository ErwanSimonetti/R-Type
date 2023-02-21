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
    class ProtocolClient : public AProtocol {
        public:
            ProtocolClient() : AProtocol()
            {

            };

            ~ProtocolClient() = default;

        protected:
        private:
            std::unordered_map<int, std::function<void(char *, size_t)>> _idToType;
    };
}

#endif /* !PROTOCOLCLIENT_HPP_ */
