#include "carrierController.hh"
#include <iostream>
int main()
{
    std::cout << "Program init" << std::endl;
    Carrier::CarrierController c{ 0,0 };
    std::cout << "CarrierController created" << std::endl;
    c.update();
    std::cout << "update" << std::endl;
    std::cin.get();

}