/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AProtocol
*/

#ifndef APROTOCOL_HPP_
#define APROTOCOL_HPP_

#include <unordered_map>
#include <functional>
#include <cstddef>

#include "Header.hpp"
#include "AProtocol.hpp"
#include "IProtocol.hpp"

namespace Protocol
{
    class AProtocol : public IProtocol {
        public:
            AProtocol() = default;
            ~AProtocol() = default;

            void read(char *buffer)
            {
                Header* ptr1 = reinterpret_cast<Header*>(buffer);
                std::cout << "Header == " << ptr1->_id << std::endl;

                if (_idToType.count(ptr1->_id)) {
                    _idToType[ptr1->_id](buffer, sizeof(Header));
                } else {
                    std::cout << "Error: Invalid header id : "  << ptr1->_id << " not found." << std::endl;
                }
            };

        protected:
            std::unordered_map<int, std::function<void(char *, size_t)>> _idToType;

        private:
    };
}

#endif /* !APROTOCOL_HPP_ */
