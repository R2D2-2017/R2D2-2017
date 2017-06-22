/**
 * \file      main.cc
 * \brief     Main of the NAVSYS Client
 * \author    Philippe Zwietering
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See ../../LICENSE
 */

#include "server.hh"
#include <iostream>

int main() {
    std::cout << "Starting server\n";
    Server(5000).run();
    return 0;
}
