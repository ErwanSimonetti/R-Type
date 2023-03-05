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
    _camera.position = (Vector3){ 5.0f, 120.0f, 200.0f };   // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };         // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };             // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                                   // Camera field-of-view Y
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
    asset.size = {10.00f, 10.00f, 10.00f};
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

void Raylib::loadModuleSystem(registry &_reg)
{
    _reg.add_system<Position, Drawable, DrawableText, Particulable, Animatable>(std::bind(&Raylib::draw_system, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
    _reg.add_system<SoundEffect>(std::bind(&Raylib::sound_system, this, std::placeholders::_1));
}

void Raylib::animation_system(Animatable &anim, Drawable &draw)
{
    if (!_models.count(draw._type) )
        return;
    auto model = _models.find(draw._type)->second;
    if (!model.animation || !IsModelReady(model.model)) {
        return;
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - anim._clock);
    if (anim._refreshPoint == nullptr || *anim._refreshPoint >= _models.find(draw._type)->second.animation[anim._animationIndex].frameCount) 
        anim._refreshPoint = std::make_shared<int>(0);
    if (elapsedTime.count() >= 30) {
        *anim._refreshPoint += 1;
        anim._clock = currentTime;
    }
    UpdateModelAnimation(_models.find(draw._type)->second.model, _models.find(draw._type)->second.animation[anim._animationIndex], *anim._refreshPoint);
}

Events get_event() {
    Events newEvent;
    for (auto &it: KeyboardMap) {
        if (IsKeyDown(it.first)) 
            newEvent.inputs.emplace_back(it.second);
        if (IsKeyReleased(it.first)) 
            newEvent.inputs.emplace_back(KEYBOARD::NONE);
    }
    return newEvent;
}

 void Raylib::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<DrawableText> &drawableTexts, sparse_array<Particulable> &particles, sparse_array<Animatable> &animables) 
 {
    _window.startDrawing();
    _window.clearWindow();
    _window.start3DMode(_camera);

    for (size_t i = 0; i < drawables.size() && i < positions.size() && i < animables.size(); ++ i) {
        auto &draw = drawables[i];
        auto &pos = positions[i];
        auto &anim = animables[i];
        if (draw && pos) {
            if (!_models.count(draw.value()._type))
                continue;
            _models.find(draw.value()._type)->second.model.transform = MatrixRotateXYZ((Vector3){ 
                DEG2RAD*draw.value()._rotation.angleX, DEG2RAD*draw.value()._rotation.angleY, DEG2RAD*draw.value()._rotation.angleZ });
            if (anim && draw)
                animation_system(anim.value(), draw.value());
            DrawModel(_models.find(draw.value()._type)->second.model , (Vector3){ float(pos.value()._x) , float(pos.value()._y), float(pos.value()._z) }, draw.value()._scale, WHITE);
        }

    }
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