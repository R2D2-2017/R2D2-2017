/**
 * \file      speaker.hh
 * \brief     The declarations of the class Speaker of GAS-02
 * \author    Robbie Valkenburg
 * \author    Mike Hilhorst
 * \copyright Copyright (c) 2017, The R2D2 Team
 * \license   See LICENSE
 */

#pragma once
#include "wrap-hwlib.hh"

/**
 * \brief Speaker class for playing sounds
 */
class Speaker {
public:
    /**
       * \brief Constructor for Speaker
       * \param speakerPin that must be connected to the speaker
       */
    Speaker(hwlib::pin_out &speakerPin)
            : speakerPin(speakerPin) {}

    /**
     * \brief play a note from the speaker
     * \param note will be the frequency to play for the speaker. Specified notes can be found in enum.hh
     */
    void playNote(int note);
private:
    /**
     * digital pin used for the speaker
     **/
    hwlib::pin_out & speakerPin;
};