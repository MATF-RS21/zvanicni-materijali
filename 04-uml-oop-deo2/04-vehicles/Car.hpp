#ifndef CAR_HPP
#define CAR_HPP

#include "VehicleWithWindows.hpp"

class Car : public VehicleWithWindows
{
public:
    Car(const unsigned windows = 6u, const unsigned seats = 5u, const unsigned wheels = 4u)
        : VehicleWithWindows(windows, seats, wheels)
    {
    }

    Vehicle *Copy() const override
    {
        return new Car(*this);
    }

    std::string Type() const override
    {
        return "Car";
    }
};

std::ostream &operator<<(std::ostream &out, const Car &a)
{
    return out << a.Type() << " " << a.NumOfSeats() << " " << a.NumOfWheels() << " " << a.NumOfWindows();
}

#endif // CAR_HPP
