/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** exception
*/

#pragma once

#include <exception>

/**
 * @brief is class inherited from expection for throw when NoEntityFound in the ECS.
 * 
 */
struct NoEntityFound : public std::exception
{
    /**
     * @brief give a char * for explain error
     * 
     * @return const char* value of error
     */
	const char * what () const throw ()
    {
    	return "Can't find an entity matching this index";
    }
};
