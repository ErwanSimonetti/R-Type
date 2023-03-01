/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** registry
*/

#include "registry.hpp"

entity findSmallestUnusedValue(const std::vector<entity>& v) {
    std::vector<entity> sorted_v = v;
    std::sort(sorted_v.begin(), sorted_v.end());

    size_t smallest_unused_value = 1;
    for (int i = 0; i < sorted_v.size(); i++) {
        if (sorted_v[i] > smallest_unused_value) {
            break;
        } else if (sorted_v[i] == smallest_unused_value) {
            smallest_unused_value++;
        }
    }

    return entity(smallest_unused_value);
}

entity registry::spawn_entity() 
{
    size_t id_entity = 0;
    if (!_entities.empty())
        id_entity = findSmallestUnusedValue(_entities);
    entity new_entity(id_entity);
    _entities.emplace_back(new_entity);
    std::cout << "spawn entity nb == " << new_entity << std::endl;
    std::cout << "get nb entities == " << _entities.size() << std::endl;
    return new_entity;
}

entity registry::spawn_entity_by_id(size_t id) 
{
    size_t id_entity = id;
    entity new_entity(id_entity);
    _entities.emplace_back(new_entity);
    return new_entity;
}

std::vector<entity> &registry::get_entities()
{
    return _entities;
}

bool registry::is_entity_alive(size_t id) 
{
    auto it = std::find(_entities.begin(), _entities.end(), id);
    if (it == _entities.end()) {
        return false;
    }
    return true;
}

entity registry::entity_from_index(std::size_t idx) {
    if (idx > _entities.size() - 1)
        throw NoEntityFound();
    return (_entities.at(idx));
}

void registry::kill_entity(entity const &e) {
    for(auto &element : _function_stored) {
        element(*this, e);
    }
    auto it = std::find(_entities.begin(), _entities.end(), e._id);
    _entities.erase(it); 
};

void registry::run_systems() {
    for(auto &element : _systems) {
        element(*this);
    };
};