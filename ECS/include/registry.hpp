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
#include <memory>

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
        std::shared_ptr<Component> get_component_at(int position) {
            auto iter = _components_arrays.find(std::type_index(typeid(Component)));
            if (iter == _components_arrays.end()) {
                return nullptr;
            }

            auto& array = std::any_cast<sparse_array<Component>&>(iter->second);
            if (position < 0 || position >= array.size()) {
                return nullptr;
            }
            return &(array[position].value());
        }

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
         * @brief add component in an entity
         * 
         * @tparam Component type of components
         * @param to index in the ECS
         * @param c components struct move in ECS
         * @return sparse_array<Component>::reference_type 
         */
        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity const &to, Component &&c) {
            std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).insert_at(to, std::forward<Component>(c));
        };

        /**
         * @brief emplace a component in a entity
         * 
         * @tparam Component type of component 
         * @tparam Params give params for setting components
         * @param to entity for give id in ECS
         * @param p list of parameters given in set components
         * @return sparse_array<Component>::reference_type 
         */
        template <typename Component, typename... Params>
        void emplace_component(entity const &to, Params &&... p) {
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
            auto componentArray = std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second);
            if (from < componentArray.size()) {
                std::any_cast<sparse_array<Component>&>(_components_arrays.find(std::type_index(typeid(Component)))->second).erase(from);
            }
        }

        /**
         * @brief add a system in _system array with std::funtion, the function will be move in the vector.
         * 
         * @tparam List of components needed in the function.
         * @tparam Function type.
         * @param f the std::function to move in _systems array.
         */
        template <class ... Components, typename Function>
        void add_system(Function && f) {
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
                f(reg, reg.get_components<Components>()...);
            };
            _systems.push_back(system);
        };

        /**
         * @brief Add new entity in _entities array.
         * 
         * @return created entity
         */
        entity spawn_entity();

        /**
         * @brief create an entity with his id.
         * 
         * @param id of the entity.
         * @return entity created.
         */
        entity spawn_entity_by_id(size_t id);

        /**
         * @brief gets the vector of entities
         * 
         * @return entities used.
         */
        std::vector<entity> &get_entities();

        /**
         * @brief check if an entity id exist in the entity vector.
         * 
         * @param id of the entity.
         * @return return true if _it_ exist
         * @return return false if _it_ doesn't exist
         */
        bool is_entity_alive(size_t id);

        /**
         * @brief return the entity with this indexin the array.
         * 
         * @param idx, pos in the array.
         * @return entity at the position idx.
         */
        entity entity_from_index(std::size_t idx);

        /**
         * @brief delete all elements of an entity in each array.
         * 
         * @param e, entity to remove.
         */
        void kill_entity(entity const &e);

        /**
         * @brief running all systems in _systems array.
         * 
         */
        void run_systems();

    private:
        std::vector<entity> _entities;
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<std::function<void(registry &, entity const &)>> _function_stored;
        std::vector<std::function<void(registry&)>> _systems;
};