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
#include "Engine_utils.hpp"
#include "ReadJson.hpp"

class IGraphic {
    public:
        IGraphic() = default;
        ~IGraphic() = default;
        virtual void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables) = 0;
        virtual void animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables) = 0;
        virtual Events run_graphic(registry &r) = 0;

    protected:
    private:
};

#endif /* !IGRAPHIC_HPP_ */
