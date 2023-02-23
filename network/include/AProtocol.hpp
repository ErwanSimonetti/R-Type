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


        protected:
            std::unordered_map<int, std::function<void(char *, size_t)>> _idToType;

        private:
    };
}

#endif /* !APROTOCOL_HPP_ */
