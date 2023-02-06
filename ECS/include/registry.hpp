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

/**
 * 
 * @class registry
 * @brief A class to manage the ECS
 * 
 */
class registry
{
    public:

        /**
         * @brief this function is used to add a new component in _component_arrays.
         * 
         * @tparam Component type to register.
         * @return sparse_array<Component>& the register type array.
         */
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

        /**
         * @brief Get the components object with a type given in template
         * 
         * @tparam Component given
         * @return sparse_array<Component>& get reference on the table
         */
        template <class Component>
        sparse_array<Component> &get_components() {
            return std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
        };

        /**
         * @brief Get the components object with a type given in template
         * 
         * @tparam Component given
         * @return sparse_array<Component> const& get const reference on the array
         */
        template <class Component>
        sparse_array<Component> const &get_components() const {
            return std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
        };

        /**
         * @brief Add new entity in _entities array.
         * 
         * @return entity create.
         */
        entity spawn_entity() {
            size_t id_entity = 0;
            if (!_entities.empty())
                id_entity = _entities.at(_entities.size() - 1) + 1;
            entity new_entity(id_entity);
            _entities.emplace_back(new_entity);
            return new_entity;
        }

        entity spawn_entity_by_id(size_t id) {
            size_t id_entity = id;
            entity new_entity(id_entity);
            _entities.emplace_back(new_entity);
            return new_entity;
        }

        bool is_entity_alive(size_t id) {
            std::cout << id << "\n";
            auto it = std::find(_entities.begin(), _entities.end(), id);
            // std::cout << static_cast<size_t>(*it) << "\n";
            if (it == _entities.end()) {
                printf("jaj\n");
                return false;
            }
            return true;
        }

        /**
         * @brief return the entity with this indexin the array.
         * 
         * @param idx, pos in the array.
         * @return entity at the position idx.
         */
        entity entity_from_index(std::size_t idx) {
            if (idx > _entities.size() - 1)
                throw NoEntityFound();
            return (_entities.at(idx));
        }

        /**
         * @brief delete all elements of an entity in each array.
         * 
         * @param e, entity to remove.
         */
        void kill_entity(entity const &e) {
            for(auto &element : _function_stored) {
                element(*this, e);
            }
            auto it = std::find(_entities.begin(), _entities.end(), e._id);
            _entities.erase(it); 
        };

        /**
         * @brief 
         * 
         * @tparam Component 
         * @param to 
         * @param c 
         * @return sparse_array<Component>::reference_type 
         */
        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity const &to, Component &&c) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).insert_at(to, std::forward<Component>(c));
        };

        /**
         * @brief 
         * 
         * @tparam Component 
         * @tparam Params 
         * @param to 
         * @param p 
         * @return sparse_array<Component>::reference_type 
         */
        template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity const &to, Params &&... p) {
            Component c;
            c.set_component(p...);
            get_components<Component>().insert_at(to, c);
        };

        /**
         * @brief remove component in sparse array with the type of the component.
         * 
         * @tparam Component type will be delete;
         * @param from the index of the node will be delete in sparse array.
         */
        template <typename Component>
        void remove_component(entity const &from) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).erase(from);
        }

        /**
         * @brief add a system in _system array with std::funtion, the function will be move in the vector.
         * 
         * @tparam List of components needed in the function.
         * @tparam Function type.
         * @param f the std::function to move in _systems array.
         */
        template <class ... Components, typename Function>
        void add_system (Function && f) {
            auto system = [f](registry& reg) {
                 f(reg.get_components<Components>()...);
            };
            _systems.push_back(system);
        }

        /**
         * @brief add a system in _system array with a reference on a std::funtion.
         * 
         * @tparam List of components needed in the function.
         * @tparam Function type.
         * @param f the std::function to add in _systems array.
         */
        template <class... Components , typename Function>
        void add_system(Function const & f) {
            auto system = [f](registry& reg) {
                f(reg.get_components<Components>()...);
            };
            
            _systems.push_back(system);
        };

        /**
         * @brief running all systems in _systems array.
         * 
         */
        void run_systems() {
            for(auto &element : _systems) {
                element(*this);
            };
        };

        std::vector<entity> _entities;
    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        // std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        std::vector<std::function<void(registry&)>> _systems;
};