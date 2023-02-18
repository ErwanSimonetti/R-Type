/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IGraphic.hpp"

struct Asset {
    std::string _texture;
    sf::IntRect _bounds;
    uint16_t _textureSize;
    uint16_t _textureRect;
    sf::Sprite _sprite;
};

class SFML : public IGraphic {

    public:
        SFML();
        ~SFML();
        EntityEvent get_event(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities, sparse_array<Shootable> &shootable);
        void animation_system(registry &r, sparse_array<Animatable> &animatable, sparse_array<Drawable> &drawable);
        void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables);
        EntityEvent event_system(registry &reg);
        void initialize_rect(Drawable &draw);
        EntityEvent run_graphic(registry &r);
        void set_sprite();
        void hello();

    protected:
    private:
        sf::RenderWindow *_window;

        std::unordered_map<OBJECT, Asset> _assets = {
            {SHIP, { "ressources/ship.png", sf::IntRect(0, 0, 101, 41), 808, 101 }},
            {ENEMYSHIP, { "ressources/enemyship.png", sf::IntRect(0, 0, 101, 41), 808, 101 }},
            { PARA_1, {"ressources/para_1.png", sf::IntRect(0, 0, 1920, 1129), 1920, 1920}},
            { PARA_2, {"ressources/para_2.png", sf::IntRect(0, 0, 1920, 1059) , 1920, 1920}},
            { PARA_3, {"ressources/para_3.png", sf::IntRect(0, 0, 1920, 1280), 1920, 1920}},
            { PARA_4, {"ressources/para_4.png", sf::IntRect(0, 0, 1920, 1129), 1920, 1920}},
        };
};

std::unordered_map<OBJECT, std::string> textureMap = {
    { SHIP, "ressources/ship.png" },
    { ENEMYSHIP, "ressources/enemyship.png" },
    { BULLET, "ressources/shoot.png" },
    { PARA_1, "ressources/para_1.png" },
    { PARA_2, "ressources/para_2.png" },
    { PARA_3, "ressources/para_3.png" },
    { PARA_4, "ressources/para_4.png" }
};

std::unordered_map<OBJECT, sf::IntRect> boundsMap = {
    { SHIP, sf::IntRect(0, 0, 101, 41) },
    { ENEMYSHIP, sf::IntRect(0, 0, 101, 41) },
    { BULLET, sf::IntRect(0, 0, 43, 41) },
    { PARA_1, sf::IntRect(0, 0, 1920, 1129) },
    { PARA_2, sf::IntRect(0, 0, 1920, 1059) },
    { PARA_3, sf::IntRect(0, 0, 1920, 1280) },
    { PARA_4, sf::IntRect(0, 0, 1920, 734)  }
};

std::unordered_map<OBJECT, uint16_t> textureSize = {
    { SHIP,  808},
    { ENEMYSHIP,  808},
    { BULLET, 174 },
    { PARA_1, 1920 },
    { PARA_2, 1920 },
    { PARA_3, 1920 },
    { PARA_4, 1920 }
};

std::unordered_map<OBJECT, uint16_t> textureRect = {
    { SHIP,  101},
    { ENEMYSHIP,  101},
    { BULLET, 43 },
    { PARA_1, 1920 },
    { PARA_2, 1920 },
    { PARA_3, 1920 },
    { PARA_4, 1920 }

extern "C" std::shared_ptr<IGraphic> createLibrary();

#endif /* !SFML_HPP_ */
