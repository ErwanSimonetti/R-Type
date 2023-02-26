/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rtype
*/

#ifndef RTYPE_HPP_
#define RTYPE_HPP_

#include "IGame.hpp"
#include <memory>

class Rtype : public IGame {
    public:
        Rtype();
        ~Rtype();

        std::vector<entity> getPLayers() const;

        void initGame(registry &r);
        void run_gameLogic(registry &r, const Events &events);
        void updateRegistry(registry &r, const GameData &data);
        void updateRegistry(registry &r, const GameData data[4]);
        void create_player(registry &r, entity newEntity, bool isControllable, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);
        void create_enemy_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, uint16_t posY);
        void create_entity(registry &r, entity newEntity, const int16_t velX, const int16_t velY, const uint16_t posX, const uint16_t posY);
        void create_projectile(registry &r, entity newEntity, int16_t parentId, const uint16_t velX, const uint16_t velY);
        void create_parallax(registry &r, entity newEntity, const uint16_t posX, const uint16_t posY, const uint16_t speed, const OBJECT obj);

    protected:
        void handleInputs(registry &r, size_t entity, const uint16_t inputs[10]);
    private:
        /**
         * @brief players vector 
         **/ 
        std::vector<entity> _players;

};

extern "C" std::shared_ptr<IGame> createLibrary();

#endif /* !RTYPE_HPP_ */
