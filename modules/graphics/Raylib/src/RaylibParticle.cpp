/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibParticle
*/

#include "RaylibParticle.hpp"

Particle::Particle(std::pair<int, int> &pos) : _position(pos)
{
    _size = 5.0f;
    _velocity.first = GetRandomValue(-20, 20)*.1f;
    _velocity.second = GetRandomValue(-50, -20)*.1f;
    _acc.first = 0;
    _acc.second = 0.05f;
}

Particle::~Particle()
{
}


void Particle::draw(){
    Color color = {0, 204, 102, 255};
    Color color2 = {87, 168, 98, 255};
	DrawRectangle(_position.first + 3, _position.second + 3, _size, _size, ORANGE);
    DrawCircleLines(_position.first, _position.second, _size + 10, color);
}

void Particle::update(){
    if (_velocity.first < 10 && _velocity.second < 10 && _velocity.first > -10 && _velocity.second > -10) {
    _velocity.first = _velocity.first + _acc.first;
    _velocity.second = _velocity.second + _acc.second;
    }

    _position.first = _position.first + _velocity.first;
    _position.second = _position.second + _velocity.second;

    if (GetRandomValue(0, 100) < 30) 
        _size -= 1;
}





ParticleSystem::ParticleSystem(std::pair<int, int> & pos) {
    system.reserve(MAX_PARTICLE);
    for (int i = 0; i < MAX_PARTICLE; i++) { 
            system.emplace_back(pos);   
    }
}

void ParticleSystem::draw(){
    for (std::vector<Particle>::iterator obj = system.begin(); obj < system.end(); obj++) {
        obj->draw();
    }
}

void ParticleSystem::update(){
    system.erase( std::remove_if( system.begin(), system.end(), []( auto& p ){ 
        p.update(); 
        return p._size <= 0; 
    }), system.end());
}