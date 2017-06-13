//
// Created by Luke Roovers on 12-6-2017.
//

#ifndef TEMPLATE_PC_HC_SR04_HH
#define TEMPLATE_PC_HC_SR04_HH

class hcSr04 {
private:
    int     TriggerPin;
    int     EchoPin;
    float   distance;
    double  distanceMeters;
    long    travelTimeUsec;
    long    now;
    volatile long endTimeUsec;
    volatile long startTimeUsec;
public:
    hcSr04(int & TriggerPin,int & EchoPin);
    float   get();
    double  getDistance();
    void    Timer();
};




#endif //TEMPLATE_PC_HC_SR04_HH
