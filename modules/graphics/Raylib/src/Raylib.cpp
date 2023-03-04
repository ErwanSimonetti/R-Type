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

    for (int i = 0; i < nbAsset; i++)
        createModel(reader.IntValueFromArray("asset", i, "type"), reader.readValueFromArray("asset", i, "texture"), \
            reader.readValueFromArray("asset", i, "model"), reader.readValueFromArray("asset", i, "animation"));
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

void Raylib::loadModuleSystem(registry &_reg)
{
    _reg.add_system<Position, Drawable, Animatable>(std::bind(&Raylib::draw_system, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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
            if ( anim._refreshPoint == nullptr || *anim._refreshPoint >= _models.find(draw._type)->second.animation[anim._animationIndex].frameCount) 
                anim._refreshPoint = std::make_shared<int>(0);

            if (elapsedTime.count() >= 30) {
                    *anim._refreshPoint += 1;
                    UpdateModelAnimation(_models.find(draw._type)->second.model, _models.find(draw._type)->second.animation[anim._animationIndex], *anim._refreshPoint);
                    anim._clock = currentTime;
            }
}

Events get_event() {
    Events newEvent;
    for (auto &it: KeyboardMap) {
        if (IsKeyDown(it.first)) 
            newEvent.inputs.emplace_back(it.second);
    }
    newEvent.inputs.emplace_back(KEYBOARD::NONE);
    return newEvent;
}

 void Raylib::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables, sparse_array<Animatable> &animables) 
 {
    // UpdateCamera(&_camera, CAMERA_FIRST_PERSON);

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
    _window.endDrawing();

 }


Events Raylib::run_graphic(registry &reg) {
    return get_event();
}