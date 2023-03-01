/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadLibrary
*/

#include "LoadLibrary.hpp"

LoadLibrary::LoadLibrary(std::string newLib) : _libName(newLib)
{
}

LoadLibrary::~LoadLibrary()
{
}

void *LoadLibrary::loadLibrary()
{
    std::cout << _libName.c_str() << std::endl;
    void *handle = dlopen(_libName.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        std::cerr << "Failed to load shared library: " << dlerror() << std::endl;
        std::cerr << "error loadLibrary";
        std::exit(84);
    }
    return handle;
}

void *LoadLibrary::getFunction(void *handle, std::string functionName)
{
    void *func = dlsym(handle, functionName.c_str());
    const char *error = dlerror();
    if (error != NULL) {
        std::cerr << error << std::endl;
        std::exit(84);
    }
    return func;
}

void LoadLibrary::closeLibrary(void *handle)
{
    dlclose(handle);
}