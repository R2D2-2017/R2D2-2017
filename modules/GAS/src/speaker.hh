#pragma once
#include "wrap-hwlib.hh"

class Speaker {
public:
    /**
       * \brief Constructor for Speaker
       * Initializes lsp
       */
    Speaker(hwlib::pin_out &lsp)
            : lsp(lsp) {}

    void playNote(int note);

private:

    /**
     * pin for the speaker.
     **/
    hwlib::pin_out & lsp;

};