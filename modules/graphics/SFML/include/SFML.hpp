/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "IGraphic.hpp"
#include "SFML_utils.hpp"


struct Asset {
    std::string _texture;
    sf::IntRect _bounds;
    uint16_t _textureSize;
    uint16_t _textureRect;
    sf::Sprite _sprite;
    std::shared_ptr<sf::Texture> _newtexture;
};

class SFML : public IGraphic {

    public:
        SFML();
        ~SFML();
        void animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables);
        void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables);
        Events event_system(registry &reg);
        void initialize_rect(Drawable &draw);
        Events run_graphic(registry &r);
        void set_sprite();

    protected:
    private:
        std::shared_ptr<sf::RenderWindow> _window;

        std::unordered_map<OBJECT, Asset> _assets = {
            { SHIP, { "ressources/SFML/ship.png", sf::IntRect(0, 0, 101, 41), 808, 101 }},
            { ENEMYSHIP, { "ressources/SFML/enemyship.png", sf::IntRect(0, 0, 101, 41), 808, 101 }},
            { BULLET, {"ressources/SFML/shoot.png", sf::IntRect(0, 0, 43, 41), 174, 43}},
            { PARA_1, {"ressources/SFML/para_1.png", sf::IntRect(0, 0, 1920, 1129), 1920, 1920}},
            { PARA_2, {"ressources/SFML/para_2.png", sf::IntRect(0, 0, 1920, 1059) , 1920, 1920}},
            { PARA_3, {"ressources/SFML/para_3.png", sf::IntRect(0, 0, 1920, 1280), 1920, 1920}},
            { PARA_4, {"ressources/SFML/para_4.png", sf::IntRect(0, 0, 1920, 734), 1920, 1920}},
        };
};

extern "C" std::shared_ptr<IGraphic> createLibrary();

#endif /* !SFML_HPP_ */
