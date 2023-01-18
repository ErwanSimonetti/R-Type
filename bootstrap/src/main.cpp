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

    reg.add_system<sparse_array<position>, sparse_array<velocity>>(position_system);

    // logging_system(reg.get_components<position>(), reg.get_components<velocity>());

    // entity entWin(0);
    // drawable draw;
    // reg.add_component<drawable>(j, std::move(draw));
    // reg.emplace_component<drawable>(j, 50, sf::Color::Blue);

    // RenderGame game(1920, 1080);
    // game.gameLoop(reg);

    return 0;
}