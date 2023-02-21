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

Raylib::Raylib()
{
    InitWindow(1920, 1080, "R-TYPE");
    SetTargetFPS(60); 
}

Raylib::~Raylib()
{
    CloseWindow();
}

EntityEvent Raylib::run_graphic(registry &reg) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //DRAW

    EndDrawing();
    return event_system(reg);
}