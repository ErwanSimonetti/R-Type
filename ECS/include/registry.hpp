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

        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity const &to, Component &&c) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).insert_at(to, std::forward<Component>(c));
        };

        template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&... p) {
            Component c;
            c.set_component(p...);
            get_components<Component>().insert_at(to, c);
        };

        template <typename Component>
        void remove_component(entity const &from) {
            auto componentArray = std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
            if (from < componentArray.size()) {
                std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).erase(from);
            }
        }

        template <class ... Components, typename Function>
        void add_system(Function && f) {
            auto system = [f](registry& reg) {
                 f(reg.get_components<Components>()...);
            };
            _systems.push_back(system);
        }

        template <class... Components , typename Function>
        void add_system(Function const & f) {
            auto system = [f](registry& reg) {
                f(reg, reg.get_components<Components>()...);
            };
            _systems.push_back(system);
        };

        entity spawn_entity();
        entity spawn_entity_by_id(size_t id);
        std::vector<entity> &get_entities();
        bool is_entity_alive(size_t id);
        entity entity_from_index(std::size_t idx);
        void kill_entity(entity const &e);
        void run_systems();

    private:
        std::vector<entity> _entities;
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        std::vector<std::function<void(registry&)>> _systems;
};