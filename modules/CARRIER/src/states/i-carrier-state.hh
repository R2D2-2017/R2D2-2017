#pragma once
namespace Carrier
{
    enum class CarrierState {
        Idle,
        Forward,
        Backward,
        Clockwise,
        CounterClockwise
    };

class ICarrierState {
    public:
        virtual void update() = 0;
        virtual CarrierState getState() = 0;
};
}
