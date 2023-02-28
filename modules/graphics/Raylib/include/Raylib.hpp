/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Raylib
*/

#include "Raylib_utils.hpp"

#include "IGraphic.hpp"
#include "raylib.h"
#include "raymath.h"
#include "RaylibWindow.hpp"

struct Asset {
    Model model;
    ModelAnimation *animation;
    Vector3 size;
    Texture texture;
};

#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_

class Raylib : public IGraphic {
    public:
        Raylib();
        ~Raylib();
        void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables);
        void animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables);
        void createModel(uint16_t type, std::string texture, std::string model, std::string animation);
        Events run_graphic(registry &r);
        void constructFromJson();
        void createCamera();

    protected:
    private:
    Camera3D _camera;
    std::map<uint16_t, Asset> _models;
    Window _window;
    // bool _initWindow;
};

extern "C" std::shared_ptr<IGraphic> createLibrary();

#endif /* !RAYLIB_HPP_ */
