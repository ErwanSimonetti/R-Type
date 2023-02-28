/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Graphics.hpp>

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
        std::unordered_map<OBJECT, Asset> _assets;
};

extern "C" std::shared_ptr<IGraphic> createLibrary();

#endif /* !SFML_HPP_ */
