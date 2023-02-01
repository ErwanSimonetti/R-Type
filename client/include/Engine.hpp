/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Engine
*/

#include "RenderGame.hpp"

/// @brief Engine class used to handle everything related to the game engine

class Engine {
    public:
        /// @brief Create a new instance of object Engine, with a game window size of width and height 
        /// @param width Width of the game window
        /// @param height Height of the game window
        Engine(uint16_t width, uint16_t height);
        ~Engine();
        
        /// @brief Registry variable getter
        /// @return the registry object
        registry get_registry();

        /// @brief Function used to create a friendly "character" entity, giving it an id, and various parameters 
        /// @param id Entity ID
        /// @param col sf::Color object, until we use actual sprites
        /// @param const velX uint_16_t corresponding to the vertical velocity
        /// @param const velY uint_16_t corresponding to the horizontal velocity
        /// @param const posX uint_16_t corresponding to the vertical position
        /// @param const posY uint_16_t corresponding to the horizontal position
        /// @return a friendly entity, that is controllable
        entity create_friendly_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, const uint16_t posY);
        
        /// @brief Function used to create an enemy "character" entity, giving it an id, and various parameters 
        /// @param id Entity ID, has to be unused
        /// @param col sf::Color object, until we use actual sprites
        /// @param const velX uint_16_t corresponding to the vertical velocity
        /// @param const velY uint_16_t corresponding to the horizontal velocity
        /// @param const posX uint_16_t corresponding to the vertical position
        /// @param const posY uint_16_t corresponding to the horizontal position
        /// @return an enemy enity, that cannot be controlled by the user
        entity create_enemy_entity(int id, sf::Color col, const uint16_t velX, const uint16_t velY, const uint16_t posX, uint16_t posY);
        
        /// @brief function used to launch the whole game, systems and all
        void run_game();
    protected:
    private:
        /// @brief registry object 
        registry _reg;

        /// @brief SFML encapsulation
        RenderGame _game;
};
