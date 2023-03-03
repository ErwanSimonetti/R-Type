/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EndpointInformation
*/

#pragma once

#include <boost/asio.hpp>

struct EndpointInformation
{
    boost::asio::ip::udp::endpoint _endpoint;
    bool _isAccepted;
};
