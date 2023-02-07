/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

#pragma once

enum OBJECT {
    SHIP,
    BULLET
};


struct Drawable {

std::unordered_map<OBJECT, std::string> textureMap = {
    { SHIP, "ressources/ship.png" },
    { BULLET, "ressources/bullet.png" }
};

std::unordered_map<OBJECT, sf::IntRect> boundsMap = {
    { SHIP, sf::IntRect(0, 0, 33, 18) },
    { BULLET, sf::IntRect(10, 10, 50, 30) }
};
    Drawable() = default;
    void set_component(const OBJECT &obj) {
        printf("%s\n", textureMap[obj].c_str());
        _texture = std::make_shared<sf::Texture>();
        if (!_texture->loadFromFile(textureMap[obj].c_str())) {
        std::cerr << "Failed to load texture " << textureMap[obj].c_str() << std::endl;
        }
        _sprite.setTexture(*_texture);
        _sprite.setTextureRect(boundsMap[obj]);
        // _sprite.setColor(sf::Color(255, 255, 255, 200));
        // _sprite.setPosition(100, 25);
    }
    // sf::CircleShape _sprite;
    sf::Sprite _sprite;
    std::shared_ptr<sf::Texture> _texture;
};
