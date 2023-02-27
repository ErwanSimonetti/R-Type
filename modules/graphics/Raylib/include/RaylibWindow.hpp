/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RaylibWindow
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include "raylib.h"

class Window
{
    private:
        int _screenWidth;
        int _screenHeight;
        std::string _name;
    public:
        Window(const int &screenWidth, const int &screenHeight, const std::string &name, const int &fps = 60);
        ~Window();
        bool const windowIsClose();
        void const startDrawing();
        void const endDrawing();
        void const start3DMode(Camera3D &camera);
        void const stop3DMode();
        int const& getScreenWidth();
        int const& getScreenHeight();
        std::string const& getName();
        void clearWindow();
};

#endif /* !WINDOW_HPP_ */
