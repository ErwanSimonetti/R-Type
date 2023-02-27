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
        createModel(static_cast<OBJECT>(reader.IntValueFromArray("asset", i, "type")), reader.readValueFromArray("asset", i, "texture"), \
            reader.readValueFromArray("asset", i, "model"), reader.readValueFromArray("asset", i, "animation"));
}

void Raylib::createCamera()
{
    _camera = { 0 };
    _camera.position = (Vector3){ 0.1f, 50.0f, 0.0f };  // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };         // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                               // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;  
}

void Raylib::createModel(OBJECT type, std::string texture, std::string model, std::string animation) 
{
    Asset asset;
    asset.texture = LoadTexture(texture.c_str());
    asset.model = LoadModel(model.c_str());
    asset.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = asset.texture;
    asset.model.transform = MatrixRotateXYZ({ 90.0f, -90.0f, 0.0f });
    unsigned int animsmodel = 0;
    asset.animation = LoadModelAnimations(animation.c_str(), &animsmodel);
    asset.size = {0.10f, 0.10f, 0.10f};
    std::cout << type << " "<< texture << model<< " " << animation << " " << std::endl;
    _models.insert(std::pair<OBJECT, Asset>(type, asset));
}

void Raylib::animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables)
{
    for (size_t i = 0; i < animatables.size() && i < drawables.size(); ++ i) {
        auto &anim = animatables[i];
        auto &draw = drawables[i];
        if (anim && draw) {
            if (!_models.count(draw.value()._type))
                continue;
            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - anim.value()._clock);

            if ( anim.value()._refreshPoint == nullptr || *anim.value()._refreshPoint >=  _models.find(draw.value()._type)->second.animation[0].frameCount) 
                anim.value()._refreshPoint = std::make_shared<int>(0);

            if (elapsedTime.count() >= 30) {
                *anim.value()._refreshPoint += 1;
                UpdateModelAnimation(_models.find(draw.value()._type)->second.model, _models.find(draw.value()._type)->second.animation[0], *anim.value()._refreshPoint);
                anim.value()._clock = currentTime;
            }
        }
    }
}

EntityEvent get_event() {
    EntityEvent newEvent;
    for (auto &it: KeyboardMap)
        if (IsKeyDown(it.first)) 
            newEvent.events.emplace_back(it.second);
    return newEvent;
}

 void Raylib::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables) 
 {

    _window.startDrawing();
    _window.clearWindow();
    _window.start3DMode(_camera);

    if (IsKeyDown(KEY_SPACE)) {
    std::cout << _camera.position.x << " " << _camera.position.y << " " << _camera.position.x  << " " << std::endl;
    std::cout << _camera.position.x << " " << _camera.position.y << " " << _camera.position.x  << " " << std::endl;
    std::cout << _camera.up.x << " " << _camera.up.y << " " << _camera.up.x  << " " << std::endl;
    }

    for (size_t i = 0; i < drawables.size() && i < positions.size(); ++ i) {
        auto &draw = drawables[i];
        auto &pos = positions[i];
        if (draw && pos) {
            if (!_models.count(draw.value()._type))
                continue;
            DrawModelEx(_models.find(draw.value()._type)->second.model , (Vector3){ (pos.value()._x - 18), 0.0f, (pos.value()._y + 33) }, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.0f, (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
        }

    }
    DrawGrid(1000, 1.0f); 
    _window.stop3DMode();
    _window.endDrawing();

 }


EntityEvent Raylib::run_graphic(registry &reg) {
    return get_event();
}