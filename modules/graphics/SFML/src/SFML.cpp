/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFML
*/

#include "SFML.hpp"

extern "C" std::shared_ptr<IGraphic> createLibrary()
{
    return std::make_shared<SFML>();
}

SFML::SFML()
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-TYPE");
    _window->setFramerateLimit(30);
    set_sprite();
    set_text();
}

SFML::~SFML()
{
}

void SFML::set_text()
{
    _font.loadFromFile("./ressources/SYNNova.otf");
}

void SFML::set_sprite() {
    for (auto &it: _assets) {
        it.second._newtexture = std::make_shared<sf::Texture>();
        if (!it.second._newtexture->loadFromFile(it.second._texture))
            std::cerr << "Failed to load texture" << std::endl;
        it.second._sprite.setTexture(*it.second._newtexture);
        it.second._sprite.setTextureRect(it.second._bounds);
    }
}

void SFML::initialize_rect(Drawable &draw){
    draw._rect = std::make_shared<spriteRect>(spriteRect{_assets.at(draw._type)._bounds.left, _assets.at(draw._type)._bounds.top, _assets.at(draw._type)._bounds.width, _assets.at(draw._type)._bounds.height});
}

void SFML::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<DrawableScore> &drawableScores) {
    for (size_t i = 0; i < drawables.size() && i < positions.size(); ++ i) {
        auto &draw = drawables[i];
        auto &pos = positions[i];
        if (draw && pos) {
            if (!draw.value()._rect)
                initialize_rect(draw.value());
            _assets.find(draw.value()._type)->second._sprite.setPosition(pos.value()._x, pos.value()._y);
            sf::IntRect newRect = {draw.value()._rect->left, draw.value()._rect->top, draw.value()._rect->width, draw.value()._rect->height};
            _assets.find(draw.value()._type)->second._sprite.setTextureRect(newRect);
            _window->draw(_assets.find(draw.value()._type)->second._sprite);
        }
    }
    for (size_t i = 0; i < drawableScores.size(); ++i) {
        auto &dbs = drawableScores[i];
        if (dbs) {
            sf::Text text("Score: " + std::to_string(*dbs.value()._score), _font, 48);
            text.setFillColor(sf::Color::White);
            text.setPosition(100, 30);
            _window->draw(text);
        }
    }
}

void SFML::animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables) 
{
    for (size_t i = 0; i < animatables.size() && i < drawables.size(); ++ i) {
        auto &anim = animatables[i];
        auto &draw = drawables[i];
        if (anim && draw) {
            if (!draw.value()._rect)
                initialize_rect(draw.value());
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - anim.value()._clock);
            if (elapsedTime.count() >= anim.value()._speed) {
                draw.value()._rect->left += _assets.find(draw.value()._type)->second._textureRect;
                anim.value()._clock = currentTime;
            }
            if ( draw.value()._rect->left >= _assets.find(draw.value()._type)->second._textureSize) {
                draw.value()._rect->left = 0;
            }
        }
    }
}


Events SFML::event_system(registry &reg) {
    std::vector<int> inputs;
    sf::Event event;
    Events events;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            events.gameEvents.emplace_back(GAME_EVENT::WINDOW_CLOSE);
            _window->close();
            break;
        }
        if (event.type ==  sf::Event::KeyReleased)
            events.inputs.emplace_back(KEYBOARD::NONE);
        for (std::map<sf::Keyboard::Key, KEYBOARD>::iterator it = KeyboardMap.begin(); it != KeyboardMap.end(); it++) {
            if (sf::Keyboard::isKeyPressed(it->first)) {
                events.inputs.emplace_back(it->second);
            }
        }
    }
    return events;
}

Events SFML::run_graphic(registry &reg) {
    _window->display();
    _window->clear();
    return event_system(reg);
}