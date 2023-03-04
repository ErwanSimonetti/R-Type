/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Raylib
*/

#include "Raylib.hpp"

extern "C" std::shared_ptr<IGraphic> createLibrary()
{
    return std::make_shared<Raylib>();
}

Raylib::Raylib() : _window(1920, 1080, "R-TYPE")
{
    createCamera();
    constructFromJson();
}

Raylib::~Raylib()
{

}

void Raylib::constructFromJson()
{
    ReadJson reader("ressources/Raylib/raylib.json");
    int nbAsset = reader.getNumberOfElement("asset");
    int nbSound = reader.getNumberOfElement("sound");

    for (int i = 0; i < nbAsset; i++)
        createModel(reader.IntValueFromArray("asset", i, "type"), reader.readValueFromArray("asset", i, "texture"), \
            reader.readValueFromArray("asset", i, "model"), reader.readValueFromArray("asset", i, "animation"));

    for (int i = 0; i < nbSound; i++) {
        if (reader.IntValueFromArray("sound", i, "type") == 1) {
            _music = LoadMusicStream(reader.readValueFromArray("sound", i, "music").c_str());
            PlayMusicStream(_music);
        } else {
            Sound newSound = LoadSound(reader.readValueFromArray("sound", i, "music").c_str());
            _sound.insert(std::pair<uint16_t, Sound>(reader.IntValueFromArray("sound", i, "type"), newSound));
        }
    }
}

void Raylib::createCamera()
{
    _camera = { 0 };
    _camera.position = (Vector3){ 4.0f, 20.0f, 0.0f };  // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                               // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;  
}

void Raylib::createModel(uint16_t type, std::string texture, std::string model, std::string animation) 
{
    Asset asset;
    asset.texture = LoadTexture(texture.c_str());
    asset.model = LoadModel(model.c_str());
    asset.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = asset.texture;
    asset.model.transform = MatrixRotateXYZ({ 0.0f, 0.0f, 0.0f });
    unsigned int animsmodel = 0;
    asset.animation = LoadModelAnimations(animation.c_str(), &animsmodel);
    asset.size = {0.10f, 0.10f, 0.10f};
    _models.insert(std::pair<uint16_t, Asset>(type, asset));
}

void Raylib::sound_system(sparse_array<SoundEffect> &sounds)
{
    UpdateMusicStream(_music);
    for(size_t i = 0; i < sounds.size(); ++i) {
        auto &sound = sounds[i];
        if (sound) {
            if (sound.value()._play) {
                PlaySound(_sound.find(sound.value()._type)->second);
                sound.value()._play = false;
            }
        }
    }
}

void Raylib::animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables)
{
    for (size_t i = 0; i < animatables.size() && i < drawables.size(); ++ i) {
        auto &anim = animatables[i];
        auto &draw = drawables[i];
        if (anim && draw) {
            if (!_models.count(draw.value()._type) )
                continue;
            auto model = _models.find(draw.value()._type)->second;
            if (!model.animation || !IsModelReady(model.model)) {
                continue;
        }
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - anim.value()._clock);
                if ( anim.value()._refreshPoint == nullptr || *anim.value()._refreshPoint >= _models.find(draw.value()._type)->second.animation[0].frameCount) 
                    anim.value()._refreshPoint = std::make_shared<int>(0);

                if (elapsedTime.count() >= 30) {
                        *anim.value()._refreshPoint += 1;
                        UpdateModelAnimation(_models.find(draw.value()._type)->second.model, _models.find(draw.value()._type)->second.animation[0], *anim.value()._refreshPoint);
                        anim.value()._clock = currentTime;
            }
        }
    }
}

Events get_event() {
    Events newEvent;
    for (auto &it: KeyboardMap)
        if (IsKeyDown(it.first)) 
            newEvent.inputs.emplace_back(it.second);
    return newEvent;
}

 void Raylib::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Particulable> &particles) 
 {
    _window.startDrawing();
    _window.clearWindow();
    _window.start3DMode(_camera);

    for (size_t i = 0; i < drawables.size() && i < positions.size(); ++ i) {
        auto &draw = drawables[i];
        auto &pos = positions[i];
        if (draw && pos) {
            if (!_models.count(draw.value()._type))
                continue;
            DrawModelEx(_models.find(draw.value()._type)->second.model , (Vector3){ pos.value()._x , 0.0f, pos.value()._y }, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
        }

    }
    DrawGrid(10, 1.0f); 
    _window.stop3DMode();
	draw_particles(positions, drawables, particles);
    _window.endDrawing();

 }

 void Raylib::draw_particles(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Particulable> &particles)
 {
    for (size_t i = 0; i < drawables.size() && i < positions.size() && i < particles.size(); ++ i) {
        auto &draw = drawables[i];
        auto &pos = positions[i];
        auto &part = particles[i];
        if (draw && pos && part) {
            if (part.value()._play == true) {
                Vector2 m_pos =(Vector2){(float)pos.value()._x, (float)pos.value()._y};
                _particles.emplace_back(ParticleSystem{m_pos});
                part.value()._play = false;
            }
         _particles.erase(std::remove_if( _particles.begin(), _particles.end(), []( ParticleSystem& sys ){ 
            sys.update();
		    sys.draw();
		    return sys.system.size() <= 0; 
            }),  _particles.end());
        }
    }
 }


Events Raylib::run_graphic(registry &reg) {
    return get_event();
}