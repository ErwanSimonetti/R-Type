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
}

SFML::~SFML()
{
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


void SFML::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables) {
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


EntityEvent SFML::event_system(registry &reg) {
    std::vector<int> inputs;
    sf::Event event;
    EntityEvent entityEvent;
    entityEvent.entity = -1;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            entityEvent.events.emplace_back(GAME_EVENT::WINDOW_CLOSE);
            _window->close();
            break;
        }
        for (std::map<sf::Keyboard::Key, KEYBOARD>::iterator it = KeyboardMap.begin(); it != KeyboardMap.end(); it++) {
            if (sf::Keyboard::isKeyPressed(it->first)) {
                inputs.emplace_back(it->second);
            }
        }
    }
    return get_event(reg, inputs, reg.get_components<Position>(), reg.get_components<Controllable>(), reg.get_components<Velocity>(), reg.get_components<Shootable>());
}

EntityEvent SFML::get_event(registry &r, std::vector<int> &directions, sparse_array<Position> &positions, sparse_array<Controllable> &controllables, sparse_array<Velocity> &velocities, sparse_array<Shootable> &shootable)
{
    EntityEvent entityEvent;
    int current_direction = 0;

    entityEvent.entity = -1;
    entityEvent.xVelocity = 0;
    entityEvent.yVelocity = 0;
    for (size_t i = 0; i < velocities.size() && i < controllables.size() && i < positions.size() && i < shootable.size(); ++ i) {
        auto &vel = velocities[i];
        auto &pos = positions[i];
        auto &contr = controllables[i];
        auto &shoot = shootable[i];
        if (vel && contr && pos && shoot) {
            for(std::size_t j = 0; j < directions.size(); ++j) {
                entityEvent.entity = i;
                current_direction = directions[j];
                contr.value()._currentAction = current_direction;
                switch (current_direction) {
                    case KEYBOARD::ARROW_UP:
                        entityEvent.yVelocity = -1 * vel.value()._speedY;
                        break;
                    case KEYBOARD::ARROW_DOWN:
                        entityEvent.yVelocity = vel.value()._speedY;
                        break;
                    case KEYBOARD::ARROW_LEFT:
                        entityEvent.xVelocity = -1 * vel.value()._speedX;
                        break;
                    case KEYBOARD::ARROW_RIGHT:
                        entityEvent.xVelocity = vel.value()._speedX;
                        break;
                    case KEYBOARD::SPACE:
                        if (shoot.value()._canShoot == true) {
                            entityEvent.events.emplace_back(GAME_EVENT::SHOOT);
                            shoot.value()._clock.restart();
                        }
                        break;
                    default:
                        entityEvent.xVelocity = 0;
                        entityEvent.yVelocity = 0;
                        break;
                }
            }
            if (directions.empty()) {
                entityEvent.xVelocity = 0;
                entityEvent.yVelocity = 0;
            }
        }
    }
    return entityEvent;
}

EntityEvent SFML::run_graphic(registry &reg) {
    _window->display();
    _window->clear();
    return event_system(reg);
}