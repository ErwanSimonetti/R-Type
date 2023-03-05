/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibParticle
*/


#ifndef SFMLPARTICLE_HPP_
#define SFMLPARTICLE_HPP_

#define MAX_PARTICLES 5

#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

class Particle {
    public:
        
        Particle(std::pair<int, int> &pos);
        ~Particle();

        void draw(sf::RenderWindow &window);
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
	
    void draw(sf::RenderWindow &window);
    
    void update();

    std::vector<Particle> system;
};

#endif /* !RAYLIBPARTICLE_HPP_ */