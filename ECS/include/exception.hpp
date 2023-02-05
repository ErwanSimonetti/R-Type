/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** exception
*/

#pragma once

#include <exception>

struct NoEntityFound : public std::exception
{
	const char * what () const throw ()
    {
    	return "Can't find an entity matching this index";
    }
};
