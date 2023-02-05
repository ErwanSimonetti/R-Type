/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** entity
*/

#pragma once

#include <cstddef>
#include <type_traits>

class entity {
    friend class registry;
    public:
        explicit entity(size_t id) : _id(id) {}
        template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, size_t>>>
        explicit entity(T t) : _id(static_cast<size_t>(t)) {}
        operator size_t() const { return _id; }
    
    private:
        size_t _id;
};
