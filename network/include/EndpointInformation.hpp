/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EndpointInformation
*/

#pragma once

#include <boost/asio.hpp>
#include <chrono>

struct EndpointInformation
{
    boost::asio::ip::udp::endpoint _endpoint;
    bool _isAccepted = true;
    bool _isBanTmp = false;
    bool _isBanDef = false;
    std::chrono::steady_clock::time_point _timeStartBanTmp;
    std::chrono::minutes _banTmpDuration;
};
