//
// Created by Robert on 5/24/17.
//
#pragma once
//#include "wrap-hwlib.hh"
#include <sam3x8e.h>

namespace hwlib {
bool uart_char_available();
void uart_putc(char c);
char uart_getc();
void init(unsigned int baudrate);
}

