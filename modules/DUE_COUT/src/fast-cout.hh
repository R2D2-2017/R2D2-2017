//
// Created by Robert on 5/24/17.
//
#pragma once
#include "wrap-hwlib.hh"

namespace hwlib {
bool uart_char_available();
void init(unsigned int baudrate);
}

