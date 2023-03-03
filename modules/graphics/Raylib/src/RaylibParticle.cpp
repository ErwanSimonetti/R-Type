/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibParticle
*/

#include "RaylibParticle.hpp"

Particle::Particle(Vector2 &pos) : _position(pos)
{
    _size = 5.0f;
    _velocity.x = GetRandomValue(-20, 20)*.1f;
    _velocity.y = GetRandomValue(-50, -20)*.1f;
    _acc.x = 0;
    _acc.y = 0.05f;
}

Particle::~Particle()
{
}


void Particle::draw(){
    // DrawCircle(position.x, position.y, size, RED);
    Color color = {0, 204, 102, 255};
    Color color2 = {87, 168, 98, 255};
	DrawRectangle(_position.x, _position.y, _size, _size, ORANGE);
    DrawCircleLines(_position.x, _position.y, _size, color);
    // DrawCircleLines(_position.x+0.5f, _position.y+0.5f, _size/2, MAROON);
    // DrawCircleLines(_position.x, _position.y, _size/2, MAROON);
}
void Particle::update(){
    if (_velocity.x < 10 && _velocity.y < 10 && _velocity.x > -10 && _velocity.y > -10) {
    _velocity.x = _velocity.x + _acc.x;
    _velocity.y = _velocity.y + _acc.y;
    }

    _position.x = _position.x + _velocity.x;
    _position.y = _position.y + _velocity.y;

    if (GetRandomValue(0, 100) < 30) 
        _size -= 1;
}





ParticleSystem::ParticleSystem(Vector2& pos) {
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