/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

#include "RenderGame.hpp"
#include "components.hpp"
#include "entity.hpp"
#include "registry.hpp"

// void logging_system(registry &r) {
//     auto const &positions = r.get_components<position>() ;
//     auto const &velocities = r.get_components<velocity>() ;
//     for (size_t i = 0; i < positions.size() || i < velocities.size(); ++ i) {
//         auto const &pos = positions[i];
//         auto const &vel = velocities[i];
//         if (pos || vel)
//             std::cerr << i;
//         if (pos) {
//             std::cerr << ": Position = { " << pos.value()._x << ", " << pos.value()._y << " } ";
//         }
//         if (vel) {
//             std::cerr << ": Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }";
//         }
//         if (pos || vel)
//             std::cerr << std::endl;
//     }
// }

// void logging_system (sparse_array<position_t> const& positions,
//     sparse_array<velocity_t> const& velocities) {

//     for (size_t i = 0; i < positions.size() && i < velocities.size() ; ++i) {
//         auto const &pos = positions[i];
//         auto const &vel = velocities[i];

//         if (pos && vel) {
//             std :: cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y
//             << " } , Velocity = { " << vel.value()._vx << ", " << vel.value()._vy << " }" << std::endl;
//         }
//     }
// }

template <typename Component>
void print_system(registry &r) {
    auto const &component = r.get_components<Component>();
    for (size_t i = 0; i < component.size(); ++i) {
        if (component[i])
            std::cout << i << ": " << component[i].value();
    }
    std::cout << "\n";
}

// void position_system(registry &r) {
//     auto &positions = r.get_components<position>();
//     auto const &velocities = r.get_components<velocity>();
//     for (size_t i = 0; i < positions.size() && i < velocities.size(); ++ i) {
//         auto &pos = positions[i];
//         auto const &vel = velocities[i];
//         if (pos && vel) {
//             pos.value()._x += vel.value()._vx;
//             pos.value()._y += vel.value()._vy;
//         }
//     }
// }

// void control_system(registry &r) {
// }
    

int main(void)
{
    
    entity j(5);
    entity a(7);

    registry reg;
    // reg.register_component<char>();
    reg.register_component<position>();
    reg.register_component<velocity>();
    reg.register_component<drawable>();
    reg.register_component<controllable>();

    position pos;
    velocity vel;
    controllable control;

    reg.add_component<position>(j, std::move(pos));
    reg.add_component<velocity>(j, std::move(vel));
    reg.add_component<controllable>(j, std::move(control));
    reg.add_component<velocity>(a, std::move(vel));

    reg.emplace_component<position>(j, 1, 2);
    reg.emplace_component<velocity>(j, 0, 0);
    reg.emplace_component<velocity>(a, 44, 44);

    std::cout << reg.get_components<position>()[j].value()._x << " ";
    std::cout << reg.get_components<position>()[j].value()._y << "\n";
    std::cout << reg.get_components<velocity>()[a].value()._vy << "\n";

    entity test = reg.spawn_entity();
    reg.emplace_component<position>(entity(9), 3, 1);
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

    // logging_system(reg.get_components<position>(), reg.get_components<velocity>());

    entity entWin(0);
    drawable draw;
    reg.add_component<drawable>(j, std::move(draw));
    reg.emplace_component<drawable>(j, 50, sf::Color::Blue);

    RenderGame game(1920, 1080);
    game.gameLoop(reg);

    return 0;
}