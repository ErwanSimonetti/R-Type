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
#include "RaylibParticle.hpp"
#include "RaylibWindow.hpp"


#ifndef RAYLIB_HPP_
#define RAYLIB_HPP_

struct Asset {
    Model model;
    ModelAnimation *animation;
    Vector3 size;
    Texture texture;
};

class Raylib : public IGraphic {
    public:
        Raylib();
        ~Raylib();
        void draw_particles(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Particulable> &particles);
        void sound_system(sparse_array<SoundEffect> &sound);
        void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<DrawableText> &drawableText, sparse_array<Particulable> &particles, sparse_array<Animatable> &animables);
        void animation_system(Animatable &animatables, Drawable &drawables);
        void createModel(uint16_t type, std::string texture, std::string model, std::string animation);
        void loadModuleSystem(registry &reg);
        Events run_graphic(registry &r);
        void constructFromJson();
        void createCamera();
        void clique_system(sparse_array<Cliquable> &cliquables, sparse_array<Drawable> &drawables) {};
        void closeWindow(){};

    protected:
    private:
    Camera3D _camera;
    std::map<uint16_t, Asset> _models;
    std::map<uint16_t, Sound> _sound;
    Window _window;
    std::vector<ParticleSystem> _particles;
    Music _music;
};

extern "C" std::shared_ptr<IGraphic> createLibrary();

#endif /* !RAYLIB_HPP_ */
