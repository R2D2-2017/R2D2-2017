//
// Created by Luke Roovers on 2-6-2017.
//

#ifndef ROBOARM_KY101_HH
#define ROBOARM_KY101_HH


class KY101 {
private:
    hwlib::target::pin_in & signal;
public:
    KY101( hwlib::target::pin_in & signal );
    bool get();
};


#endif //ROBOARM_KY101_HH
