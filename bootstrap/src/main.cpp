/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

#include "components.hpp"
#include "entity.hpp"
#include "registry.hpp"

void logging_system(registry &r) {
    auto const &positions = r.get_components<position>() ;
    auto const &velocities = r.get_components<velocity>() ;
    for (size_t i = 0; i < positions.size() || i < velocities.size(); ++ i) {
        auto const &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos || vel)
            std::cerr << i;
        if (pos) {
            std::cerr << ": Position = { " << pos.value()._x << ", " << pos.value()._y << " } ";
        }
        if (vel) {
            std::cerr << ": Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }";
        }
        if (pos || vel)
            std::cerr << std::endl;
    }
}

void logging_system (sparse_array<position_t> const& positions,
    sparse_array<velocity_t> const& velocities) {

    for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
        auto const &pos = positions [i];
        auto const &vel = velocities [i];

        if ( pos && vel ) {
            std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
            << " } , Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }" << std::endl;
        }
    }
}

void position_system(registry &r) {
    auto &positions = r.get_components<position>();
    auto const &velocities = r.get_components<velocity>();
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
        auto &pos = positions[i];
        auto const &vel = velocities[i];
        if (pos && vel) {
            pos.value()._x += vel.value()._vx;
            pos.value()._y += vel.value()._vy;
        }
    }
}

void control_system(registry &r) {
}
    

int main(void)
{
    
    entity j(5);
    entity a(7);
    // Entity n(NamedType(8));
    // Entity e(NamedType(5));
    // Entity g(NamedType(5));

    // sparse_array<char> a;
    // a.insert_at(0, 'a');

    registry reg;
    // reg.register_component<char>();
    reg.register_component<position_t>();
    reg.register_component<velocity_t>();
    reg.register_component<drawable_t>();
    // reg.register_component<position_t>();
    // reg.register_component<int>();
    // reg.get_components<char>().insert_at(0, 'J');
    // reg.get_components<char>().insert_at(1, 'a');
    // reg.get_components<int>().insert_at(1, 1);
    // reg.get_components<int>().insert_at(0, 2);

    // std::cout << "function stored size = " << reg._function_stored.size() << '\n';
    // printf("chars: \n");
    // std::cout << reg.get_components<char>();
    // printf("___________________\nint: \n");
    // std::cout << reg.get_components<int>();

    // reg.remove_component<char>(reg.get_components<char>()[0]);
    // reg.unregister_component<char>(reg, entity(1));
    // reg.(entity(1));
    // printf("__________________\nchars: \n");
    // reg.kill_entity(entity(0));
    position pos;
    velocity_t vel;
    reg.add_component<position_t>(j, std::move(pos));
    reg.add_component<velocity_t>(j, std::move(vel));
    // reg.add_component<position_t>(a, std::move(pos));
    reg.add_component<velocity_t>(a, std::move(vel));
    // std::cout << reg.get_components<position_t>();
    // std::cout << std::any_cast<sparse_array<position_t>&>(reg.get_components<position_t>())[5]._x << "\n";
    reg.emplace_component<position_t>(j, 1, 2);
    // reg.emplace_component<position_t>(a, 34, 2);
    reg.emplace_component<velocity_t>(j, 7, 16);
    reg.emplace_component<velocity_t>(a, 44, 44);

    std::cout << reg.get_components<position_t>()[j].value()._x << " ";
    std::cout << reg.get_components<position_t>()[j].value()._y << "\n";
    std::cout << reg.get_components<velocity_t>()[a].value()._vy << "\n";
    // std::cout << reg.get_components<velocity_t>()[j].value()._speed << "\n";

    entity test = reg.spawn_entity();
    std::cout << "entity test =" << test << std::endl;
    entity test2 = reg.spawn_entity();
    std::cout << "entity test2 =" << test2 << std::endl;
    entity test3 = reg.spawn_entity();
    std::cout << "entity test3 =" << test3 << std::endl;
    std::cout << "entity at index 0 = " << reg.entity_from_index(0) << std::endl;
    std::cout << "entity at index 1 = " << reg.entity_from_index(1) << std::endl;
    std::cout << "entity at index 2 = " << reg.entity_from_index(2) << std::endl;
    try
    {
        entity test4 = reg.entity_from_index(3);
    }
    catch(const std::exception& e)
    {
        std::cout << "error caught" << std::endl;
        entity test4 = reg.spawn_entity(); // maybe we want to spawn an entity to avoid crashing the whole program when we can't find a specific one
    }
    std::cout << "entity at index 3 = " << reg.entity_from_index(3) << std::endl;
    logging_system(reg);
    position_system(reg);
    logging_system(reg);

    // std::cout << reg.get_components<velocity_t>() << std::endl;
    logging_system(reg.get_components<position_t>(), reg.get_components<velocity_t>());

    // printf("chars: \n"); 
    // std::cout << reg.get_components<A>();
    // printf("___________________\nint: \n");
    // std::cout << reg.get_components<int>();

    // reg.remove_component()
    // req.register_component<>()

    // printf("____________\n");
    // reg.insert_at(0, 'b');
    // printf("____________\n");
    // a.insert_at(1, 'c');
    // printf("____________lol\n");
    // a.insert_at(10, 'z');
    // printf("____________lol\n");
    // a.erase(1);
    // // std::cout << '|' << a._data[1] << "|\n";

    // // a.insert_at(9, 'Y');
    // std::cout << a.get_index('z') << '\n';
    // // a.insert_at(10, 'Z');
    // printf("trop marrant\n");
    // sparse_array<char> ok;
    // ok = a;
    // std::cout << a[1] << std::endl;
    // std::cout << ok[1] << std::endl;
}