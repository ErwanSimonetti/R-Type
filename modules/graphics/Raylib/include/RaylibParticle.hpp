/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibParticle
*/


#ifndef RAYLIBPARTICULE_HPP_
#define RAYLIBPARTICULE_HPP_

#define MAX_PARTICLE 200

#include "raylib.h"
#include <iostream>
#include <algorithm>

class Particle {
    public:
        
        Particle(Vector2 &pos);
        ~Particle();

        void draw();
        void update();

        float _size;
        Vector2 _velocity;
        private:
        Vector2 _acc;
        Vector2 _position;

};

class ParticleSystem {

    public:
		
    ParticleSystem(Vector2& pos);
    ~ParticleSystem() = default;
	
    void draw();
    
    void update();

    std::vector<Particle> system;
};

#endif /* !RAYLIBPARTICULE_HPP_ */