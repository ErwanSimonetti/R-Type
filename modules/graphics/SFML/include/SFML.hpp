/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFML
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include "SFMLParticle.hpp"
#include <SFML/Graphics.hpp>
#include "IGraphic.hpp"
#include "SFML_utils.hpp"
#include <SFML/Audio.hpp>
// #include <SFML/Mouse.hpp>

struct Asset {
    std::string _texture;
    sf::IntRect _bounds;
    uint16_t _textureSize;
    uint16_t _textureRect;
    sf::Sprite _sprite;
    std::shared_ptr<sf::Texture> _newtexture;
};

class SFML : public IGraphic {

    public:
        SFML();
        ~SFML();
        void createAsset(uint16_t type, std::string texture, uint16_t width, uint16_t height, uint16_t size);
        void animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables);
        void draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Particulable> &particles, sparse_array<DrawableText> &drawableTexts);
        void draw_particles(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Particulable> &particles);
        void clique_system(sparse_array<Cliquable> &cliquables, sparse_array<Drawable> &drawables);
        void sound_system(sparse_array<SoundEffect> &sound);
        void initialize_rect(Drawable &draw);
        Events event_system(registry &reg);
        Events run_graphic(registry &r);
        void constructFromJson();
        void set_sprite();
        void loadModuleSystem(registry &reg);
        void set_text();
        void closeWindow();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Font _font;
        std::unordered_map<uint16_t, Asset> _assets;
        std::unordered_map<uint16_t, sf::Sound> _sound;
        sf::Music _music;
        std::vector<ParticleSystem> _particles;
};

extern "C" std::shared_ptr<IGraphic> createLibrary();

#endif /* !SFML_HPP_ */
