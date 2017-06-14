#include "carrierController.hh"
#include <iostream>
#include <thread>
int main()
{
    std::cout << "Program init" << std::endl;
    auto timeStart = std::chrono::high_resolution_clock::now();
    Carrier::CarrierController c{ };
    std::cout << "CarrierController created" << std::endl;
    c.update();
    std::cout << "update() called" << std::endl;
    std::cout << c.timeUntilDestination(10).count() / std::micro::den << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << c.distanceTraveled( std::chrono::time_point<std::chrono::steady_clock>(std::chrono::high_resolution_clock::now() - timeStart ) ) << " meter" << std::endl;
    std::cin.get();

}