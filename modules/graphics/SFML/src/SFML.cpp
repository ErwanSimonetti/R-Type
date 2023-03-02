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

    constructFromJson();
    set_sprite();
}

SFML::~SFML()
{
}

void SFML::createAsset(uint16_t type, std::string texture, uint16_t width, uint16_t height, uint16_t size)
{
    Asset newAsset;

    sf::IntRect newRect;
    newRect.left = 0;
    newRect.top = 0;
    newRect.width = width;
    newRect.height = height;

    newAsset._textureRect = width;
    newAsset._textureSize = size;
    newAsset._bounds = newRect;
    newAsset._texture = texture;

    _assets.insert(std::pair<uint16_t, Asset>(type, newAsset));
    
}

void SFML::constructFromJson()
{
    ReadJson reader("ressources/SFML/sfml.json");
    int nbAsset = reader.getNumberOfElement("asset");

    for (int i = 0; i < nbAsset; i++) {
        createAsset(reader.IntValueFromArray("asset", i, "type"), reader.readValueFromArray("asset", i, "texture"), \
        reader.IntValueFromArray("asset", i, "width"), reader.IntValueFromArray("asset", i, "height"), reader.IntValueFromArray("asset", i, "size"));
    }
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
            if (! _assets.count(draw.value()._type))
                continue;
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
            if (! _assets.count(draw.value()._type))
                continue;
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

    while(_window->pollEvent(event)) {
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