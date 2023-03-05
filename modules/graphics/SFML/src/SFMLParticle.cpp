/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibParticle
*/

#include "SFMLParticle.hpp"

Particle::Particle(std::pair<int, int> &pos) : _position(pos)
{
    _size = 5.0f;
    _velocity.first = ((rand() % 50))*.1f;
    _velocity.second = ((rand() % 50) - 25)*.1f;
    _acc.first = 0;
    _acc.second = 0.01f;
}

Particle::~Particle()
{
}

void Particle::draw(sf::RenderWindow &window){
    sf::CircleShape shape(2);
    shape.setPosition(_position.first, _position.second);
    shape.setFillColor(sf::Color(135, 206, 250));
    window.draw(shape);
}

void Particle::update(){
    if (_velocity.first < 10 && _velocity.second < 10 && _velocity.first > -10 && _velocity.second > -10) {
    _velocity.first = _velocity.first + _acc.first;
    _velocity.second = _velocity.second + _acc.second;
    }

    _position.first = _position.first + _velocity.first;
    _position.second = _position.second + _velocity.second;

    if ((rand() % 100) < 30) 
        _size -= 1;
}





ParticleSystem::ParticleSystem(std::pair<int, int> & pos) {
    system.reserve(1);
    for (int i = 0; i < 1; i++) { 
            system.emplace_back(pos);   
    }
}

void ParticleSystem::draw(sf::RenderWindow &window){
    for (std::vector<Particle>::iterator obj = system.begin(); obj < system.end(); obj++) {
        obj->draw(window);
    }
}

void ParticleSystem::update(){
    system.erase( std::remove_if( system.begin(), system.end(), []( auto& p ){ 
        p.update(); 
        return p._size <= 0; 
    }), system.end());
}