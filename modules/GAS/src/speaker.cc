//
// Created by MuscioCraft on 13-6-2017.
//

#include "speaker.hh"

void Speaker::play( int frequency, int duration){
    if( frequency == 0 ){
        hwlib::wait_us( duration );
    } else {
        auto end = hwlib::now_us() + duration;
        auto half_period = 1000000 / ( 2 * frequency );
        while( end > hwlib::now_us() ){
            lsp.set( 1 );
            hwlib::wait_us( half_period );
            lsp.set( 0 );
            hwlib::wait_us( half_period );
        }
    }
}

