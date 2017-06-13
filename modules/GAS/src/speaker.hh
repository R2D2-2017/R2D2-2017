#pragma once
#include "wrap-hwlib.hh"

class Speaker {
public:

    Speaker(hwlib::pin_out &lsp)
            : lsp(lsp) {}

    void play(int frequency, int duration);

private:

    hwlib::pin_out & lsp;

};