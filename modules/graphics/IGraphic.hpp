/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include "registry.hpp"
#include "System.hpp"
#include "GameEvents.hpp"
#include "ReadJson.hpp"

class IGraphic {
    public:
        IGraphic() = default;
        ~IGraphic() = default;
        virtual void loadModuleSystem(registry &reg) = 0;
        virtual Events run_graphic(registry &r) = 0;
    protected:
    private:
};

#endif /* !IGRAPHIC_HPP_ */
