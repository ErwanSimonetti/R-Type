/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Raylib
*/

#include "RaylibWindow.hpp"

Window::Window(const int &screenWidth, const int &screenHeight, const std::string &name, const int &fps) :
    _screenHeight(screenHeight),
    _screenWidth(screenWidth),
    _name(name)
{
    InitWindow(screenWidth, screenHeight, name.c_str());
    if (!IsWindowReady()) {
        
    }
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        
    }
    SetTargetFPS(fps);
}

Window::~Window()
{
    CloseAudioDevice();
    CloseWindow();
}

bool const Window::windowIsClose()
{
    return WindowShouldClose();
}

int const& Window::getScreenWidth()
{
    return _screenWidth;
}

int const& Window::getScreenHeight()
{
    return _screenHeight;
}

std::string const& Window::getName()
{
    return _name;
}

void const Window::startDrawing()
{
    BeginDrawing();
}

void const Window::endDrawing()
{
    EndDrawing();
}

void Window::clearWindow()
{
    ClearBackground(LIGHTGRAY);
}

void const Window::start3DMode(Camera3D &camera)
{
    BeginMode3D(camera);
}

void const Window::stop3DMode()
{
    EndMode3D();
}