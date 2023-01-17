/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** bootstrap
*/

#ifndef BOOTSTRAP_H_
#define BOOTSTRAP_H_

#include <utility>
#include <cstddef>
#include <type_traits>
#include <typeindex>
#include <iostream>
#include <vector>
#include <map>
#include <any>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <optional>
#include <SFML/Graphics.hpp>



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

struct A {
    A() : x(5) {}
    ~A() {}

    private:int x;
};

// class A {
    
//     template <typename Component>
//     friend class sparse_array;

//     private:
//         A(const int &i){ x = i + 1;};
//         A() = default;
//         // build_component()
//         public:
//         int x;
// };





struct NamedType
{
    explicit NamedType(size_t id) : id_(id) {}
    operator size_t() const { return id_; }
    size_t id_;
};

#endif /* !BOOTSTRAP_H_ */
