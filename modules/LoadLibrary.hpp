/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadLibrary
*/

#ifndef LOADLIBRARY_HPP_
#define LOADLIBRARY_HPP_

#include <ostream>
#include <iostream>
#include <dlfcn.h>

class LoadLibrary {
    public:
        LoadLibrary(std::string newLib);
        ~LoadLibrary();
        
        /**
         * @brief loads graphical lib picked
         * @fn void *loadLibrary();
         * @return void* 
         */
        void *loadLibrary();
        
        /**
         * @brief Get the Function object
         * @fn void *getFunction(void *handle, std::string functionName);
         * @param handle 
         * @param functionName 
         * @return void* 
         */
		void *getFunction(void *handle, std::string functionName);

        /**
         * @brief closes graphical library
         * @fn void closeLibrary(void *handle); 
         * @param handle 
         */
		void closeLibrary(void *handle);

    protected:
    private:
        /**
         * @brief currently loaded library 
         */
        std::string _libName;
};

#endif /* !LOADLIBRARY_HPP_ */
