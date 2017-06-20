/**
 * \file      speaker.hh
 * \brief     The declarations of the class Speaker of GAS-02
 * \author    Robbie Valkenburg
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 * \wiki      https://github.com/R2D2-2017/R2D2-2017/wiki/M-LSP-12
 * \trello    https://trello.com/c/rFuGBmTr/5-9-speaker-sounds-alarm-when-threshold-is-crossed
 */

#pragma once
#include "wrap-hwlib.hh"

/**
 * \brief Speaker class for playing sounds.
 */
class Speaker {
public:
    /**
       * \brief Constructor for Speaker.
       *
       * \param speakerPin That must be connected to the speaker.
       */
    Speaker(hwlib::pin_out &speakerPin)
            : speakerPin(speakerPin) {}

    /**
     * \brief Play a note from the speaker.
     *
     * \param note Will be the frequency to play for the speaker.
     */
    void playNote(int note);
private:
    /**
     * Digital pin used for the speaker.
     **/
    hwlib::pin_out & speakerPin;
};
