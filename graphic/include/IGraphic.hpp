/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include <SFML/Graphics.hpp>

#include "registry.hpp"
#include "System.hpp"
#include "SFML_utils.hpp"
#include "Engine_utils.hpp"

class IGraphic {
    public:
        IGraphic() = default;
        ~IGraphic() = default;
        virtual void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables) = 0;
        virtual void animation_system(registry &r, sparse_array<Animatable> &animatable, sparse_array<Drawable> &drawable) = 0;
        virtual EntityEvent run_graphic(registry &r) = 0;
        virtual void hello() = 0;

    protected:
    private:
};

#endif /* !IGRAPHIC_HPP_ */
