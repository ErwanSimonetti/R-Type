/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** exception
*/

#pragma once

#include <exception>

/**
 * @brief this class inherits from expection, its purpose is to manage errors in the ECS.
 * 
 */
struct NoEntityFound : public std::exception
{
    /**
     * @brief  to explain an error
     * 
     * @return const char* value of error
     */
	const char * what () const throw ()
    {
    	return "Can't find an entity matching this index";
    }
};
