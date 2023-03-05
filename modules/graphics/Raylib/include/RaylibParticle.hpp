/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibParticle
*/


#ifndef RAYLIBPARTICLE_HPP_
#define RAYLIBPARTICLE_HPP_

#define MAX_PARTICLE 20

#include "raylib.h"
#include <iostream>
#include <algorithm>

class Particle {
    public:
        
        Particle(std::pair<int, int> &pos);
        ~Particle();

        void draw();
        void update();

        float _size;
        std::pair<int, int> _velocity;
        private:
        std::pair<int, int> _acc;
        std::pair<int, int> _position;

};

class ParticleSystem {

    public:
		
    ParticleSystem(std::pair<int, int> & pos);
    ~ParticleSystem() = default;

    void draw();
    
    void update();

    std::vector<Particle> system;
};

#endif /* !RAYLIBPARTICLE_HPP_ */