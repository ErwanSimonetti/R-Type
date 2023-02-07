/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>

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
        printf("%s\n", textureMap[SHIP].c_str());
        // sf::Texture _texture;
        if (!_texture.loadFromFile(textureMap[SHIP].c_str())) {
        std::cerr << "Failed to load texture " << textureMap[SHIP].c_str() << std::endl;
        }
        _sprite.setTexture(_texture);
        // _sprite.setTextureRect(boundsMap[SHIP]);
        // _sprite.setColor(sf::Color(255, 255, 255, 200));
        // _sprite.setPosition(100, 25);
    }
    // sf::CircleShape _sprite;
    sf::Sprite _sprite;
    sf::Texture _texture;
};
