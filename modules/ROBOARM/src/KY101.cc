//
// Created by Luke Roovers on 2-6-2017.
//

#include "KY101.hh"

KY101::KY101( hwlib::target::pin_in & signal ):
    signal( signal )
{}

KY101::get(){
    if (signal.get()){
        return 1;
    }
    return 0;
}