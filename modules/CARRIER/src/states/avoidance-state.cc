
#include "avoidance-state.hh"
using namespace Carrier;

AvoidanceState::AvoidanceState(CarrierController *controller): controller(controller) {

}


CarrierState AvoidanceState::getState() {
    return CarrierState::Avoidance;
}

void mainAvoidance(){
    if(north.getDistance() <= threshold){
        controller->getMotorController()->stop(controller->getSpeed());
        while( !(south.getDistance() <= threshold) ) {
            controller->getMotorController()->left(controller->getSpeed());
        }
    }


    if( controller->getSensor(Carrier::Sensors::West)->getDistance() <= threshold ){
        controller->getMotorController()->stop(controller->getSpeed());
        //turning around?? ?? nee, dit is stoppen wanneer object tegen is gekomen, daarna ga je kijken in welke situatie je zit.

        // Barrier found. Can't go left or right. Dead end found, turnaround. DEADEND
        if( (East.getDistance() <= threshold) && (West.getDistance() <= threshold) ){
            deadEndState();
        }
        // Barrier found. Barrier to the left. Corner found, turn right. CORNER RIGHT
        if( (East.getDistance() >= threshold) && (West.getDistance() <= threshold) ){
            rightCornerState();
        }
        // Barrier found. Barrier to the right. Corner found, turn right. CORNER LEFT
        if( (East.getDistance() <= threshold) && (West.getDistance() >= threshold) ){
            leftCornerState();
        }
        // Barrier found. No barrier to left or right. Box found, avoid box. ( IN THE BOX FUNTION SHOULD BE THE WALL CATCH ) BOX
        if( (East.getDistance() >= threshold) && (West.getDistance() >= threshold) ){
            boxState();
        }
    }
    //RAVINE FOUND
    if( ((West.getDistance() <= threshold ) && (East.getDistance() <= threshold))&&(North.getDistance >= threshold ){
        valleyState();
    }
}



void AvoidanceState::avoidSimple(){

}

void AvoidanceState::leftCornerState(){
    controller->getMotorController()->left(controller->getSpeed());
    //check north sensor has no treshold


}

void AvoidanceState::rightCornerState(){
    //turn right, make sure the back sensor is pickign up the wall behind you. Ride forward for a little while.
    // give state back to driving
    int temp = North.getDistance();
    while( West.getDistance() >= (temp) )
        controller->getMotorController()->right(controller->getSpeed());

}

void AvoidanceState::valleyState(){
    controller->getMotorController()->forward(controller->getSpeed());
    //riding out of valley
    //check sensor to make sure the valley is gone then swith state

}

void AvoidanceState::deadEndState(){
    controller->getMotorController()->left(controller->getSpeed());
    // How to know when turning succesfull???
    /*
      1. Left sensor clears treshold
    2. Front sensor clears treshold
    3. RIght sensor ses treshold


  */
    // check front sensor for when treshold is gone

}

void AvoidanceState::wallState(){
    //checking if it is a left or right wall state
    if(West.getDistance() <= treshold){
        //left wall right turn
        controller->getMotorController()->right(controller->getSpeed());
        while(West.getDistance() <= treshold){
            //go on
        }
        while(South.getDistance() <= treshold){
            //turning complete
            controller->getMotorController()->stop()
        }
    }else if(East.getDistance() < treshold){
        //right wall left turn

        // Make sure the random driving thing doesnt get control while in this situation...
        //itertions counter. driving when counter max reached turn left
    }

    void AvoidanceState::boxState(){
// go left around the box.
        controller->getMotorController()->left(controller->getSpeed());
        /*
            1. right sensor sees treshold
          2. Go forward for udetirmend time
          3. When right sensor still sees treshold switch to wallState
          4.



        */

    }

