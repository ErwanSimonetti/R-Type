/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Drawable
*/

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include "ECS_Utils.hpp"

#pragma once

struct Drawable {

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
};

    Drawable() = default;
    void set_component(const OBJECT &obj) {
        _texture = std::make_shared<sf::Texture>();
        if (!_texture->loadFromFile(textureMap[obj].c_str())) {
        std::cerr << "Failed to load texture " << textureMap[obj].c_str() << std::endl;
        }
        _sprite.setTexture(*_texture);
        _sprite.setTextureRect(boundsMap[obj]);
        _textureSize = textureSize[obj];
        _textureRect = textureRect[obj];
    }

    sf::Sprite _sprite;
    std::shared_ptr<sf::Texture> _texture;
    uint16_t _textureSize;
    uint16_t _textureRect;

};
