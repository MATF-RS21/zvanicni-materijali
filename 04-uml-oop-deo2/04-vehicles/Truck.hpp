#ifndef TRUCK_HPP
#define TRUCK_HPP

#include "VehicleWithWindows.hpp"

class Truck : public VehicleWithWindows
{
public:
    Truck(const unsigned windows = 3u, const unsigned seats = 3u, const unsigned wheels = 6u)
        : VehicleWithWindows(windows, seats, wheels)
    {
    }

    Vehicle *Copy() const override
    {
        return new Truck(*this);
    }

    std::string Type() const override
    {
        return "Truck";
    }
};

std::ostream &operator<<(std::ostream &out, const Truck &k)
{
    return out << k.Type() << " " << k.NumOfSeats() << " " << k.NumOfWheels() << " " << k.NumOfWindows();
}

#endif // TRUCK_HPP

