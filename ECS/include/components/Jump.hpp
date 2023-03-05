/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Jump
*/

#ifndef JUMP_HPP_
#define JUMP_HPP_

#include <ostream>

/**
 * @brief components for the ECS, represents the entity Jump
 */
struct Jump {
    Jump() = default;

    /**
     * @brief Set the Jump values
     * 
     * @param jumpForce the jumpForce of the Jump
     */
    void set_component(const int16_t &jumpForce) {
        _clock = std::chrono::high_resolution_clock::now();
        _jumpForce = jumpForce;
        _jumpHeight = jumpForce;
        _canJump = true;
        _isJumping = false;
        _hasReachedTheTop = false;
        _stop = false;
    }

    /**
     * @brief overload << operator
     * 
     * @param output, variable to fill for print the result of the function.
     * @param D class with the field to print.
     * @return std::ostream&, output.
     */
    friend std::ostream &operator<<(std::ostream &output, const Jump &D) {
        output << "jumpForce = " << D._jumpForce  << std::endl;
        return output;
    }
    int16_t _jumpForce;
    int16_t _jumpHeight;
    bool _canJump;
    bool _stop;
    bool _isJumping;
    bool _hasReachedTheTop;
    std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
};

#endif /* !JUMP_HPP_ */
