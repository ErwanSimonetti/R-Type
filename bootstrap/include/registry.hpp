/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** registry
*/

#pragma once

#include <cstddef>
#include <typeindex>
#include <any>
#include <functional>
#include <vector>
#include <unordered_map>

#include "entity.hpp"
#include "sparse_array.hpp"
#include "exception.hpp"

class registry
{
    public:
        template <class Component>
        sparse_array<Component> &register_component() {
            static sparse_array<Component> newElem;
            _components_arrays.emplace(std::type_index(typeid(Component)), newElem);
            auto lambda = []  (registry &regis, entity const &it) -> void {
                regis.remove_component<Component>(it);
            };
            _function_stored.push_back(lambda);
            return newElem;
        };

        template <class Component>
        sparse_array<Component> &get_components() {
            return std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
        };

        template <class Component>
        sparse_array<Component> const &get_components() const {
            return std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
        };


        entity spawn_entity() {
            size_t id_entity = 0;
            if (!_entities.empty())
                id_entity = _entities.at(_entities.size() - 1) + 1;
            entity new_entity(id_entity);
            _entities.emplace_back(new_entity);
            return new_entity;
        }

        //wtf does that mean ? ar we meant to store them ?
        entity entity_from_index(std::size_t idx) {
            if (idx > _entities.size() - 1)
                throw NoEntityFound();
            return (_entities.at(idx));
        }

        void kill_entity(entity const &e) {
            for(auto &element : _function_stored) {
                element(*this, e);
            };
        };

        // not sure about this one
        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity const &to, Component &&c) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).insert_at(to, std::forward<Component>(c));
        };

        template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&... p) {
            Component c;
            c.build_component(p...);
            get_components<Component>().insert_at(to, c);
        };

        template <typename Component>
        void remove_component(entity const &from) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).erase(from);
        }

        template <class ... Components, typename Function>
        void add_system (Function && f) {
            auto system = [f](registry& reg) {
                // f(std::forward<sparse_array<args>&>(get_components<args>())...);
                 f(reg.get_components<Components>()...);
            };
            _systems.push_back(system);
        }

        // template <class... Components, typename Function>
        // void add_system(Function &&f); // perfect forwarding in lambda capture , anyone ?
        // // or
        // template <class... Components , typename Function>
        // void add_system(Function const & f) {
        //     auto system = [f](registry& reg) {
        //     };

        //     _systems.push_back(system);
        // }; // taking it by reference 

        template <class... Components , typename Function>
        void add_system(Function const & f) {
            auto system = [f](registry& reg) {
                f(reg.get_components<Components>()...);
            };
            
            _systems.push_back(system);
        }; // taking it by reference .

        void run_systems() {
            for(auto &element : _systems) {
                element(*this);
            };
        };

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        // std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        std::vector<std::function<void(registry&)>> _systems;
        std::vector<entity> _entities;
};