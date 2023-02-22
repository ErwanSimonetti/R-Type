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
    // createCamera();

    // createModel(SHIP, "ressources/Raylib/BombermanBlue.png", "ressources/Raylib/Bomberman.iqm", "ressources/Raylib/BombermanAnim.iqm");
}

Raylib::~Raylib()
{

}

void Raylib::createWindow()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");  
    SetTargetFPS(60);
}

void Raylib::createCamera()
{
    _camera = { 0 };
    _camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    _camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    _camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    _camera.fovy = 45.0f;                                // Camera field-of-view Y
    _camera.projection = CAMERA_PERSPECTIVE;  
}

void Raylib::createModel(OBJECT type, std::string texture, std::string model, std::string animation) 
{
    Asset asset;
    asset.texture = LoadTexture(texture.c_str());
    asset.model = LoadModel(model.c_str());
    // model.model.materials[0].shader = fireShader;
    asset.model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = asset.texture;
    asset.model.transform = MatrixRotateXYZ({ 140.0f, 0.0f, 0.0f });
    unsigned int animsmodel = 0;
    asset.animation = LoadModelAnimations(animation.c_str(), &animsmodel);
    asset.size = {0.15f, 0.15f, 0.15f};
    _models.insert(std::pair<OBJECT, Asset>(type, asset));
}

// EntityEvent Raylib::event_system()
void Raylib::animation_system(sparse_array<Animatable> &animatables, sparse_array<Drawable> &drawables)
{

}

EntityEvent get_event() {
    EntityEvent newEvent;
    for (auto &it: KeyboardMap)
        if (IsKeyDown(it.first)) 
            newEvent.events.emplace_back(it.second);
    return newEvent;
}

 void Raylib::draw_system(sparse_array<Position> const &positions, sparse_array<Drawable> &drawables) {
 
    SetTargetFPS(60);
    // Main game loop
    // if (IsWindowReady()) {
    // while (!WindowShouldClose())    // Detect window close button or ESC key
    // {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        // _window.startDrawing();

            _window.clearWindow();
            std::cout << "REFRESH" << std::endl;
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        // _window.endDrawing();
        EndDrawing();
        //----------------------------------------------------------------------------------
    // }
    // }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // CloseWindow();  
 }


EntityEvent Raylib::run_graphic(registry &reg) {
    return get_event();
}