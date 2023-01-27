/*
** EPITECH PROJECT, 2023
** boostrap
** File description:
** main
*/

#include "RenderGame.hpp"
#include "./components/Components.hpp"
#include "entity.hpp"
#include "registry.hpp"
#include <functional>
// #include "ZipperIterator.hpp"

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
    reg.register_component<Position>();
    reg.register_component<Velocity>();
    reg.register_component<Drawable>();
    reg.register_component<Controllable>();

    Position pos;
    Velocity vel;
    Controllable control;

    reg.add_component<Position>(j, std::move(pos));
    reg.add_component<Velocity>(j, std::move(vel));
    reg.add_component<Controllable>(j, std::move(control));
    reg.add_component<Velocity>(a, std::move(vel));

    reg.emplace_component<Position>(j, 1, 2);
    reg.emplace_component<Velocity>(j, 0, 0);
    reg.emplace_component<Velocity>(a, 44, 44);

    // reg.add_system<position, velocity>(position_system);

    // logging_system(reg.get_components<position>(), reg.get_components<velocity>());

    RenderGame game(1920, 1080);

    entity entWin(0);
    Drawable draw;
    reg.add_component<Drawable>(j, std::move(draw));
    reg.emplace_component<Drawable>(j, 50, sf::Color::Blue);
    reg.add_system<Position, Velocity>(position_system);
    reg.add_system<Position, Velocity>(position_system);
    reg.add_system<Position, Drawable>(std::bind(&RenderGame::draw_system, &game, std::placeholders::_1, std::placeholders::_2));
    game.gameLoop(reg);

    return 0;
}