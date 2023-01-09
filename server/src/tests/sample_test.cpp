/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sample_test
*/

#include <string.h>
#include <criterion/criterion.h>

Test(suite_name, test_name) {
    cr_assert(strlen("test") == 4);
}