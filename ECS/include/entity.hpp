/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** entity
*/

#pragma once

#include <cstddef>
#include <type_traits>

/**
 * @brief permits to manage index in ECS
 * 
 */
class entity {
    friend class registry;
    public:

        /**
         * @brief Construct a new entity object with an id
         * 
         * @param id the number to set like id
         */
        explicit entity(size_t id) : _id(id) {}
    
        /**
         * @brief Ensure the convertability from type entity to size t
         * 
         */    
        template <typename T, typename = std::enable_if_t<std::is_convertible_v<T, size_t>>>
        explicit entity(T t) : _id(static_cast<size_t>(t)) {}

        /**
         * @brief Ensure the convertability from type entity to size t
         * 
         */
        operator size_t() const { return _id; }
    
    private:
        size_t _id;
};
